#ifndef MATERIALSWIDGET_H
#define MATERIALSWIDGET_H

#include <QWidget>
#include "baywidget.h"
#include <string>
using namespace std;

namespace Ui {
    class MaterialsWidget;
}

class MaterialsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialsWidget(QWidget *parent, CoreInterface *ci);
    //map<string, MaterialCalibration, LessThanString> materialCalibrations;
    ~MaterialsWidget();

public slots:
    void initializeMaterials(int numBays, QVector<string> bayMaterials);
    void setBayCommand(int bayNum, double distance, bool absolute);
    void setBayMaterial(int bayNum, QString material);

signals:
    void sendBayCommand(int bayNum, double distance, bool absolute);
    void sendBayMaterial(int bayNum, QString material);

private:
    Ui::MaterialsWidget *ui;
    int numBays;
    QVector<std::string> materials;
    QVector<BayWidget*> bayWidgets;
    CoreInterface *ci_;

};

#endif // MATERIALSWIDGET_H
