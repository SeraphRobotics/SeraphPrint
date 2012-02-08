#include "printwidget.h"
#include "ui_printwidget.h"

PrintWidget::PrintWidget(QWidget *parent, CoreInterface *ci) :
    QWidget(parent),
    ui(new Ui::PrintWidget),
    totalPaths(0),
    currentPath(0),
    isPrinting(false),
    isPaused(true)
{
    ui->setupUi(this);

    ci_ = ci;
    isPrinting = false;
    isPaused = true;

    connect(this,SIGNAL(go()),ci_,SLOT(startPrint()));
    connect(this,SIGNAL(pause()),ci_,SLOT(pausePrint()));
    connect(this,SIGNAL(stop()),ci_,SLOT(forceStop()));
    connect(this,SIGNAL(resume()),ci_,SLOT(resumePrint()));

    connect(ci_,SIGNAL(currentCommand(int)),this,SLOT(setCurrentPath(int)));
    connect(ci_,SIGNAL(estimated(double,double,int)),this,SLOT(estimated(double,double,int)));
    connect(ci_,SIGNAL(printsComplete()),this,SLOT(printDone()));

}

PrintWidget::~PrintWidget()
{
    delete ui;
}

void PrintWidget::printDone(){
    ui->label_info->setText("Done Printing");
//    ui->playButton->setText("Start");
    updateButtons();
    currentPath = 0;
    totalPaths = 0;
    isPrinting = false;
    isPaused = true;

}

void PrintWidget::estimated(double time, double volume, int numCmd){
    totalPaths = numCmd;
}

// public slots
void PrintWidget::setCurrentPath(int num){
    currentPath = num;
    ui->label_info->setText("Printing path "
                            + QString::number(currentPath)+ " of "
                            + QString::number(totalPaths) + "...");
}

void PrintWidget::setTotalPaths(int num){
    totalPaths = num;
}

void PrintWidget::on_playButton_clicked()
{
    ui->stopButton->setEnabled(true);

    if (isPrinting)
    {
        if (isPaused)
        {
            // Resume print job (!= Start print job)
            emit resume();
        }
        else
        {
            // pausing hte print
            emit pause();
            ui->label_info->setText("Paused.");
        }
        isPaused = !isPaused;
    }
    else
    {
        // Start print job
        emit go();
        isPrinting = true;
        isPaused = false;
    }
    updateButtons();
}

void PrintWidget::on_stopButton_clicked()
{
    if (isPrinting && !isPaused){
        //CALLED for forced stop, system is printing and isnt paused
        emit stop();
        ui->label_info->setText("FORCED STOP Please reconnect to the printer.");

        isPrinting = false;
        isPaused = true;
    }else{
        // Cancelling the print
        ui->label_info->setText("Printing canceled.");
        isPrinting = false;
        isPaused = true;
        emit cancel();
    }
    updateButtons();
}

void PrintWidget::getPrinterProgress(int currPath, QString status)
{
    currentPath = currPath;
    ui->label_progress->setText(status);
}

void PrintWidget::setPaused(){
    isPaused = false;
    isPrinting = true;
}

void PrintWidget::updateButtons(){
    if (isPrinting && isPaused)
    {
        //If the printer is printing and is paused, We
//        ui->label_info->setText("Paused...");
        ui->playButton->setText("Resume");
        ui->stopButton->setText("Cancel");
    }else if (isPrinting && !isPaused){
        ui->playButton->setText("Pause");
        ui->stopButton->setText("ForceStop");
    }else if (!isPrinting && isPaused){
        ui->playButton->setText("Pause");
        ui->stopButton->setText("ForceStop");

    }else if (!isPrinting && !isPaused){
        ui->playButton->setText("Start");
        ui->stopButton->setText("ForceStop");
    }
}
