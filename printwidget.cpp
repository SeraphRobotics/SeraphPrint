#include "printwidget.h"
#include "ui_printwidget.h"

PrintWidget::PrintWidget(QWidget *parent, CoreInterface *ci) :
    QWidget(parent),
    ui(new Ui::PrintWidget),
    currentPath(0),
    totalPaths(0),
    isPaused(true)
{
    ui->setupUi(this);

    ci_ = ci;

    connect(this,SIGNAL(go()),ci_,SLOT(startPrint()));
    connect(this,SIGNAL(pause()),ci_,SLOT(pausePrint()));
    connect(this,SIGNAL(stop()),ci_,SLOT(forceStop()));
    connect(this,SIGNAL(resume()),ci_,SLOT(resumePrint()));
    connect(this,SIGNAL(cancel()),ci_,SLOT(cancelPrint()));

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
    currentPath = 0;
    totalPaths = 0;
    isPaused = false;
    ui->pauseButton->setText("Pause");
    ui->stackedWidget->setCurrentIndex(0);
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

void PrintWidget::on_playButton_clicked(){
    // Start print job
    emit go();
    ui->stackedWidget->setCurrentIndex(1);
    isPaused=false;
}

void PrintWidget::on_cancelButton_clicked(){
    // Cancelling the print
    ui->label_info->setText("Printing canceled");
    emit cancel();
}

void PrintWidget::on_pauseButton_clicked(){
    if (!isPaused){// pausing the print
        emit pause();
        setPaused();
    }else{
        emit resume();
        ui->label_info->setText("Resuming");
        isPaused=false;
    }
}

void PrintWidget::on_stopButton_clicked(){
    //CALLED for forced stop, system is printing and isnt paused
    emit stop();
    ui->label_info->setText("FORCED STOP Please reconnect to the printer.");
}

void PrintWidget::getPrinterProgress(int currPath, QString status)
{
    currentPath = currPath;
    ui->label_progress->setText(status);
}


void PrintWidget::setPaused(){
    ui->pauseButton->setText("Resume");
    ui->label_info->setText("Paused");
    isPaused=true;
}

