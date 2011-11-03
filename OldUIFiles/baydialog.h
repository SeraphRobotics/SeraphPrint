#ifndef BAYDIALOG_H
#define BAYDIALOG_H

#include <QDialog>

namespace Ui {
    class BayDialog;
}

class BayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BayDialog(QWidget *parent = 0, QString s = "Bay 1");
    ~BayDialog();

signals:
    void moveBay(QString bayName, double distance);

private slots:

    void on_moveButton_clicked();
    void on_acceptButton_clicked();
    void on_upButton_released();
    void on_downButton_released();

private:
    Ui::BayDialog *ui;
};

#endif // BAYDIALOG_H
