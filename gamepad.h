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
    explicit GamePad(QWidget *parent = 0);
    ~GamePad();



private:
    Ui::GamePad *ui;

};

#endif // GAMEPAD_H
