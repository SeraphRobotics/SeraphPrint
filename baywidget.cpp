#include "baywidget.h"
#include "ui_baywidget.h"
#include "baydialog.h"

//Should take in the map of materialCalibrations in its constructor
//Then iterate through this map to add items to each BayWidget's drop down list
BayWidget::BayWidget(QWidget *parent, QString bayName, QVector<std::string> bayMaterials)
    : QWidget(parent), ui(new Ui::BayWidget)
{
    ui->setupUi(this);
    ui->bayLabel->setText(bayName);

    //Add items (materials) to drop down
    /*for(int x = 0; x < bayMaterials.size(); x++)
    {
        ui->materialCombo->addItem(QString(bayMaterials.at(x)));
    }*/
}


void BayWidget::on_editButton_clicked()
{
    BayDialog* dialog = new BayDialog(this,ui->bayLabel->text());
    dialog->show();
}

BayWidget::~BayWidget()
{
    delete ui;
}

void BayWidget::on_materialCombo_currentIndexChanged(const QString &arg1)
{
    QString material = arg1;
    QString bayName = ui->bayLabel->text();
    emit materialChanged(bayName, material);

}


