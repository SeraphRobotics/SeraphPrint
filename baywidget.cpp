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
    // connect(dialog, SIGNAL(sendBayCommand(int,double,bool)), this, SLOT(setBayCommand(int,double,bool)));

}

void BayWidget::setMaterials(QMap<int,QString> materials){
    materialMap_ = materials;
    QStringList materialList;
    QMapIterator<int,QString> i(materialMap_);
    while(i.hasNext()){
        i.next();
        materialList.append(i.value());
        idtomaterials_[i.value()]=i.key();
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
