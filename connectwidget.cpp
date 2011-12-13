#include "connectwidget.h"
#include "ui_connectwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "qextserialenumerator.h"
#include <QDebug>
#include <iostream>
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QFileInfo>

#define FAB_CONFIG_DIRECTORY_NAME_UNIX ".fab_configs"
#define FAB_CONFIG_DIRECTORY_NAME_WIN "Fab Configs"

ConnectWidget::ConnectWidget(QWidget *parent, CoreInterface *ci) : QWidget(parent), ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);
    ci_ = ci;

    // Populate portList and ui->portBox.
    foreach(QextPortInfo port, QextSerialEnumerator::getPorts())
    {
        // Display the port's FriendName in the GUI portBox;
        // printer connection uses the PortName (portList values).
        // Ports which are clearly not printers (empty FriendNames) are ignored.

        // NOTE: Since the selected port name is retrieved by its combobox index
        //       (because friend name may not be unique), it is important that
        //       the order of portBox items be maintained.
        // The selected port name is retrieved by portList.at(ui->portBox->currentIndex()).

        if (!port.friendName.isEmpty())
        {
            portList.append(port.portName);
            ui->portBox->addItem(port.friendName);
        }
    }

    if (portList.size() == 1)
    {
        // Only one possible printer found; select it.
        ui->portBox->setCurrentIndex(0);
    }

    // Populate configList and ui->configBox.
    // NOTE: Since the selected file is retrieved by its combobox index
    //       (because base name may not be unique), it is important that
    //       the order of configBox items be maintained.
    // The selected  config path is retrieved by configList.at(ui->configBox->currentIndex()).

    QString verifyDirectoryExistsCommand;

    if (true /* OS is UNIX-like */)
    {
        configFileDirectory = QDir(QDir::homePath() + "/" + FAB_CONFIG_DIRECTORY_NAME_UNIX + "/");

        if(!configFileDirectory.exists()){
            configFileDirectory.mkdir("child");
        }
    }
    else
    {
        configFileDirectory = QDir(QDir::homePath() + "\\" + FAB_CONFIG_DIRECTORY_NAME_WIN);
        if(!configFileDirectory.exists()){
            configFileDirectory.mkdir("child");
            printf("\nmaking dir child");
        }
        // Code to make sure the directory exists on Windows...
        // configFileDirectory = whatever I want it to be on Windows
    }

    system(verifyDirectoryExistsCommand.toStdString().c_str());

    loadFiles();

    QSettings theSettings("Creative Machines Lab", "FabPrint");
    ui->configBox->setCurrentIndex(theSettings.value("load config next time index", 0).toInt());


//SAMPLE getPorts() OUTPUT (MAC OS)
//Starting /Applications/D:/fab@home/FabPrint/FabPrint-build-desktop/FabPrint.app/Contents/MacOS/FabPrint...
//PortName:  "/dev/cu.usbserial-A9003UF2" ;
// PhysName:  "IOService:/AppleACPIPlatformExpert/PCI0@0/AppleACPIPCI/OHC1@4/AppleUSBOHCI/FT232R USB UART@4400000/FT232R USB UART@0/FTDIUSBSerialDriver/IORS232SerialStreamSync/IOSerialBSDClient" ;
// FriendName:  "FT232R USB UART" ;
// EnumName:  "" ;
// VendorID:  1027 ;
// ProductID:  24577 .

//PortName:  "/dev/cu.Bluetooth-PDA-Sync" ;
// PhysName:  "IOService:/IOResources/IOBluetoothSerialManager/IOBluetoothSerialClient/IOBluetoothSerialClientSerialStreamSync/IOSerialBSDClient" ;
// FriendName:  "" ;
// EnumName:  "" ;
// VendorID:  0 ;
// ProductID:  0 .

//PortName:  "/dev/cu.Bluetooth-Modem" ;
// PhysName:  "IOService:/IOResources/IOBluetoothSerialManager/IOBluetoothSerialClient/IOBluetoothSerialClientModemStreamSync/IOSerialBSDClient" ;
// FriendName:  "" ;
// EnumName:  "" ;
// VendorID:  0 ;
// ProductID:  0 .

}

// Reload .config files from the appropriate directory for the given platform
void ConnectWidget::loadFiles()
{
    // Cloud-leveraged parameter-widgetized Qmagic to load the files into the config list
    configList = configFileDirectory.entryInfoList(QStringList("*.config"), QDir::Files);

    // Clear the entries currently in the config combo box
    ui->configBox->clear();

    // Add all of the files from the configList to the combo box
    foreach(QFileInfo config, configList){
        ui->configBox->addItem(config.baseName());
    }


}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

// Copy the config file specified in path into the config directory
void ConnectWidget::addConfig(QString path)
{
    QFile* command = new QFile(path);

    if(command->open(QIODevice::ReadOnly)){


        QString str = command->fileName();
        QStringList parts = str.split("/");
        QString simpleName = parts.at(parts.size()-1);

        QString newPath = configFileDirectory.absolutePath()+ QDir::separator() + simpleName;

        qDebug() << newPath;
        if(!command->copy(newPath)){
            printf("Error copying the code.");
        }

    }
    else{
        printf("Error opening the file.");
    }
}

/*
 Public slot to preload a remembered configuration file.
 */
//void ConnectWidget::preloadConfig(QString preloaded_path)
//{
//    addConfig(preloaded_path);
//}

void ConnectWidget::on_configButton_clicked(){
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open"),
    QDir::homePath(), tr("Printer Config File (*.config);;All Files (*.*)"));
    addConfig(filepath); // addConfig should do the file copy/move
    loadFiles();
    // TODO: the chooser dialog starts in the last-used directory instead of the home folder
}

void ConnectWidget::on_connectButton_clicked(){
    int portIndex   = ui->portBox  ->currentIndex();
    int configIndex = ui->configBox->currentIndex();
    bool canConnect = true;

    if (portIndex == -1){
        QMessageBox::information(this, "FabPrint", tr("Error: Select a valid COM port from the list."));
        canConnect = false;
    }

//    if (configIndex == -1 || (configIndex == 0 && !configList.at(0).exists())){
//        QMessageBox::information(this, "FabPrint", tr("Error: Select a valid printer configuration from the list."));
//        canConnect = false;
//    }

    if (canConnect||true){
        QSettings theSettings("Creative Machines Lab", "FabPrint");
        theSettings.setValue("load config next time index", ui->configBox->currentIndex());
        theSettings.sync();


        // LOAD THE FILE
//        QString config_path = configList.at(configIndex).filePath();
        QString config_path = "JrKerr-Single-deposition.config";
        QString configString;
        QDomDocument configDom;
        // load the config file into the DOM document
        {
          QFile configFile(config_path);
          if (!configFile.open(QFile::ReadOnly)) {
              printf("\nFAILED TO OPEN CONFIG FILE\n");
              return;
          }
          configDom.setContent(&configFile);
          configFile.close();
        }
        configString = configDom.toString();


        // ATTEMPT THE CONNECTION
        ci_->setConfig(configString,portList.at(portIndex));
        emit atemptConnect();
        /// Need an mechanism for checking errors
    }
}

void ConnectWidget::loading(bool load){
    ui->connectButton->setEnabled(load);
    ui->portBox->setEnabled(load);
    ui->configBox->setEnabled(load);
    ui->configButton->setEnabled(load);
}
