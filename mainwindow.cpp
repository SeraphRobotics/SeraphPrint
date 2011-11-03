#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget.h"
//#include "Interface.h"


// Edit these stylesheets to change the appearance of the progress bar
#define ACTIVE "* { background-color: rgb(0,0,128); color: rgb(255,255,255); padding-top: 6px; padding-bottom: 6px }"
#define DONE "* { background-color: rgb(0,128,0); color: rgb(255,255,255) }"
#define INCOMPLETE "* { background-color: rgb(128,0,0); color: rgb(255,255,255) }"
enum
{
    CONNECT,
    JOB,
    MATERIALS,
    PRINT
};


int current_state = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->connectButton->setStyleSheet(ACTIVE);
    ui->jobButton->setStyleSheet(INCOMPLETE);
    ui->materialsButton->setStyleSheet(INCOMPLETE);
    ui->printButton->setStyleSheet(INCOMPLETE);

    // Note: wizard-style 'forward' and 'back' buttons will be superseded by an interactive progress bar
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(forwardClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backClicked()));
    //connect(ui, SIGNAL(sendBaysAndMaterials(int, QVector<string>)), materialsWidget, SLOT(initializeMaterials(int,QVector<std::string>)));
    this->setUpWidgets();
}

/**
 * This is an absolutely horiffic kludge to get a
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

    switch (current_state)
    {
    case CONNECT:
        ui->backButton->setEnabled(false);
        ui->tempLabel->setText("[ Connect Widget ]");
        ui->currentWidget = connectWidget;
        enableOne(CONNECT);
        break;
    case JOB:
        ui->backButton->setEnabled(true);
        ui->tempLabel->setText("[ Job Widget ]");
        ui->currentWidget = jobWidget;
        enableOne(JOB);
        break;
    case MATERIALS:
        ui->tempLabel->setText("[ Materials Widget ]");
        ui->currentWidget = materialsWidget;
        //emit sendBaysAndMaterials(printInterface.numLoadedBays(),printInterface.printer->bayMaterials);
        enableOne(MATERIALS);
        break;
    case PRINT:
        ui->forwardButton->setEnabled(true);
        ui->tempLabel->setText("[ Print Widget ]");
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

void MainWindow::setUpWidgets()
{

    connectWidget = new ConnectWidget(this);
    //connectWidget->move(this->geometry().center() - connectWidget->rect().center());

    jobWidget = new JobWidget(this);
    jobWidget->hide();
    //jobWidget->move(this->geometry().center() - jobWidget->rect().center());

    materialsWidget = new MaterialsWidget(this);
    materialsWidget->hide();
    //materialsWidget->move(this->geometry().center() - materialsWidget->rect().center());

    printWidget = new PrintWidget(this);
    printWidget->hide();
    //printWidget->move(this->geometry().center() - printWidget->rect().center());

    ui->tempLabel->hide();
    ui->currentWidget = connectWidget;
    //ui->gamepad = new GamePad
    GamePad* gamepad_container = new GamePad(this);
    gamepad_container->move(0, 350);

}

void MainWindow::setPrinter(QString port, QString config_path)
{
    printInterface.loadConfigFile(config_path, port);
}

void MainWindow::setFabFile(QString fab_path)
{
    printInterface.loadFabFile(fab_path);
}

void MainWindow::setBayCommand(int bayNum, double distance)
{
    printInterface.moveBayMotor(bayNum, distance);
}

void MainWindow::setMaterial(int bayNum, QString material)
{
    printInterface.equipMaterial(bayNum, material);
}

void MainWindow::setGo()
{
    printInterface.print();
}

void MainWindow::setPause()
{
    printInterface.pausePrint();
}

void MainWindow::setStop()
{
    printInterface.cancelPrint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
