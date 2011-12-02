#include "gamepad.h"
#include "ui_gamepad.h"
#include "motordialog.h"
#include <stdio.h>
#include <QKeyEvent>

// TODO: Replace the Position text boxes with labels, which is really what they should be

GamePad::GamePad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePad)
{
    ui->setupUi(this);

    //initialization of variables
    XVelocity = 100.0;
    XAcceleration = 100.0;
    YVelocity = 100.0;
    YAcceleration = 100.0;
    ZVelocity = 100.0;
    ZAcceleration = 100.0;
    xRev = false;
    yRev = false;
    zRev = false;
    motorX = "X";
    motorY = "Y";
    motorZ = "Z";
    xOpen = false;
    yOpen = false;
    zOpen = false;
    /*xOrigin = 0;
    yOrigin = 0;
    zOrigin = 0;*/
    /*curLocX =
    curLocY =
    curLocZ =
    */
    //update the position fields
    connect(parent, SIGNAL(posChanged(double,double,double)), this, SLOT(onPositionChanged(double,double,double)));;
}


GamePad::~GamePad()
{
    delete ui;
}


\

void GamePad::on_xLaunchButton_clicked()
{
    if (! xOpen){
    xOpen = true;
    motordialog* dialog = new motordialog(this, motorX, XVelocity, XAcceleration, xRev);
    dialog->show();
    connect(dialog, SIGNAL(setProperties(QString,double,double,bool)), this, SLOT(onMotorChanged(QString, double, double, bool)));
    connect(dialog, SIGNAL(closed()), this, SLOT(onXDialogDes()));
    }
}

void GamePad::on_yLaunchButton_clicked()
{
    if (! yOpen)
    {
        yOpen = true;
        motordialog* dialog = new motordialog(this, motorY, YVelocity, YAcceleration, yRev);
        dialog->show();
        connect(dialog, SIGNAL(setProperties(QString,double,double,bool)), this, SLOT(onMotorChanged(QString, double, double, bool)));
        connect(dialog, SIGNAL(closed()), this, SLOT(onYDialogDes()));
    }
}

void GamePad::on_zLabelButton_clicked()
{
    if (! zOpen)
    {
        zOpen = true;
        motordialog* dialog = new motordialog(this, motorZ, ZVelocity, ZAcceleration, zRev);
        dialog->show();
        connect(dialog, SIGNAL(setProperties(QString,double,double,bool)), this, SLOT(onMotorChanged(QString, double, double, bool)));
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

void GamePad::onMotorChanged(QString motorname, double velocity, double acceleration, bool reverse) {
   if (motorname == motorX) {
       /*
       if (reverse) {
       XVelocity = -1 * velocity;
       XAcceleration = -1 * acceleration;

       }

       else {
       XVelocity = velocity;
       XAcceleration = acceleration;
       }
       */
       XVelocity = velocity;
       XAcceleration = acceleration;
       xRev = reverse;
       //emit to main window to change this guys velocity and acceleration
       emit setProperties(motorX, XVelocity, XAcceleration);
   }
   else if (motorname == motorY){
       /*if (reverse) {
       YVelocity = -1 * velocity;
       YAcceleration = -1 * acceleration;

       }
       else {
       YVelocity = velocity;
       YAcceleration = acceleration;
       } */

       YVelocity = velocity;
       YAcceleration = acceleration;
       yRev = reverse;
       emit setProperties(motorY, YVelocity, YAcceleration);
   }
   else if (motorname == motorZ) {
       /*if (reverse) {
       ZVelocity = -1 * velocity;
       ZAcceleration = -1 * acceleration;

       }
       else {
       ZVelocity = velocity;
       ZAcceleration = acceleration;
       } */
       ZVelocity = velocity;
       ZAcceleration = acceleration;
       zRev = reverse;
       emit setProperties(motorZ, ZVelocity, ZAcceleration);
   }
}

void GamePad::on_toOriginButton_clicked()
{
    //move to origin
    emit moveTo(-ui->xPositionSpin->value(), -ui->yPositionSpin->value(), -ui->zPositionSpin->value());
}

void GamePad::on_originButton_clicked()
{
    //setting origin
    ui->xPositionSpin->setValue(0);
    ui->yPositionSpin->setValue(0);
    ui->zPositionSpin->setValue(0);
}


void GamePad::on_moveButton_clicked()
{
    //move to commanded
    emit moveTo(ui->xCommandSpin->value() - ui->xPositionSpin->value(), ui->yCommandSpin->value() - ui->yPositionSpin->value(), ui->zCommandSpin->value() - ui->zPositionSpin->value());
}

void GamePad::onPositionChanged(double xPos, double yPos, double zPos) {
    ui->xPositionSpin->setValue(ui->xPositionSpin->value() + xPos);
    ui->yPositionSpin->setValue(ui->yPositionSpin->value() + yPos);
    ui->zPositionSpin->setValue(ui->zPositionSpin->value() + zPos);

}

void GamePad::on_upPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value());
    emit moveTo(-ui->xIncrementSpin->value(), 0, 0);
}

void GamePad::on_downPushbutton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value());
    emit moveTo(ui->xIncrementSpin->value(), 0, 0);
}

void GamePad::on_leftPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(0, - ui->yIncrementSpin->value(), 0);
}

void GamePad::on_rightPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(0, ui->yIncrementSpin->value(), 0);
}
void GamePad::on_minusZPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value() - ui->zIncrementSpin->value());
    emit moveTo(0, 0,- ui->zIncrementSpin->value());
}

void GamePad::on_plusZPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value(), ui->yPositionSpin->value(), ui->zPositionSpin->value() + ui->zIncrementSpin->value());
    emit moveTo(0, 0, ui->zIncrementSpin->value());
}


void GamePad::on_urPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(- ui->xIncrementSpin->value(), ui->yIncrementSpin->value(), 0);
}

void GamePad::on_ulPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() - ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(- ui->xIncrementSpin->value(), -ui->yIncrementSpin->value(), 0);
}



void GamePad::on_dlPushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(),
      //          ui->yPositionSpin->value() - ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(ui->xIncrementSpin->value(), -ui->yIncrementSpin->value(), 0);
}

void GamePad::on_drpushButton_clicked()
{
    //emit moveTo(ui->xPositionSpin->value() + ui->xIncrementSpin->value(),
    //            ui->yPositionSpin->value() + ui->yIncrementSpin->value(), ui->zPositionSpin->value());
    emit moveTo(ui->xIncrementSpin->value(), ui->yIncrementSpin->value(), 0);
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
