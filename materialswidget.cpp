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
    numBays = ci_->vm_->bays.size();

    for (int x = 0; x < numBays; x++)
    {
        BayWidget* b = new BayWidget(this,ci_,x);
        bayWidgets.append(b);
        ui->horizontalLayout->addWidget(b);
    }

}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
}
