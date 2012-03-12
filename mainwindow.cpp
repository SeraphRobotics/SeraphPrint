#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget.h"
#include "iostream"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
// for opening web browser
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

#include "qextserialenumerator.h"


// Edit these stylesheets to change the appearance of the progress bar
#define ACTIVE "* { background-color: rgb(0,0,128); color: rgb(255,255,255); padding-top: 6px; padding-bottom: 6px}"
#define DONE "* { background-color: rgb(0,128,0); color: rgb(255,255,255) }"
#define INCOMPLETE "* { background-color: rgb(128,0,0); color: rgb(255,255,255) }"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_state(CONNECT),
    file_arg(""),
    use_file_arg(false),
    haveValidFile(false),
    isConnected(false),
    materialsInitialized(false),
    machineState(0)
{
    QDateTime curdt = QDateTime::currentDateTime();
    QDateTime settime = QDateTime(QDate::fromString("12:06:2012", "d':'MM':'yyyy"),QTime(0,0));

    if (curdt>settime){
      QMessageBox::information(this->centralWidget(),"info","Your version has expired. please contact Seraph Robotics");
      QTimer::singleShot(0,this,SLOT(close()));
    }


    // Setup Internal States
    ci_ = new CoreInterface();

    // Settings for config file default directory path
    // Find OS-specific app_data filepath
    // QSettings constructor values were specified in main.cpp.
    QSettings settings;
    QString app_data_path = QFileInfo(settings.fileName()).absolutePath();
    enumerator = new QextSerialEnumerator();
    //Create new folder (if one does not exist) and store in default path variable
    QDir app_data_dir = QDir(app_data_path);
    app_data_dir.mkdir("Seraph");

    default_config_path = app_data_path ;//+ QString("/Seraph");
    default_config_path = QDir::toNativeSeparators(default_config_path);

    if(!QDir(default_config_path).exists()){
        QDir().mkdir(default_config_path);
    }


    // Setup UI
    ui->setupUi(this);
    this->setWindowTitle("SeraphPrint");
    ui->connectButton->setStyleSheet(ACTIVE);
    ui->jobButton->setStyleSheet(INCOMPLETE);
    ui->materialsButton->setStyleSheet(INCOMPLETE);
    ui->printButton->setStyleSheet(INCOMPLETE);
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(forwardClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backClicked()));


    ui->menuBar->setEnabled(true);
    this->setUpWidgets();

    setUpConnections();
    this->enumerator->setUpNotifications();
}


/**
 * This is an absolutely horrific kludge to get a
 * passable widget-switching inteface going by
 * Friday - will be updated to use a custom-
 * designed progress bar.
 */
void MainWindow::forwardClicked(){
    if (current_state < 4){
        current_state++;
        updateState();
    }
}

void MainWindow::backClicked(){
    if (current_state > 0){
        current_state--;
        updateState();
    }
}


void MainWindow::onStateChaged(int i){
    qDebug()<<"Machine State changed to "<<i;
    machineState = i;
    if(i==CoreInterface::NotInitialized){
        current_state=0;
        haveValidFile = false;
        isConnected = false;
        materialsInitialized = false;
    }else if (i==CoreInterface::Connected){
        printerConnected();
        qDebug()<<"Connected...";
        haveValidFile = false;
        isConnected = true;
        materialsInitialized = false;
    }else if(i==CoreInterface::FileLoaded){
        qDebug()<<"File Loaded...";
        haveValidFile = true;
        isConnected = true;
        materialsInitialized = false;
    }else if(i==CoreInterface::Printing){
        qDebug()<<"Printing...";
        haveValidFile = true;
        isConnected = true;
    }else{
        qDebug()<<"WTF"<<machineState;
    }
    updateState();
}

void MainWindow::materialNeeded(int){
    setPause();
    printWidget->setPaused();
}

/**
 * Add to the cases in this method to execute
 * transitions between widgets.  Widgets that
 * need to update MainWindow's state will need
 * to do so here.
 */
void MainWindow::updateState()
{

    // NOTE: If jumping around in the state is permitted, back and forward buttons must be enabled/disabled everywhere
    qDebug()<<"\nCurrent View State: "<<current_state;

    switch (current_state)
    {
    case CONNECT:
            ui->backButton->setEnabled(false);
            ui->connectButton->setStyleSheet(ACTIVE);
            ui->jobButton->setStyleSheet(INCOMPLETE);
            ui->materialsButton->setStyleSheet(INCOMPLETE);
            ui->printButton->setStyleSheet(INCOMPLETE);
        break;
    case JOB:
        ui->backButton->setEnabled(true);
        if (haveValidFile){
            ui->forwardButton->setEnabled(true);
        }
        else{
            ui->forwardButton->setEnabled(false);
        }
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(ACTIVE);
        ui->materialsButton->setStyleSheet(INCOMPLETE);
        ui->printButton->setStyleSheet(INCOMPLETE);
        break;
    case MATERIALS:
        ui->forwardButton->setEnabled(true);
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(DONE);
        ui->materialsButton->setStyleSheet(ACTIVE);
        ui->printButton->setStyleSheet(INCOMPLETE);
        this->materialsWidget->show();
        break;
    case PRINT:
        ui->forwardButton->setEnabled(false);
        ui->connectButton->setStyleSheet(DONE);
        ui->jobButton->setStyleSheet(DONE);
        ui->materialsButton->setStyleSheet(DONE);
        ui->printButton->setStyleSheet(ACTIVE);
        break;
    }
    ui->stackedWidget->setCurrentIndex(current_state);
    showGamePad();
}

