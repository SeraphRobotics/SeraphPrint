#include "connectwidget.h"
#include "ui_connectwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "qextserialenumerator.h"
#include <QDebug>
#include <iostream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#define FAB_CONFIG_DIRECTORY_NAME_UNIX ".fab_configs"
#define FAB_CONFIG_DIRECTORY_NAME_WIN "Fab Configs"

ConnectWidget::ConnectWidget(QWidget *parent, CoreInterface *ci) : QWidget(parent), ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);
    ci_ = ci;

    // Set up default directory
    // Settings for Config file default directory path
    // Find OS specific app_data filepath
    // QSettings constructor values were specified in main.cpp.
    QSettings settings;
    default_config_path = QFileInfo(settings.fileName()).absolutePath();//+ "/Seraph"

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

        bool usb = port.friendName.contains("usb",Qt::CaseInsensitive);

        if (usb)//!port.friendName.isEmpty())
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
    // The selected config path is retrieved by configList.at(ui->configBox->currentIndex()).

    QString verifyDirectoryExistsCommand;

    // Find the config directory from QSettings
    configFileDirectory = QDir(settings.value("config_dir", default_config_path).toString());

    system(verifyDirectoryExistsCommand.toStdString().c_str());

    loadFiles();

    ui->configBox->setCurrentIndex(settings.value("load config next time index", 0).toInt());

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
    configList = configFileDirectory.entryInfoList(QStringList("*.config"), QDir::Files);

    //std::cout << configList.at(0).absoluteFilePath().toStdString() << std::endl;
    // Clear the entries currently in the config combo box
    ui->configBox->clear();

    // If there are no config files, disable deletion
    if (configList.isEmpty()) {
        ui->deleteButton->setEnabled(false);
    }
    else {
        ui->deleteButton->setEnabled(true);

        // Add all of the files from the configList to the combo box
        foreach(QFileInfo config, configList){
            ui->configBox->addItem(config.baseName());
        }
    }

    ui->configBox->setCurrentIndex(0);
}


/**
 Slots for COM port detection.

 deviceAdded(QextPortInfo) responds to the presence of a newly detected COM port.
 deviceRemoved(QextPortInfo) responds to the removal of a previously detected COM port.
 **/

void ConnectWidget::deviceAdded(QextPortInfo i){
    qDebug() << "Device added named: " + i.portName + ". Calling response code.";

    bool usb = i.friendName.contains("usb",Qt::CaseInsensitive);

    if (usb)//!port.friendName.isEmpty())
    {
        portList.append(i.portName);
        ui->portBox->addItem(i.friendName);
        /**
            TODO: Check for duplicates
        **/
    }
}

void ConnectWidget::deviceRemoved(QextPortInfo i){
    qDebug()<<"Device removed named: " + i.portName + ". Calling response code.";
    bool usb = i.friendName.contains("usb",Qt::CaseInsensitive);

    if (usb)//!port.friendName.isEmpty())
    {

        portList.removeAt(portList.indexOf(i.portName));
        ui->portBox->removeItem(ui->portBox->findText(i.friendName));
        /**
            TODO: Alert other stages to changes, display warning of some kind.
        **/
        if(i.portName == portName){
            mainDeviceRemoved();
        }
    }
}

/**
  End of comport detection slots.
  */


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
            qDebug()<<"Error copying the code.";
        }

    }
    else{
        qDebug()<<"Error opening the file.";
    }
}

void ConnectWidget::removeConfig(QString path)
{
    QFile::remove(path);
    loadFiles();
}

/*
 Public slot to preload a remembered configuration file.
 */
/*void ConnectWidget::preloadConfig(QString preloaded_path)
{
    addConfig(preloaded_path);
}*/

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



    if ((portIndex == -1)||(portList.isEmpty())){
        QMessageBox::information(this, "SeraphPrint", tr("Error: Select a valid COM port from the list."));
        canConnect = false;
    }

    if (configIndex == -1 || configList.isEmpty()){//(configIndex == 0 && !configList.at(0).exists())){
        QMessageBox::information(this, "SeraphPrint", tr("Error: Select a valid printer configuration from the list."));
        canConnect = false;
    }

    if (canConnect){
        QSettings theSettings("Creative Machines Lab", "SeraphPrint");
        theSettings.setValue("load config next time index", ui->configBox->currentIndex());
        theSettings.sync();
		
        // LOAD THE FILE
        QString config_path = configList.at(configIndex).filePath();
//        QString config_path = "JrKerr-Single-deposition.config";
        qDebug() << "Loading: " + config_path;
        QString configString;
        QDomDocument configDom;
        // load the config file into the DOM document
        {
          QFile configFile(config_path);
          if (!configFile.open(QFile::ReadOnly)) {
              qDebug() << "Failed to open config file.";
              QMessageBox::warning(this,tr("Config Error"),tr("Cound not open config file"));
              return;
          }
          configDom.setContent(&configFile);
          configFile.close();
        }

        qDebug() << "Configuring config";
        configString = configDom.toString();
        qDebug() << "Configuring port";
        portName = portList.at(portIndex);

        // ATTEMPT THE CONNECTION

        qDebug() << "Attempting connection";
        ci_->setConfig(configString,portName);
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

//Deletes a config file upon user request
void ConnectWidget::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("The currently selected configuration will be permanently deleted.");
    msgBox.setInformativeText("Are you sure you want to delete?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ans = msgBox.exec();

    switch (ans)
    {
       case QMessageBox::Yes:
       {
           // Yes was clicked
           int configIndex = ui->configBox->currentIndex();
           QString config_path = configList.at(configIndex).filePath();
           removeConfig(config_path);
           break;
       }
       default:
           // Cancel or close button was clicked
           break;
     }
}

//reloads config files after user changes the default config file directory
void ConnectWidget::reLoadConfigFiles()
{
    // QSetting to grab config directory
    // QSettings constructor values were specified in main.cpp.
    QSettings settings;
    configFileDirectory = QDir(settings.value("config_dir", default_config_path).toString());
    loadFiles();
}
