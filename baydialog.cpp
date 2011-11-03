#include "baydialog.h"
#include "ui_baydialog.h"

BayDialog::BayDialog(QWidget *parent, QString bayName) :
    QDialog(parent),
    ui(new Ui::BayDialog)
{
    ui->setupUi(this);
    ui->bayLabel->setText(bayName);
    this->setWindowTitle("Edit Bay");
}

BayDialog::~BayDialog()
{
    delete ui;
}

void BayDialog::on_moveButton_clicked()
{
    QString bayName = ui->bayLabel->text().at(ui->bayLabel->text().length()-1);
    int bayNum = bayName.toInt();
    emit moveBay(bayNum, ui->commandSpin->value());
}

void BayDialog::on_acceptButton_clicked()
{
    this->close();
}

void BayDialog::on_upButton_released()
{
    int currentCommand = ui->commandSpin->value();
    int increment = ui->incrementSpin->value();
    ui->commandSpin->setValue(currentCommand-increment);
    ui->positionSpin->setValue(currentCommand-increment);
}

void BayDialog::on_downButton_released()
{
    int currentCommand = ui->commandSpin->value();
    int increment = ui->incrementSpin->value();
    ui->commandSpin->setValue(currentCommand+increment);
    ui->positionSpin->setValue(currentCommand+increment);
}
