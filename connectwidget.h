#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QFileInfoList>
#include <QDir>

namespace Ui
{
    class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = 0);
    ~ConnectWidget();

signals:
    void connectToPrinter(QString port, QString config_path);

private:
    void loadFiles();
    Ui::ConnectWidget *ui;
    QStringList portList;
    QFileInfoList configList;
    QDir configFileDirectory;

    void addConfig(QString path);

//public slots:
//    void preloadConfig(QString preloaded_path);

private slots:
    void on_configButton_clicked();
    void on_connectButton_clicked();
};

#endif // CONNECTWIDGET_H
