#ifndef MATERIALSWIDGET_H
#define MATERIALSWIDGET_H

#include <QWidget>

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
    void initializeBayWidget(int numBays, map<string, MaterialCalibration, LessThanString> materialCalibrations);
    //void initializeMaterials(int numBays);

private:
    Ui::MaterialsWidget *ui;
    int numBays;
    map<string, MaterialCalibration, LessThanString> materials;

};

#endif // MATERIALSWIDGET_H
