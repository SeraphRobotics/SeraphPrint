#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget.h"
#include "iostream"
#include <QMessageBox>


// Edit these stylesheets to change the appearance of the progress bar
#define ACTIVE "* { background-color: rgb(0,0,128); color: rgb(255,255,255); padding-top: 6px; padding-bottom: 6px}"
#define DONE "* { background-color: rgb(0,128,0); color: rgb(255,255,255) }"
#define INCOMPLETE "* { background-color: rgb(128,0,0); color: rgb(255,255,255) }"
enum
{
    CONNECT,
    JOB,
    MATERIALS,
    PRINT
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup Internal States
    ci_ = new CoreInterface();
    use_file_arg = false;
    haveValidFile = false;
    isConnected = false;


    // Setup UI
    ui->setupUi(this);
    current_state = 0;
    this->setWindowTitle("FabPrint");
    ui->connectButton->setStyleSheet(ACTIVE);
    ui->jobButton->setStyleSheet(INCOMPLETE);
    ui->materialsButton->setStyleSheet(INCOMPLETE);
    ui->printButton->setStyleSheet(INCOMPLETE);
    this->setGeometry(120, 120, 531, 260);
    this->setFixedSize(this->size());
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(forwardClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backClicked()));

    //    // Job widget
    //    connect(jobWidget, SIGNAL(sendAndLoadFile(QString)), this, SLOT(setFabFile(QString)));

    this->setUpWidgets();

    setUpConnections();
}

/**
 * This is an absolutely horrific kludge to get a
 * passable widget-switching inteface going by
 * Friday - will be updated to use a custom-
 * designed progress bar.
 */
void MainWindow::forwardClicked()
{
    if (current_state < 4)
    {
        current_state++;
        updateState();
    }
}

void MainWindow::backClicked()
{
    if (current_state > 0)
    {
        current_state--;
        updateState();
    }
}

/**
 * Add to the cases in this method to execute
 * transitions between widgets.  Widgets that
 * need to update MainWindow's state will need
 * to do so here.
 */
void MainWindow::updateState()
{
    ui->currentWidget->hide();

    // NOTE: If jumping around in the state is permitted, back and forward buttons must be enabled/disabled everywhere

    switch (current_state)
    {
    case CONNECT:
        ui->backButton->setEnabled(false);
        //ui->tempLabel->setText("[ Connect Widget ]");
        ui->currentWidget = connectWidget;
        enableOne(CONNECT);
        break;
    case JOB:
        ui->backButton->setEnabled(true);

        if (haveValidFile)
        {
            ui->forwardButton->setEnabled(true);
        }
        else
        {
            ui->forwardButton->setEnabled(false);
        }

        ui->currentWidget = jobWidget;
//        qDebug() << "About to call initial load...";

//        if (!haveValidFile)
//        {
//            jobWidget->doInitialLoad();
//        }

        enableOne(JOB);
        break;
    case MATERIALS:
        ui->forwardButton->setEnabled(true);
        ui->currentWidget = materialsWidget;
        enableOne(MATERIALS);
        break;
    case PRINT:
        ui->forwardButton->setEnabled(false);
        ui->currentWidget = printWidget;
        enableOne(PRINT);
        break;
    }
    ui->currentWidget->show();
}

// Yes, I know...
void MainWindow::enableOne(int newActiveButton)
{
    switch (newActiveButton)
    {
    case CONNECT:
        ui->connectButton->setStyleSheet(ACTIVE);
        ui->jobButton->setStyleSheet(INCOMPLETE);
        ui->materialsButton->setStyleSheet(INCOMPLETE);
        ui->printButton->setStyleSheet(INCOMPLETE);
        break;

    case JOB:
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(ACTIVE);
        ui->materialsButton->setStyleSheet(INCOMPLETE);
        ui->printButton->setStyleSheet(INCOMPLETE);
        break;

    case MATERIALS:
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(DONE);
        ui->materialsButton->setStyleSheet(ACTIVE);
        ui->printButton->setStyleSheet(INCOMPLETE);
        break;

    case PRINT:
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(DONE);
        ui->materialsButton->setStyleSheet(DONE);
        ui->printButton->setStyleSheet(ACTIVE);
        break;
    }
}
void MainWindow::setUpConnections()
{
    // Connect widget
        connect(connectWidget, SIGNAL(connectToPrinter(QString,QString)), this, SLOT(setPrinter(QString,QString)));

    //  Possible future use
    //  connect(this, SIGNAL(sendPreloadedConfig(QString)), connectWidget, SLOT(preloadConfig(QString)));

    // Gamepad widget
    connect(gamepad_container, SIGNAL(moveTo(double,double,double)), this, SLOT(moveHandler(double,double,double)));
    connect(gamepad_container, SIGNAL(setProperties(QString, double, double)), this, SLOT(propertiesHandler(QString, double, double)));

    // Materials widget
    connect(this, SIGNAL(sendBaysAndMaterials(int,QVector<string>)), materialsWidget, SLOT(initializeMaterials(int,QVector<string>)));
    connect(materialsWidget, SIGNAL(sendBayCommand(int,double,bool)), this, SLOT(setBayCommand(int,double,bool)));
    connect(materialsWidget, SIGNAL(sendBayMaterial(int,QString)), this, SLOT(setBayMaterial(int,QString)));

    // Print widget
    connect(printWidget, SIGNAL(go()), this, SLOT(setGo()));
    connect(printWidget, SIGNAL(pause()), this, SLOT(setPause()));
    connect(printWidget, SIGNAL(stop()), this, SLOT(setStop()));
    connect(printWidget, SIGNAL(resume()), this, SLOT(setResume()));
    connect(this, SIGNAL(sendCurrentPath(int)), printWidget, SLOT(setCurrentPath(int)));
    connect(this, SIGNAL(sendTotalPaths(int)), printWidget, SLOT(setTotalPaths(int)));
    //connect(&printInterface, SIGNAL(reportPrinterProgress(int,QString)), this, SLOT(getPrinterProgress(int,QString)));
    //connect(this, SIGNAL(reportPrinterProgress(int,QString)), printWidget, SLOT(getPrinterProgress(int,QString)));
}

