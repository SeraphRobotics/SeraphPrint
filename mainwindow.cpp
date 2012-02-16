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
    // Setup Internal States
    ci_ = new CoreInterface();

    //Settings for Config file default directory path
    //Find OS specific app_data filepath
    QSettings ini(QSettings::IniFormat, QSettings::UserScope,
    QCoreApplication::organizationName(),
    QCoreApplication::applicationName());
    QString app_data_path = QFileInfo(ini.fileName()).absolutePath();

    //For Testing
    /*QSettings theSettings("Creative Machines Lab", "FabPrint");
    theSettings.clear();*/

    //Create new folder (if one does not exist) and store in default path variable
    QDir app_data_dir = QDir(app_data_path);
    app_data_dir.mkdir("FabAtHome");
    default_config_path = app_data_path + QString("/FabAtHome");

    // Setup UI
    ui->setupUi(this);
    this->setWindowTitle("FabPrint");
    ui->connectButton->setStyleSheet(ACTIVE);
    ui->jobButton->setStyleSheet(INCOMPLETE);
    ui->materialsButton->setStyleSheet(INCOMPLETE);
    ui->printButton->setStyleSheet(INCOMPLETE);
    this->setGeometry(120, 120, 531, 260);
    this->setFixedSize(this->size());
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(forwardClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backClicked()));

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

    if(!(ui->currentWidget->isHidden())){ui->currentWidget->hide();}

    // NOTE: If jumping around in the state is permitted, back and forward buttons must be enabled/disabled everywhere
    qDebug()<<"\nCurrent View State: "<<current_state;

    switch (current_state)
    {
    case CONNECT:
            ui->backButton->setEnabled(false);
            ui->currentWidget = connectWidget;
            enableOne(CONNECT);
        break;
    case JOB:
        ui->backButton->setEnabled(true);
        if (haveValidFile){
            ui->forwardButton->setEnabled(true);
        }
        else{
            ui->forwardButton->setEnabled(false);
        }
        ui->currentWidget = jobWidget;
        this->gamepad_container->show();
        enableOne(JOB);
        break;
    case MATERIALS:
        ui->forwardButton->setEnabled(true);
        ui->currentWidget = materialsWidget;
        materialsWidget->updateBays();
        this->gamepad_container->show();
        enableOne(MATERIALS);
        break;
    case PRINT:
        ui->forwardButton->setEnabled(false);
        ui->currentWidget = printWidget;
        enableOne(PRINT);
        this->gamepad_container->show();
        break;
    }
    ui->currentWidget->show();
    qDebug()<<"Current View State is now:"<<current_state;
}




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
    //CoreInterface
    connect(ci_,SIGNAL(stateChaged(int)),this,SLOT(onStateChaged(int)));
    connect(ci_,SIGNAL(needMaterialLoaded(int)),this,SLOT(materialNeeded(int)));
    connect(ci_,SIGNAL(printsComplete()),this,SLOT(printDone()));

    // Print widget
    connect(printWidget, SIGNAL(go()), this, SLOT(setGo()));
    connect(printWidget, SIGNAL(pause()), this, SLOT(setPause()));
    connect(printWidget, SIGNAL(stop()), this, SLOT(setStop()));
    connect(printWidget, SIGNAL(resume()), this, SLOT(setResume()));

    connect(this, SIGNAL(sendReloadConfigCommand()), connectWidget, SLOT(reLoadConfigFiles()));
}

void MainWindow::setUpWidgets()
{
    connectWidget = new ConnectWidget(this,ci_);

    //Job widget
    jobWidget = new JobWidget(this, ci_);
    jobWidget->hide();
//    if (use_file_arg)
//    {
//        jobWidget->preloadedFabFile();
//    }
    materialsWidget = new MaterialsWidget(this,ci_);
    materialsWidget->hide();

    printWidget = new PrintWidget(this,ci_);
    printWidget->hide();

    ui->currentWidget = connectWidget;

    gamepad_container = new GamePad(this,ci_);
    gamepad_container->move(0, 260);
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
}

void MainWindow::printerConnected(){

    if (ci_->vm_->isInitialized())
    {
        qDebug()<<"Config file loaded successfully";
//        QSettings settings("Creative Machines Lab", "FabPrint");
//        settings.setValue("config",config_path);
//        cout << settings.value("config").toString().toStdString() << std::endl;
//        settings.sync();
        this->setFixedHeight(471);
        this->setFixedWidth(531);
        this->gamepad_container->show();
        ui->forwardButton->setEnabled(true);
        isConnected = true;
    }

    else
    {
        QMessageBox::information(this, "FabPrint", tr("Error: invalid config file"));
        isConnected = false;
    }

}

void MainWindow::setGo()
{
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

    this->setFixedHeight(612);

    this->gamepad_container->move(0, 400);
    this->materialsWidget->move(0, 200);
    this->materialsWidget->show();
    this->gamepad_container->hide();//show();

}

void MainWindow::setResume()
{

    this->setFixedHeight(260);

    this->gamepad_container->move(0, 260);
    this->materialsWidget->move(0, 0);
    this->materialsWidget->hide();
    this->gamepad_container->hide();
}

void MainWindow::setStop()
{
    this->setFixedHeight(471);
    this->gamepad_container->move(0, 260);
    this->materialsWidget->move(0, 0);
    this->materialsWidget->hide();
    this->gamepad_container->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionChange_Directory_triggered()
{ 
    //Change the default directory for config files using a file chooser dialog
    QSettings theSettings("Creative Machines Lab", "FabPrint");
    QString current_path = (theSettings.value("config_dir", default_config_path)).toString();
    QString new_path = QFileDialog::getExistingDirectory(this, tr("Directory"), current_path);

    /*As long as the user does not press "cancel", change the path*/
    if (!new_path.isNull())
    {
       theSettings.setValue("config_dir", new_path);
       theSettings.sync();
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
    QDesktopServices::openUrl(QUrl("http://www.fabathome.org/"));
}
