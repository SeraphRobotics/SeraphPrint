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
    // "Executing path <currentPath> of <totalPaths>..."

signals:
    void go();
    void pause();
    void stop();

private:
    Ui::PrintWidget *ui;
    int currentPath;
    int totalPaths;
    bool isPaused;

private slots:
    void on_stopButton_clicked();
    void on_playButton_clicked();
};

#endif // PRINTWIDGET_H
