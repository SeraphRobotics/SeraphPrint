#include "connectwidget.h"
#include "ui_connectwidget.h"
#include <QFileDialog>
#include <QMessageBox>

ConnectWidget::ConnectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);
    // Populate portBox
    // ui->portBox->addItems(QStringList &texts);
    port = "";
    //QList qse.getPorts();
}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

// public slot
void ConnectWidget::preloadConfig(QString preloaded_path)
{
    config_path = preloaded_path;
}

void ConnectWidget::on_portBox_currentIndexChanged(QString text)
{
    port = text;
}

void ConnectWidget::on_configBox_currentIndexChanged(QString text)
{
    config_path = text;
}

void ConnectWidget::on_configButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
        "", tr("Printer Config File (*.config);;All Files (*.*)"));
    if (!filename.isEmpty()) {
        int newIndex = ui->configBox->count();
        ui->configBox->insertItem(newIndex, filename);
        ui->configBox->setCurrentIndex(newIndex); // Make sure this line causes currentIndexChanged to fire!
    }
}

void ConnectWidget::on_connectButton_clicked()
{
    if (!port.isEmpty() && !config_path.isEmpty()) {
        emit connectToPrinter(port, config_path);
    }
    else {
        if (port.isEmpty())
            QMessageBox::information(
                this,
                "FabPrint",
                tr("Error: Select a valid COM port from the list.") );
        if (config_path.isEmpty())
            QMessageBox::information(
                this,
                "FabPrint",
                tr("Error: Select a valid printer configuration from the list.") );
    }
}
