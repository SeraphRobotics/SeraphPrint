#include "jobwidget.h"
#include "ui_jobwidget.h"
#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <qdebug>
#include <QMessageBox>
#include <math.h>

JobWidget::JobWidget(QWidget *parent,CoreInterface *ci) : QWidget(parent), ui(new Ui::JobWidget)
{
    ci_ = ci;
    ui->setupUi(this);

    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoadClicked()));
    connect(ci_,SIGNAL(estimated(double,double)),this,SLOT(estimatesLoaded(double,double)));

    doInitialLoad();
}

JobWidget::~JobWidget()
{
    delete ui;
}

void JobWidget::doInitialLoad()
{
    // Load the saved file path into the box
    QSettings theSettings("Creative Machines Lab", "FabPrint");
    QString savedPath = theSettings.value("last used fab file", "").toString();

    qDebug() << "Initial load called - from settings: " << savedPath;

    if (savedPath != "")
    {
        // If the saved path looks OK, attempt to load its file
        ui->lineEdit_file->setText(savedPath);
    }

    //setAndSaveFile(savedPath, false);
}

void JobWidget::preloadedFabFile()
{
//    ui->lineEdit_fileL->setVisible(false);
//    ui->lineEdit_file->setVisible(false);
//    ui->browseButton->setVisible(false);
}

void JobWidget::setAndSaveFile(QString filePath, bool doSave)
{
    if (!filePath.isEmpty())
    {
        if (doSave)
        {
            QSettings theSettings("Creative Machines Lab", "FabPrint");
            theSettings.setValue("last used fab file", filePath);
            theSettings.sync();
        }
        LoadFile(filePath);
    }
}

void JobWidget::estimatesLoaded(double time, double volume){
    QString timeString;
    QString volumeString;
    QTextStream vs(&volumeString,QIODevice::WriteOnly);
    QTextStream ts(&timeString,QIODevice::WriteOnly);
    int hours = floor(time/3600.0);
    time = time - hours*3600;
    int min = floor(time/60.0);
    int sec =floor(time - min*60)+1;
    ts<<hours<<":"<<min<<":"<<sec;
    volume = volume/1000.0;
    vs<<volume<<"cc";
    ui->label_time->setText(timeString);
    ui->label_volume->setText(volumeString);
}


void JobWidget::onLoadClicked()
{
    setAndSaveFile(ui->lineEdit_file->text(), true);
}

void JobWidget::on_browseButton_clicked()
{
    // Thanks to QDir::homePath(), start the file chooser dialog in the user's home directory (a Qt call that should be totally cross-platform)
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr("FAB/XDFL Files (*.fab *.xdfl);;All Files (*.*)"));

    ui->lineEdit_file->setText(filename);

    setAndSaveFile(filename, true);
}

void JobWidget::LoadFile(QString xdfl_path){
    QString xdflString;
    QDomDocument xdflDom;
    // load the XDFL file into the DOM document
    {
      QFile xdflFile(xdfl_path);
      if (!xdflFile.open(QFile::ReadOnly)) {
          qDebug() <<"\nFAILED TO OPEN XDFL FILE\n";
          QMessageBox::warning(this,tr("ERROR"),tr("Could not open XDFL file"));
          return;
      }
      xdflDom.setContent(&xdflFile);
      xdflFile.close();
      xdflString = xdflDom.toString();
    }
    ci_->setXDFL(xdflString);
}
