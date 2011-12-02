#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QWidget>

namespace Ui {
    class GamePad;
}

class GamePad : public QWidget
{
    Q_OBJECT

public:
    explicit GamePad(QWidget *parent);
    ~GamePad();

signals:
    void setProperties(QString motorName, double velocity, double acceleration);
    void moveTo(double x, double y, double z);

private slots:

    void on_zCommandSpin_editingFinished();
    void on_zIncrementSpin_editingFinished();
    void on_yIncrementSpin_editingFinished();
    void on_yCommandSpin_editingFinished();
    void on_xCommandSpin_editingFinished();
    void on_xIncrementSpin_editingFinished();
    void on_drpushButton_clicked();
    void on_dlPushButton_clicked();

    void on_ulPushButton_clicked();
    void on_urPushButton_clicked();
    void on_xLaunchButton_clicked();
    void on_yLaunchButton_clicked();
    void on_zLabelButton_clicked();
    void onMotorChanged(QString motorname, double velocity, double acceleration, bool reverse);
    void onXDialogDes();
    void onYDialogDes();
    void onZDialogDes();
    void onPositionChanged(double xPos, double yPos, double zPos);

    void on_toOriginButton_clicked();

    void on_originButton_clicked();

    void on_moveButton_clicked();

    void on_upPushButton_clicked();

    void on_downPushbutton_clicked();

    void on_leftPushButton_clicked();
    void on_rightPushButton_clicked();
    void on_minusZPushButton_clicked();

    void on_plusZPushButton_clicked();

private:
    Ui::GamePad *ui;
    float XVelocity;
    float XAcceleration;
    float YVelocity;
    float YAcceleration;
    float ZVelocity;
    float ZAcceleration;
    QString motorX;
    QString motorY;
    QString motorZ;
    bool xOpen;
    bool yOpen;
    bool zOpen;
    bool xRev;
    bool yRev;
    bool zRev;
    double xOrigin;
    double yOrigin;
    double zOrigin;
    /*double curLocX;
    double curLocY;
    double curLocZ;
    double nextLocX;
    double nextLocY;
    double nextLocZ; */


};

#endif // GAMEPAD_H
