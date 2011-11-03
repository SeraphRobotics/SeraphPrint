#include "gamepad.h"
#include "ui_gamepad.h"
#include <QIcon.h>
#include <QKeyEvent>

GamePad::GamePad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePad)
{  
    ui->setupUi(this);
    /*//region construction and initialization
    int buttonWidth = 75;
    int buttonHeight = 75;

    //ui->messageEdit->hide();
    QIcon upicon;
    upicon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_uparrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->upPushButton_5->setIcon(upicon);
    //ui->upPushButton_5->setIconSize(QSize(buttonWidth,buttonHeight));
    ui->upPushButton_5->setIconSize(QSize(30,30));
    ui->upPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon downicon;
    downicon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_downarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->downPushbutton_5->setIcon(downicon);
    //ui->downPushbutton_5->setIconSize(QSize(buttonWidth,buttonHeight));
    ui->downPushbutton_5->setIconSize(QSize(30,30));
    ui->downPushbutton_5->setFocusPolicy(Qt::NoFocus);
    //connect(down, SIGNAL(clicked()), up, SLOT(quit()));

    QIcon lefticon;
    lefticon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_leftarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->rightPushButton_5->setIcon(lefticon);
    //ui->rightPushButton_5->setIconSize(QSize(buttonWidth,buttonHeight));
    ui->rightPushButton_5->setIconSize(QSize(30,30));
    ui->rightPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon righticon;
    righticon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_rightarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->leftPushButton_5->setIcon(righticon);
    //ui->leftPushButton_5->setIconSize(QSize(buttonWidth,buttonHeight));
    ui->leftPushButton_5->setIconSize(QSize(30,30));
    ui->leftPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon leftdownicon;
    leftdownicon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_leftanddownarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->dlPushButton_5->setIcon(leftdownicon);
    //ui->dlPushButton_5->setIconSize(QSize(buttonWidth,buttonHeight));
    ui->dlPushButton_5->setIconSize(QSize(16,16));
    ui->dlPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon rightdownicon;
    rightdownicon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_rightanddownarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->drPushButton_5->setIcon(rightdownicon);
    //ui->drPushButton_5->setIconSize(QSize(buttonWidth - 10,buttonHeight - 10));
    ui->drPushButton_5->setIconSize(QSize(16,16));
    ui->drPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon uplefticon;
    uplefticon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_forwardandleftarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->ulPushButton_5->setIcon(uplefticon);
    //ui->ulPushButton_5->setIconSize(QSize(buttonWidth - 10,buttonHeight - 10));
    ui->ulPushButton_5->setIconSize(QSize(16,16));
    ui->ulPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon uprighticon;
    uprighticon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_forwardandrightarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->urPushButton_5->setIcon(uprighticon);
    //ui->urPushButton_5->setIconSize(QSize(buttonWidth -10 ,buttonHeight - 10));
    ui->urPushButton_5->setIconSize(QSize(16,16));
    ui->urPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon forwardsicon;
    forwardsicon.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_uparrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->minusZPushButton_5->setIcon(forwardsicon);
    //ui->minusZPushButton_5->setIconSize(QSize(buttonWidth - 10,buttonHeight - 10));
    ui->minusZPushButton_5->setIconSize(QSize(40,40));
    ui->minusZPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon zdown;
    zdown.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Aiga_downarrow.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->plusZPushButton_5->setIcon(zdown);
    //ui->plusZPushButton_5->setIconSize(QSize(buttonWidth -10 ,buttonHeight - 10));
    ui->plusZPushButton_5->setIconSize(QSize(40,40));
    ui->plusZPushButton_5->setFocusPolicy(Qt::NoFocus);

    QIcon stop;
    stop.addFile(QString::fromUtf8("/Users/karinasobhani/Desktop/GamePad 2/arrows/Stop2.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->stopButton_5->setIcon(stop);
    ui->stopButton_5->setIconSize(QSize(buttonWidth -10 ,buttonHeight - 10));
    ui->stopButton_5->setFocusPolicy(Qt::NoFocus);*/

}


GamePad::~GamePad()
{
    delete ui;
}


/*void GamePad::on_upPushButton_5_clicked()
{

}

void GamePad::on_urPushButton_5_clicked()
{

}

void GamePad::on_leftPushButton_5_clicked()
{

}*/
