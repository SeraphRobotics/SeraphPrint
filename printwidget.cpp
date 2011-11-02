#include "printwidget.h"
#include "ui_printwidget.h"

PrintWidget::PrintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintWidget)
{
    ui->setupUi(this);
    isPaused = true;
}

PrintWidget::~PrintWidget()
{
    delete ui;
}

// public slots
void PrintWidget::setCurrentPath(int num)
{
    currentPath = num;
    ui->label_info->setText("Printing path "
                            + QString::number(currentPath)+ " of "
                            + QString::number(totalPaths) + "...");
}
void PrintWidget::setTotalPaths(int num)
{
    totalPaths = num;
}

void PrintWidget::on_playButton_clicked()
{
    ui->stopButton->setEnabled(true);

    if (isPaused)
    {
        // Start/Resume print job
        emit go();

        // TODO ** Change icon to "pause"
        ui->playButton->setText("Pause");
    }
    else
    {
        emit pause();

        ui->label_info->setText("Paused on path "
                                + QString::number(currentPath)+ " of "
                                + QString::number(totalPaths) + ".");

        // TODO ** Change icon to "play"
        ui->playButton->setText("Resume");
    }
    isPaused = !isPaused;
}

void PrintWidget::on_stopButton_clicked()
{
    emit stop();

    ui->label_info->setText("Printing canceled.");

    // TODO ** Change icon to "play"
    ui->playButton->setText("Start");
    isPaused = true;
}
