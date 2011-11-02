#include "materialswidget.h"
#include "ui_materialswidget.h"
#include "baywidget.h"

MaterialsWidget::MaterialsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialsWidget)
{
    ui->setupUi(this);

    BayWidget* bayWidget0 = new BayWidget(this, "Bay 0");
    BayWidget* bayWidget1 = new BayWidget(this, "Bay 1");
    BayWidget* bayWidget2 = new BayWidget(this, "Bay 2");

    ui->horizontalLayout->addWidget(bayWidget0);
    ui->horizontalLayout->addWidget(bayWidget1);
    ui->horizontalLayout->addWidget(bayWidget2);

    /*for (int x = 0; x < numBays; x++)
    {
        QString bayName = QString("Bay") + QString(" ") + x;
        ui->horizontalLayout->addWidget(new BayWidget(this, bayName));
    }
    this->setLayout(ui->horizontalLayout)*/

}

//Should take in a map of materialCalibrations
//can't do this since the library isn't loaded
void MaterialsWidget::initializeMaterials(int nBays, map<string, MaterialCalibration, LessThanString> materialCalibrations)
{
    numBays = nBays;
    materials = materialCalibrations;
}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
}
