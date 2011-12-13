#ifndef MATERIALSWIDGET_H
#define MATERIALSWIDGET_H

#include <QWidget>
#include "baywidget.h"
#include "FabConLib/coreinterface.h"

using namespace std;

namespace Ui {
    class MaterialsWidget;
}

class MaterialsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialsWidget(QWidget *parent, CoreInterface *ci);

    ~MaterialsWidget();


private:
    Ui::MaterialsWidget *ui;
    int numBays;
    QVector<BayWidget*> bayWidgets;
    CoreInterface *ci_;

};

#endif // MATERIALSWIDGET_H
