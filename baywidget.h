#ifndef BAYWIDGET_H
#define BAYWIDGET_H

#include <QWidget>
#include <qpushbutton.h>
#include "baydialog.h"

namespace Ui {
    class BayWidget;
}

class BayWidget : public QWidget
{
    Q_OBJECT

public:
    QPushButton editButton;
    explicit BayWidget(QWidget *parent = 0, QString bayName = "Bay 0", QVector<std::string> bayMaterials = QVector<std::string>());
    ~BayWidget();

private:
    Ui::BayWidget *ui;
    BayDialog* dialog;

signals:
    void sendBayMaterial(int bayNum, QString material);
    void sendBayCommand(int bayNum, double distance, bool absolute);

public slots:
    void setBayCommand(int bayNum, double distance, bool absolute);

private slots:
    void on_editButton_clicked();
    void on_materialCombo_activated(const QString &arg1);
};

#endif // BAYWIDGET_H
