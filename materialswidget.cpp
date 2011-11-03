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

}

void MaterialsWidget::initializeMaterials(int nBays, QVector<std::string> bayMaterials)
{
    numBays = nBays;
    materials = bayMaterials;

    for (int x = 0; x < numBays; x++)
    {
        QString bayName = QString("Bay") + QString(" ") + x;
        BayWidget* b = new BayWidget(this, bayName, materials);
        bayWidgets.append(b);
        ui->horizontalLayout->addWidget(b);
    }

}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
}
