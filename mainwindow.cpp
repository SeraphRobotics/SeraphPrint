#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget.h"
#include "iostream"
#include <QMessageBox>


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
    printf("state changed to %i",i);
    fflush(stdout);
    machineState = i;
    updateState();
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
    printf("\nCurrent State: %i",current_state);

    switch (current_state)
    {
    case CONNECT:

        if (machineState!=CoreInterface::NotInitialized){
            current_state = JOB;
            updateState();
        }else{
            ui->backButton->setEnabled(false);
            ui->currentWidget = connectWidget;
            enableOne(CONNECT);
        }
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
        enableOne(JOB);
        break;
    case MATERIALS:
        ui->forwardButton->setEnabled(true);
        ui->currentWidget = materialsWidget;
        materialsWidget->show();
        enableOne(MATERIALS);
        break;
//    case PRINT:
//        ui->forwardButton->setEnabled(false);
//        ui->currentWidget = printWidget;
//        enableOne(PRINT);
//        break;
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
    //CoreInterface
    connect(ci_,SIGNAL(stateChaged(int)),this,SLOT(onStateChaged(int)));

    // Print widget
    connect(printWidget, SIGNAL(go()), this, SLOT(setGo()));
    connect(printWidget, SIGNAL(pause()), this, SLOT(setPause()));
    connect(printWidget, SIGNAL(stop()), this, SLOT(setStop()));
    connect(printWidget, SIGNAL(resume()), this, SLOT(setResume()));
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

    gamepad_container = new GamePad(this,ci_);
    gamepad_container->move(0, 260);
    gamepad_container->hide();

    ui->currentWidget = connectWidget;

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
        printf("\nConfig file loaded successfully");
//        QSettings settings("Creative Machines Lab", "FabPrint");
//        settings.setValue("config",config_path);
//        cout << settings.value("config").toString().toStdString() << std::endl;
//        settings.sync();
        this->setFixedHeight(471);
        this->setFixedWidth(531);
        gamepad_container->show();
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
    this->gamepad_container->show();

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
