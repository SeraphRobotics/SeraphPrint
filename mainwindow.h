#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "connectwidget.h"
#include "materialswidget.h"
#include "jobwidget.h"
#include "printwidget.h"
#include "gamepad.h"
#include "FabConLib/xdflhandler.h"
#include "FabConLib/virtualmachines.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setUseFileArg(bool b);
    void setFileArg(QString theFile);
    //Interface getPrintInterface();
    ~MainWindow();

public slots:
    void forwardClicked();
    void backClicked();
    //Connect
    void setPrinter(QString port, QString config_path);
    //Job
    void setFabFile(QString fab_path);
    void setXDFLFile(QString xdfl_path);
    //Materials
    void setBayCommand(int bayNum, double distance, bool absolute); //from Bay Dialog
    void setBayMaterial(int bayNum, QString material); //from Bay Widget
    void getBayNum(int bayNum);
    //Print
    void setGo();
    void setPause();
    void setStop();
    void setResume();
    void getPrinterProgress(int currPath, QString status);
    //game pad handlers
    //sets this motor's vel and acceleration fields
    void propertiesHandler(QString motorname, double velocity, double acceleration);
    //move to this x,y,z coordinate
    void moveHandler(double xPos, double yPos, double zPos);

signals:
    //Connect
    void sendPreloadedConfig(QString preloaded_path);
    //Job
    void sendPreloadedFabFile();
    //Materials
    void sendBaysAndMaterials(int numBays, QVector<string> bayMaterials);
    void sendBayPosition(double position);
    //Print
    void sendCurrentPath(int n);
    void sendTotalPaths(int n);
    void posChanged(double x, double y, double z);
    void reportPrinterProgress(int currPath, QString status);

private:
    Ui::MainWindow *ui;
    ConnectWidget* connectWidget;
        QSettings settings;
    JobWidget* jobWidget;
    MaterialsWidget* materialsWidget;
    PrintWidget* printWidget;
    GamePad* gamepad_container;
    //Interface printInterface;
    VirtualPrinter vm;
    XDFLHandler *handler;
    int current_state;
    QString file_arg;
    bool use_file_arg;

    // aen27, 1 December 2011
    bool haveValidFile;
    bool isConnected;

    bool materialsInitialized;
    void updateState();
    void enableOne(int);
    void setUpWidgets();
    void setUpConnections();
};

#endif // MAINWINDOW_H
