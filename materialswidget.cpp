#include "materialswidget.h"
#include "ui_materialswidget.h"
#include "baywidget.h"
#include <iostream>

MaterialsWidget::MaterialsWidget(QWidget *parent, CoreInterface *ci) :
    QWidget(parent),
    ui(new Ui::MaterialsWidget)
{
    ui->setupUi(this);
    ci_ = ci;
    /*//FOR TESTING PURPOSES
    //should all be done by initializeMaterials()
    QVector<string> materials(3);
    materials.append("silicone");
    materials.append("plastic");
    materials.append("epoxy");

    for (int x = 0; x < 4; x++)
    {
        QString bayName = QString("Bay") + QString(" ") + QString::number(x);
        BayWidget* b = new BayWidget(this, bayName, materials);
        bayWidgets.append(b);
        ui->horizontalLayout->addWidget(b);
        connect(b, SIGNAL(sendBayCommand(int,double,bool)), this, SLOT(setBayCommand(int,double,bool)));
        connect(b, SIGNAL(sendBayMaterial(int,QString)), this, SLOT(setBayMaterial(int,QString)));
    }
    //END TESTING*/
}

void MaterialsWidget::initializeMaterials(int nBays, QVector<string> bayMaterials)
{
    numBays = nBays;
    materials = bayMaterials;
    //std::cout << "NumBays: " << nBays << endl;
    for (int x = 0; x < numBays; x++)
    {
        QString bayName = QString("Bay") + QString(" ") + QString::number(x);
        BayWidget* b = new BayWidget(this,ci_,x);
        bayWidgets.append(b);
        ui->horizontalLayout->addWidget(b);
        connect(b, SIGNAL(sendBayCommand(int,double,bool)), this, SLOT(setBayCommand(int,double,bool)));
        connect(b, SIGNAL(sendBayMaterial(int,QString)), this, SLOT(setBayMaterial(int,QString)));
    }

}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
}

void MaterialsWidget::setBayCommand(int bayNum, double distance, bool absolute)
{
    emit sendBayCommand(bayNum, distance, absolute);
}

void MaterialsWidget::setBayMaterial(int bayNum, QString material)
{
    emit sendBayMaterial(bayNum, material);
}
