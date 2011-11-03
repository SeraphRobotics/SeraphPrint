#ifndef BAYWIDGET_H
#define BAYWIDGET_H

#include <QWidget>
#include <qpushbutton.h>

namespace Ui {
    class BayWidget;
}

class BayWidget : public QWidget
{
    Q_OBJECT

public:
    QPushButton editButton;
    explicit BayWidget(QWidget *parent = 0, QString bayName = "Bay 0");
    ~BayWidget();

signals:
    void materialChanged(QString bay, QString material);

private:
    Ui::BayWidget *ui;

private slots:
    void on_editButton_clicked();
    //void on_materialCombo_currentIndexChanged(int index);
    void on_materialCombo_currentIndexChanged(const QString &arg1);
};

#endif // BAYWIDGET_H
