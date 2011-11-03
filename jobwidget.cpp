#include "jobwidget.h"
#include "ui_jobwidget.h"
#include <QFileDialog>

JobWidget::JobWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobWidget)
{
    ui->setupUi(this);
}

JobWidget::~JobWidget()
{
    delete ui;
}

// public slot
void JobWidget::preloadedFabFile()
{
    ui->label_fileL->setVisible(false);
    ui->label_file->setVisible(false);
    ui->browseButton->setVisible(false);
}


void JobWidget::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
        "", tr("FAB/XDFL Files (*.fab *.xdfl);;All Files (*.*)"));
    if (!filename.isEmpty()) {
        ui->label_file->setText(filename);
        fab_path = filename;
        emit loadFabFile(fab_path);

        // Calculate time/volume/dimensions
        // ui->label_time  ->setText(...);
        // ui->label_volume->setText(...);
        // ui->label_dimY  ->setText(...);
    }
}
