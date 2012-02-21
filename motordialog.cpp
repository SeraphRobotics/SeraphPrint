#include "motordialog.h"
#include "ui_motordialog.h"

QString motorId;

motordialog::motordialog(QWidget *parent, QString direction, double vel, double accel, bool checked) :
    QDialog(parent),
    ui(new Ui::motordialog)
{
    ui->setupUi(this);
    //fields
    this->setWindowTitle("Edit Motor");
    ui->motorLabel_2->setText(direction + " Motor");
    ui->velocitySlider_2->setValue(vel);
    ui->accelerationSlider_2->setValue(accel);
    ui->velocitySpin_2->setValue(vel);
    ui->accelerationSpin_2->setValue(accel);
//    ui->reverseCheckButton->setChecked(checked);
//    ui->reverseCheckButton->hide();
    motorId = direction;

    //signals / slots
    connect(ui->velocitySlider_2, SIGNAL(valueChanged(int)), this, SLOT(onVelSlider_Changed()));
    connect(ui->velocitySpin_2, SIGNAL(valueChanged(double)), this, SLOT(onVelBox_Changed()) );
    connect(ui->accelerationSlider_2, SIGNAL(valueChanged(int)), this, SLOT(onAccelSlider_Changed()));
    connect(ui->accelerationSpin_2, SIGNAL(valueChanged(double)), this, SLOT(onAccelBox_Changed()) );

}
void motordialog::onVelSlider_Changed() {

    double newVal = (double) ui->velocitySlider_2->value();
    ui->velocitySpin_2->setValue(newVal);

}
void motordialog::onVelBox_Changed() {

    int newVal = (int) ui->velocitySpin_2->value();
    ui->velocitySlider_2->setValue(newVal);

}
void motordialog::onAccelSlider_Changed() {

    double newVal = (double) ui->accelerationSlider_2->value();
    ui->accelerationSpin_2->setValue(newVal);

}
void motordialog::onAccelBox_Changed() {

    int newVal = (int) ui->accelerationSpin_2->value();
    ui->accelerationSlider_2->setValue(newVal);

}

void motordialog::on_okButton_clicked()
{
    emit setProperties(motorId, ui->velocitySpin_2->value(), ui->accelerationSpin_2->value());
    this->close();
}

void motordialog::closeEvent(QCloseEvent *)
{
    emit closed();
}

motordialog::~motordialog()
{
    delete ui;
}


