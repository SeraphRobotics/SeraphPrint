#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QFileInfoList>
#include <QDir>
#include "FabConLib/coreinterface.h"

namespace Ui
{
    class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent, CoreInterface *ci);
    ~ConnectWidget();

public slots:
    void loading(bool load);

signals:
    void atemptConnect();

private:
    void loadFiles();
    void addConfig(QString path);

private:
    Ui::ConnectWidget *ui;
    CoreInterface *ci_;
    QStringList portList;
    QFileInfoList configList;
    QDir configFileDirectory;




private slots:
    void on_configButton_clicked();
    void on_connectButton_clicked();
};

#endif // CONNECTWIDGET_H
