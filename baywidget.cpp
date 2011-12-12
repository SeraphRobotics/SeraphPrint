#include "baywidget.h"
#include "ui_baywidget.h"
#include "baydialog.h"
#include <iostream>

BayWidget::BayWidget(QWidget *parent, QString bayName, QVector<std::string> bayMaterials)
    : QWidget(parent), ui(new Ui::BayWidget)
{
    ui->setupUi(this);
    ui->bayLabel->setText(bayName);

    QStringList materials;
    //Add items (materials) to drop down
    for(int x = 0; x < bayMaterials.size(); x++)
    {
        materials << QString::fromStdString(bayMaterials.at(x));
    }
    ui->materialCombo->addItems(materials);

    //Create baydialog for this bay
    dialog = new BayDialog(this,ui->bayLabel->text());
    connect(dialog, SIGNAL(sendBayCommand(int,double,bool)), this, SLOT(setBayCommand(int,double,bool)));

}


void BayWidget::on_editButton_clicked()
{
    dialog->show();
}

BayWidget::~BayWidget()
{
    delete ui;
}


void BayWidget::setBayCommand(int bayNum, double distance, bool absolute)
{
    emit sendBayCommand(bayNum, distance, absolute);
}

void BayWidget::on_materialCombo_activated(const QString &arg1)
{
    QString material = arg1;
    QString bayName = ui->bayLabel->text().at(ui->bayLabel->text().length()-1);
    int bayNum = bayName.toInt();
    emit sendBayMaterial(bayNum, material);
}
