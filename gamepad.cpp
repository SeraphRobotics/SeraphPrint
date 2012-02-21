#include "gamepad.h"
#include "ui_gamepad.h"
#include "motordialog.h"
#include <stdio.h>
#include <QKeyEvent>

// TODO: Replace the Position text boxes with labels, which is really what they should be

GamePad::GamePad(QWidget *parent,CoreInterface* ci) :
    QWidget(parent),
    ui(new Ui::GamePad)
{
    ui->setupUi(this);
    ci_ = ci;

    //initialization of variables
    XVelocity = 100.0;
    XAcceleration = 100.0;
    YVelocity = 100.0;
    YAcceleration = 100.0;
    ZVelocity = 100.0;
    ZAcceleration = 100.0;

    xOpen = false;
    yOpen = false;
    zOpen = false;

    //update the position fields
    connect(ci_,SIGNAL(currentPosition(double,double,double)),this,SLOT(onPositionChanged(double,double,double)));

}


GamePad::~GamePad()
{
    delete ui;
}

void GamePad::onMotorChanged(QString motorname, double velocity, double acceleration) {
   if (motorname == "X") {

       XVelocity = velocity;
       XAcceleration = acceleration;
   }
   else if (motorname == "Y"){
       YVelocity = velocity;
       YAcceleration = acceleration;
   }
   else if (motorname == "Z") {
       ZVelocity = velocity;
       ZAcceleration = acceleration;
   }
}




void GamePad::on_xLaunchButton_clicked()
{
    if (! xOpen){
    xOpen = true;
    motordialog* dialog = new motordialog(this,"X", XVelocity, XAcceleration,false);
    dialog->show();
    connect(dialog, SIGNAL(setProperties(QString,double,double)), this, SLOT(onMotorChanged(QString, double, double)));
    connect(dialog, SIGNAL(closed()), this, SLOT(onXDialogDes()));
    }
}

void GamePad::on_yLaunchButton_clicked()
{
    if (! yOpen)
    {
        yOpen = true;
        motordialog* dialog = new motordialog(this,"Y",YVelocity, YAcceleration,false);
        dialog->show();
        connect(dialog, SIGNAL(setProperties(QString,double,double)), this, SLOT(onMotorChanged(QString, double, double)));
        connect(dialog, SIGNAL(closed()), this, SLOT(onYDialogDes()));
    }
}

void GamePad::on_zLabelButton_clicked()
{
    if (! zOpen)
    {
        zOpen = true;
        motordialog* dialog = new motordialog(this,"Z",ZVelocity, ZAcceleration,false);
        dialog->show();
        connect(dialog, SIGNAL(setProperties(QString,double,double)), this, SLOT(onMotorChanged(QString, double, double)));
        connect(dialog, SIGNAL(closed()), this, SLOT(onZDialogDes()));
    }
}

void GamePad::onXDialogDes()
{
    xOpen = false;
}
void GamePad::onYDialogDes()
{
    yOpen = false;
}
void GamePad::onZDialogDes()
{
    zOpen = false;
}


void GamePad::on_toOriginButton_clicked()
{
    //move to origin
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity+ZVelocity*ZVelocity);
    ci_->moveTo(0,0,0,v);
}

void GamePad::on_originButton_clicked()
{
    //setting origin
    ui->xPositionSpin->setValue(0);
    ui->yPositionSpin->setValue(0);
    ui->zPositionSpin->setValue(0);
    ci_->resetPosition();
}


void GamePad::on_moveButton_clicked()
{
    //move to commanded
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity+ZVelocity*ZVelocity);
    ci_->moveTo(ui->xCommandSpin->value(), ui->yCommandSpin->value(), ui->zCommandSpin->value(),v);
}

void GamePad::onPositionChanged(double xPos, double yPos, double zPos) {
    ui->xPositionSpin->setValue(xPos);
    ui->yPositionSpin->setValue(yPos);//ui->yPositionSpin->value() +
    ui->zPositionSpin->setValue(zPos);

}

void GamePad::on_upPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value());
    ci_->move(-ui->xIncrementSpin->value(), 0, 0,XVelocity);
}

void GamePad::on_downPushbutton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value());
    ci_->move(ui->xIncrementSpin->value(), 0, 0,XVelocity);
}

void GamePad::on_leftPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    ci_->move(0, - ui->yIncrementSpin->value(), 0, YVelocity);
}

void GamePad::on_rightPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    ci_->move(0, ui->yIncrementSpin->value(), 0, YVelocity);
}
void GamePad::on_minusZPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value() - ui->zIncrementSpin->value());
    ci_->move(0, 0,- ui->zIncrementSpin->value(),ZVelocity);
}

void GamePad::on_plusZPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value() + ui->zIncrementSpin->value());
    ci_->move(0, 0, ui->zIncrementSpin->value(),ZVelocity);
}


void GamePad::on_urPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity);
    ci_->move(- ui->xIncrementSpin->value(), ui->yIncrementSpin->value(),0,v);
}

void GamePad::on_ulPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity);
    ci_->move(- ui->xIncrementSpin->value(), -ui->yIncrementSpin->value(),0,v);
}



void GamePad::on_dlPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(),
      //          ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity);
    ci_->move(ui->xIncrementSpin->value(), -ui->yIncrementSpin->value(), 0,v);
}

void GamePad::on_drpushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    double v = sqrt(XVelocity*XVelocity+YVelocity*YVelocity);
    ci_->move(ui->xIncrementSpin->value(), ui->yIncrementSpin->value(), 0,v);
}



void GamePad::on_xIncrementSpin_editingFinished()
{
    this->setFocus();
}

void GamePad::on_xCommandSpin_editingFinished()
{
    this->setFocus();
}

void GamePad::on_yCommandSpin_editingFinished()
{
    this->setFocus();
}

void GamePad::on_yIncrementSpin_editingFinished()
{
    this->setFocus();
}

void GamePad::on_zIncrementSpin_editingFinished()
{
    this->setFocus();

}

void GamePad::on_zCommandSpin_editingFinished()
{
    this->setFocus();

}
