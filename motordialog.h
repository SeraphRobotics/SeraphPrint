#ifndef MOTORDIALOG_H
#define MOTORDIALOG_H

#include <QDialog>

namespace Ui {
    class motordialog;
}

class motordialog : public QDialog
{
    Q_OBJECT

public:
    explicit motordialog(QWidget *parent = 0, QString s = "hi", double vel = 0, double accel= 0, bool checked = false);
    ~motordialog();

signals:
    void setProperties(QString motorName, double velocity, double acceleration);
    void closed();


private slots:
    void onVelSlider_Changed();
    void onVelBox_Changed();
    void onAccelSlider_Changed();
    void onAccelBox_Changed();
    void on_okButton_clicked();

private:
    QString motorId;
    Ui::motordialog *ui;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MOTORDIALOG_H
