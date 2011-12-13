#include "baywidget.h"
#include "ui_baywidget.h"
#include "baydialog.h"
#include <iostream>


BayWidget::BayWidget(QWidget *parent, CoreInterface *ci,int id):
    QWidget(parent), ui(new Ui::BayWidget)
{
    ui->setupUi(this);
    id_=id;

    QString bayName;
    QTextStream bs(&bayName,QIODevice::WriteOnly);
    bs<<"Bay "<<id;
    ui->bayLabel->setText(bayName);

    ci_=ci;

    //Create baydialog for this bay
    dialog = new BayDialog(this,id,ci);
    connect(ci_,SIGNAL(materialsAvailable(QMap<int,Material>)),this,SLOT(setMaterials(QMap<int,Material>)));

}

void BayWidget::setMaterials(QMap<int,Material> materials){
    QStringList materialList;

    QMapIterator<int,Material> i(materials);
    while (i.hasNext()){
        i.next();
        Material m = i.value();
        materialMap_[i.key()]= m.name;
        idtomaterials_[m.name]=i.key();
        materialList.append(m.name);
    }
    ui->materialCombo->addItems(materialList);
}


void BayWidget::on_editButton_clicked()
{
    dialog->show();
}

BayWidget::~BayWidget()
{
    delete ui;
}


void BayWidget::setBayCommand(int bayNum, double distance)
{
    ci_->moveBayMotor(bayNum,distance,distance);/// THIS IS BAD FORM: TODO add a time/speed mechanism
}

void BayWidget::on_materialCombo_activated(const QString &arg1)
{
    QString material = arg1;
    int matid = idtomaterials_[material];
    ci_->setMaterial(id_,matid);
}
