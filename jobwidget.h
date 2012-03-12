#ifndef JOBWIDGET_H
#define JOBWIDGET_H

#include <QWidget>
#include "FabConLib/coreinterface.h"

namespace Ui {
    class JobWidget;
}

class JobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JobWidget(QWidget *parent, CoreInterface *ci);
    ~JobWidget();
    void setFile();

public slots:
    void updatePreloadedFabFile();
    void onLoadClicked();

    void estimatesLoaded(double time, double volume, int numcmd);
    void LoadFile(QString xdfl_path);

private:
    Ui::JobWidget *ui;
    CoreInterface *ci_;
    QString xdfl_path;
    void setAndSaveFile(QString file, bool save);
    void doInitialLoad();

private slots:
    void on_browseButton_clicked();
};

#endif // JOBWIDGET_H
