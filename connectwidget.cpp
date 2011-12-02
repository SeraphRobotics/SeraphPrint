#include "connectwidget.h"
#include "ui_connectwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "JrkerrElectronics/Posix/qextserial/qextserialenumerator.h"
#include <QDebug>
#include <iostream>
#include <QDir>
#include <QSettings>

#define FAB_CONFIG_DIRECTORY_NAME_UNIX ".fab_configs"
#define FAB_CONFIG_DIRECTORY_NAME_WIN "Fab Configs"

ConnectWidget::ConnectWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);

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

        // Create the directory if it doesn't already exist
        verifyDirectoryExistsCommand += "mkdir -p \"";
        verifyDirectoryExistsCommand += configFileDirectory.absolutePath();
        verifyDirectoryExistsCommand += "\"";
        qDebug() << "Existence confirmation: " << verifyDirectoryExistsCommand;
    }
    else
    {
        configFileDirectory = QDir(QDir::homePath() + "\\" + FAB_CONFIG_DIRECTORY_NAME_WIN);

        // Code to make sure the directory exists on Windows...
        // configFileDirectory = whatever I want it to be on Windows
    }

    system(verifyDirectoryExistsCommand.toStdString().c_str());

    loadFiles();

    QSettings theSettings("Creative Machines Lab", "FabPrint");
    ui->configBox->setCurrentIndex(theSettings.value("load config next time index", 0).toInt());

////    qDebug() << "This is the directory from which .config files will be pulled for the combo box:";
////    qDebug() << QCoreApplication::applicationDirPath();

//    configList = appdir.entryInfoList(QStringList("*.config"), QDir::Files);

////    // Add a blank entry to index 0 for a custom user-specified file.
////    configList.prepend(QFileInfo());

//    // FROM THIS POINT ON, configList and configBox ENTRIES SHOULD STAY IN ORDER!

//    foreach(QFileInfo config, configList)
//    {
//        ui->configBox->addItem(config.baseName());
//    }

//    ui->configBox->setItemText(0, "n/a (Custom)");

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
    foreach(QFileInfo config, configList)
    {
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
    QString sysCopyCommand;

    if (true /* OS is UNIX-like */)
    {
        sysCopyCommand = "cp \"" + path + "\" \"" + configFileDirectory.absolutePath() + "\"";
    }
    else
    {
        sysCopyCommand = "copy " + path + " " + configFileDirectory.absolutePath();
    }

    if (!path.isEmpty())
    {
        qDebug() << "Adding config file: " << sysCopyCommand;

        system(sysCopyCommand.toStdString().c_str());
    }
}

/*
 Public slot to preload a remembered configuration file.
 */
//void ConnectWidget::preloadConfig(QString preloaded_path)
//{
//    addConfig(preloaded_path);
//}

void ConnectWidget::on_configButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open"),
    QDir::homePath(), tr("Printer Config File (*.config);;All Files (*.*)"));
    addConfig(filepath); // addConfig should do the file copy/move
    loadFiles();

    // TODO: the chooser dialog starts in the last-used directory instead of the home folder
}

void ConnectWidget::on_connectButton_clicked()
{
    int portIndex   = ui->portBox  ->currentIndex();
    int configIndex = ui->configBox->currentIndex();
    bool canConnect = true;

    if (portIndex == -1)
    {
        QMessageBox::information(this, "FabPrint", tr("Error: Select a valid COM port from the list."));
        canConnect = false;
    }

    if (configIndex == -1 || (configIndex == 0 && !configList.at(0).exists()))
    {
        QMessageBox::information(this, "FabPrint", tr("Error: Select a valid printer configuration from the list."));
        canConnect = false;
    }

    if (canConnect)
    {
        // aen27, 30 November 2011
        ui->connectButton->setEnabled(false);
        ui->portBox->setEnabled(false);
        ui->configBox->setEnabled(false);
        ui->configButton->setEnabled(false);

        QSettings theSettings("Creative Machines Lab", "FabPrint");
        theSettings.setValue("load config next time index", ui->configBox->currentIndex());
        theSettings.sync();

        emit connectToPrinter(portList.at(portIndex), configList.at(configIndex).filePath());
    }
}
