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
#include "FabConLib/coreinterface.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum ViewState{
        CONNECT,
        JOB,
        MATERIALS,
        PRINT
    };
public:
    explicit MainWindow(QWidget *parent = 0);
    void setUseFileArg(bool b);
    void setFileArg(QString theFile);
    //Interface getPrintInterface();
    ~MainWindow();

public slots:
    void forwardClicked();
    void backClicked();
    void setGo();
    void setStop();
    void setPause();
    void setResume();
    void printerConnected();
    void onStateChaged(int i);
    void materialNeeded(int i);

signals:
    //Connect
    void sendPreloadedConfig(QString preloaded_path);
    //Job
    void sendPreloadedFabFile();

private:
    void updateState();
    void enableOne(int);
    void setUpWidgets();
    void setUpConnections();

private:
    Ui::MainWindow *ui;
    ConnectWidget* connectWidget;
    JobWidget* jobWidget;
    MaterialsWidget* materialsWidget;
    PrintWidget* printWidget;
    GamePad* gamepad_container;

    QSettings settings;

    int current_state;
    QString file_arg;
    bool use_file_arg;

    bool haveValidFile;
    bool isConnected;
    bool materialsInitialized;
    int machineState;

    CoreInterface* ci_;

};

#endif // MAINWINDOW_H
