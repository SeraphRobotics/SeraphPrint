#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectwidget.h"
#include "materialswidget.h"
#include "jobwidget.h"
#include "printwidget.h"
#include "gamepad.h"
#include "Interface.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void forwardClicked();
    void backClicked();
    //Conect
    void setPrinter(QString port, QString config_path);
    //Job
    void setFabFile(QString fab_path);
    //Materials
    void setBayCommand(int bayNum, double distance); //from Bay Dialog
    void setMaterial(int bayNum, QString material); //from Bay Widget
    //Print
    void setGo();
    void setPause();
    void setStop();

signals:
    //Connect
    void sendPreloadedConfig(QString preloaded_path);
    //Job
    void sendPreloadedFabFile();
    //Materials
    void sendBaysAndMaterials(int numBays, QVector<string> bayMaterials);
    //Print
    void sendCurrentPath(int n);
    void sendTotalPaths(int n);

private:
    Ui::MainWindow *ui;
    ConnectWidget* connectWidget;
    JobWidget* jobWidget;
    MaterialsWidget* materialsWidget;
    PrintWidget* printWidget;
    Interface printInterface;
    void updateState();
    void enableOne(int);
    void setUpWidgets();
};

#endif // MAINWINDOW_H
