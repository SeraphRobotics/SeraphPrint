#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include "qextserialenumerator.h"

namespace Ui {
    class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = 0);
    ~ConnectWidget();

public slots:
    void preloadConfig(QString preloaded_path);

signals:
    void connectToPrinter(QString port, QString config_path);

private:
    Ui::ConnectWidget *ui;
    QString port; // QComboBox index of the selected COM port
    QString config_path;
    QextSerialEnumerator qse;

private slots:
    void on_configBox_currentIndexChanged(QString text);
    void on_portBox_currentIndexChanged(QString text);
    void on_configButton_clicked();
    void on_connectButton_clicked();
};

#endif // CONNECTWIDGET_H
