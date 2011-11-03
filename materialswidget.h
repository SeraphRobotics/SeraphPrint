#ifndef MATERIALSWIDGET_H
#define MATERIALSWIDGET_H

#include <QWidget>
#include "baywidget.h"

namespace Ui {
    class MaterialsWidget;
}

class MaterialsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialsWidget(QWidget *parent = 0);
    //map<string, MaterialCalibration, LessThanString> materialCalibrations;
    ~MaterialsWidget();

public slots:
    void initializeMaterials(int numBays, QVector<std::string> bayMaterials);

    //void initializeMaterials(int numBays);

private:
    Ui::MaterialsWidget *ui;
    int numBays;
    QVector<std::string> materials;
    QVector<BayWidget*> bayWidgets;

};

#endif // MATERIALSWIDGET_H
