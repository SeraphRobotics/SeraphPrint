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
    connect(ci_,SIGNAL(materialsAvailable(QMap<int,Material>)),this,SLOT(setMaterials(QMap<int,Material>)));
    updateBays();

}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
}


void MaterialsWidget::updateBays(){
    numBays = ci_->vm_->bays.size();

    cleanUpBays();
    for (int x = 0; x < numBays; x++){
        BayWidget* b = new BayWidget(this,ci_,x);
        b->setMaterials(materials_);
        bayWidgets.append(b);
        ui->horizontalLayout->addWidget(b);
    }
}

void  MaterialsWidget::cleanUpBays(){
    foreach(BayWidget* b,bayWidgets){
        ui->horizontalLayout->removeWidget(b);
        delete b;
    }
}

void MaterialsWidget::setMaterials(QMap<int,Material> materials){
    materials_ = materials;
}