void MainWindow::setUpWidgets()
{

    connectWidget = new ConnectWidget(this);

    //Job widget
    jobWidget = new JobWidget(this);
    jobWidget->hide();
//    if (use_file_arg)
//    {
//        jobWidget->preloadedFabFile();
//    }

    materialsWidget = new MaterialsWidget(this);
    materialsWidget->hide();

    printWidget = new PrintWidget(this);
    printWidget->hide();


    ui->currentWidget = connectWidget;

    gamepad_container = new GamePad(this);
    gamepad_container->move(0, 260);
    gamepad_container->hide();

}

void MainWindow::setUseFileArg(bool useit)
{
    use_file_arg = useit;
}

void MainWindow::setFileArg(QString theFile)
{
    use_file_arg = true;
    file_arg = theFile;
}

void MainWindow::setPrinter(QString port, QString config_path)
{
    cout << "In setPrinter slot" << std::endl;
    cout << "Config path: " << config_path.toStdString() << endl;

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

    ci_->setConfig(configString,port);

    if (ci_->vm_->isInitialized())
    {
        cout << "Config file loaded successfully" << std::endl;
//        QSettings settings("Creative Machines Lab", "FabPrint");
//        settings.setValue("config",config_path);
//        cout << settings.value("config").toString().toStdString() << std::endl;
//        settings.sync();
        this->setFixedHeight(471);
        this->setFixedWidth(531);
        gamepad_container->show();
        ui->forwardButton->setEnabled(true);
    }

    else
    {
        QMessageBox::information(this, "FabPrint", tr("Error: invalid config file"));
        isConnected = false;
    }

}

void MainWindow::setXDFLFile(QString xdfl_path)
{
    QString xdflString;
    QDomDocument xdflDom;
    // load the XDFL file into the DOM document
    {
      QFile xdflFile(xdfl_path);
      if (!xdflFile.open(QFile::ReadOnly)) {
          printf("\nFAILED TO OPEN XDFL FILE\n");
          return;
      }
      xdflDom.setContent(&xdflFile);
      xdflFile.close();
      xdflString = xdflDom.toString();
    }
    ci_->setXDFL(xdflString);
    printf("\nDomLoaded");
}

void MainWindow::setFabFile(QString fab_path)
{
    /*qDebug() << "In setFabFile; fab_path = " << fab_path;

    file_arg = fab_path; // Why are we even using the global variable here?

    if (printInterface.loadFabFile(file_arg))
    {
        emit sendBaysAndMaterials(printInterface.numLoadedBays(), printInterface.getMaterials());
        ui->forwardButton->setEnabled(true);
        haveValidFile = true;
    }
    else
    {
        QMessageBox::information(this, "FabPrint", tr("Error: invalid .fab or .xdfl file"));
        ui->forwardButton->setEnabled(false);
        haveValidFile = false;
    }*/
    return;
}

void MainWindow::setBayCommand(int bayNum, double distance, bool absolute)
{

    /*FIGURE OUT HOW TO MOVE A BAY BASED ON DISTANCE*/

    return;

}

void MainWindow::setBayMaterial(int bayNum, QString material)
{
    /*Not sure if this is the right function call*/
    /*How to get material from QString?*/

    /*Material mat;
    vm.bays[bayNum]->setMaterial(mat);*/

    return;
}

void MainWindow::getBayNum(int bayNum)
{
    /*DO WE EVER USE THIS?*/

    //emit sendBayPosition(printInterface.getBayPosition(bayNum));
}

void MainWindow::setGo()
{
    ci_->startPrint();

//    emit sendTotalPaths(handler->getNumCommands());
    // TODO: Use current/total path display (not implemented in Interface)
    // This will eventually require periodically polling the current path.

    this->setFixedHeight(260);

    this->gamepad_container->move(0, 260);
    this->materialsWidget->move(0, 0);
    this->materialsWidget->hide();
    this->gamepad_container->hide();
}

void MainWindow::setPause()
{
    ci_->pausePrint();

    this->setFixedHeight(612);

    this->gamepad_container->move(0, 400);
    this->materialsWidget->move(0, 200);
    this->materialsWidget->show();
    this->gamepad_container->show();

}

void MainWindow::setResume()
{
    ci_->resumePrint();

    this->setFixedHeight(260);

    this->gamepad_container->move(0, 260);
    this->materialsWidget->move(0, 0);
    this->materialsWidget->hide();
    this->gamepad_container->hide();
}

void MainWindow::setStop()
{
    ci_->forceStop();

    this->setFixedHeight(471);
    this->gamepad_container->move(0, 260);
    this->materialsWidget->move(0, 0);
    this->materialsWidget->hide();
    this->gamepad_container->show();
}

void MainWindow::moveHandler(double xPos, double yPos, double zPos) {
    ci_->move(xPos,yPos,zPos,30);
}

void MainWindow::propertiesHandler(QString motorname, double velocity, double acceleration) {
    //printInterface.setVelocity(motorname, velocity);
    //printInterface.setAcceleration(motorname, acceleration);
    return;
}

void MainWindow::getPrinterProgress(int currPath, QString status)
{
    //emit reportPrinterProgress(currPath, status);
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}
