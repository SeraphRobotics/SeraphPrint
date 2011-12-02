#ifndef JOBWIDGET_H
#define JOBWIDGET_H

#include <QWidget>

namespace Ui {
    class JobWidget;
}

class JobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JobWidget(QWidget *parent = 0);
    ~JobWidget();

public slots:
    void preloadedFabFile();
    void onLoadClicked();

signals:
    void sendAndLoadFile(QString fab_path);

private:
    Ui::JobWidget *ui;
    QString fab_path;
    void setAndSaveFile(QString file, bool save);
    void doInitialLoad();

private slots:
    void on_browseButton_clicked();
};

#endif // JOBWIDGET_H