void MainWindow::terminate(){
    // Todo: end app or deal with lack of printer here.

    qDebug() << "Attempting shutdown.";
    if(current_state != CONNECT){
        abort();
    }
}


void MainWindow::setUpConnections()
{
    //COMPORTS
    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)),connectWidget,SLOT(deviceAdded(QextPortInfo)));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)),connectWidget,SLOT(deviceRemoved(QextPortInfo)));
    connect(connectWidget,SIGNAL(mainDeviceRemoved()),this,SLOT(terminate()));
    //CoreInterface
    connect(ci_,SIGNAL(stateChaged(int)),this,SLOT(onStateChaged(int)));
    connect(ci_,SIGNAL(needMaterialLoaded(int)),this,SLOT(materialNeeded(int)));
    connect(ci_,SIGNAL(printsComplete()),this,SLOT(printDone()));

    // Print widget
    connect(printWidget, SIGNAL(go()), this, SLOT(setGo()));
    connect(printWidget, SIGNAL(pause()), this, SLOT(setPause()));
    connect(printWidget, SIGNAL(stop()), this, SLOT(setStop()));
    connect(printWidget, SIGNAL(cancel()), this, SLOT(setStop()));
    connect(printWidget, SIGNAL(resume()), this, SLOT(setResume()));


    connect(this, SIGNAL(sendReloadConfigCommand()), connectWidget, SLOT(reLoadConfigFiles()));
}

void MainWindow::setUpWidgets()
{
    connectWidget = new ConnectWidget(this,ci_);
    jobWidget = new JobWidget(this, ci_);
    materialsWidget = new MaterialsWidget(this,ci_);
    printWidget = new PrintWidget(this,ci_);

    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());

    ui->stackedWidget->insertWidget(CONNECT,connectWidget);
    ui->stackedWidget->insertWidget(JOB,jobWidget);
    ui->stackedWidget->insertWidget(MATERIALS,materialsWidget);
    ui->stackedWidget->insertWidget(PRINT,printWidget);

    gamepad_container = new GamePad(this,ci_);

    gamepad_container->hide();
}

void MainWindow::printDone(){
    if((current_state !=JOB)&&(current_state !=CONNECT)){
        current_state = JOB;
        QMessageBox::information(this,"Print Complete","Your print has finished");
        updateState();
    }
}

void MainWindow::setUseFileArg(bool useit)
{
    use_file_arg = useit;
}

void MainWindow::setFileArg(QString theFile)
{
    use_file_arg = true;
    file_arg = theFile;
    QSettings settings;
    settings.setValue("last used fab file", theFile);
    settings.sync();
    jobWidget->updatePreloadedFabFile();
}

QString MainWindow::getFileArg(){
    if(use_file_arg){return file_arg;}
    else{return QString("");}
}

void MainWindow::printerConnected(){

    if (ci_->vm_->isInitialized())
    {
        qDebug()<<"Config file loaded successfully";
        showGamePad();
        ui->forwardButton->setEnabled(true);
        isConnected = true;
    }

    else
    {
        QMessageBox::information(this, "SeraphPrint", tr("Error: invalid config file"));
        isConnected = false;
    }

}


void MainWindow::hideGamePad(){
    this->gamepad_container->hide();
    ui->mainVLayout->removeWidget(this->gamepad_container);
}

void MainWindow::showGamePad(){
    this->gamepad_container->show();
    ui->mainVLayout->addWidget(this->gamepad_container);
}

void MainWindow::setGo()
{
    // TODO: Use current/total path display (not implemented in Interface)
    // This will eventually require periodically polling the current path.
    hideGamePad();
}

void MainWindow::setPause()
{
    ui->mainVLayout->addWidget(this->materialsWidget);
    this->materialsWidget->show();
}

void MainWindow::setResume()
{
    ui->mainVLayout->removeWidget(this->materialsWidget);
    this->materialsWidget->hide();
}

void MainWindow::setStop()
{
    showGamePad();
    ui->mainVLayout->removeWidget(this->materialsWidget);
    this->materialsWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Changes default config file directory
void MainWindow::on_actionChange_Directory_triggered()
{ 
    // Change the default directory for config files using a file chooser dialog
    // QSettings constructor values were specified in main.cpp.
    QSettings settings;
    QString current_path = (settings.value("config_dir", default_config_path)).toString();
    QString new_path = QFileDialog::getExistingDirectory(this, tr("Directory"), current_path);

    /*As long as the user does not press "cancel", change the path*/
    if (!new_path.isNull())
    {
       settings.setValue("config_dir", new_path);
       settings.sync();
    }

    //Signal to connectwidget to reload config files in drop down
    sendReloadConfigCommand();
}

void MainWindow::on_actionAbout_FabPrint_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionVisit_FabAtHome_org_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.seraphrobotics.com/"));
}
