#ifndef PRINTWIDGET_H
#define PRINTWIDGET_H

#include <QWidget>

namespace Ui {
    class PrintWidget;
}

class PrintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrintWidget(QWidget *parent = 0);
    ~PrintWidget();

public slots:
    void setCurrentPath(int num);
    void setTotalPaths(int num);
    void getPrinterProgress(int currPath, QString status);
    // "Executing path <currentPath> of <totalPaths>..."

signals:
    void go();
    void pause();
    void stop();
    void resume();

private:
    Ui::PrintWidget *ui;
    int currentPath;
    int totalPaths;
    bool isPrinting; // true once "Start" has been pressed (i.e. true even while paused)
    bool isPaused;

private slots:
    void on_stopButton_clicked();
    void on_playButton_clicked();
};

#endif // PRINTWIDGET_H