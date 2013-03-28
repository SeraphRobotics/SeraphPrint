#include "jobwidget.h"
#include "ui_jobwidget.h"
#include <QFileDialog>
#include <QDir>
#include <qdebug>
#include <QMessageBox>
#include <math.h>

JobWidget::JobWidget(QWidget *parent,CoreInterface *ci) : QWidget(parent), ui(new Ui::JobWidget)
{
    ci_ = ci;
    ui->setupUi(this);

    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoadClicked()));
    connect(ci_,SIGNAL(estimated(double,double,int)),this,SLOT(estimatesLoaded(double,double,int)));

    doInitialLoad();
}

JobWidget::~JobWidget()
{
    delete ui;
}

void JobWidget::doInitialLoad()
{
    // Load the saved file path into the box
    // QSettings constructor values were specified in main.cpp.
    QSettings settings;
    QString savedPath = settings.value("last used fab file", "").toString();

    qDebug() << "JobWidget::doInitialLoad() has last used fab file" << savedPath;

    if (savedPath != "")
    {
        // If the saved path looks OK, attempt to load its file
        ui->lineEdit_file->setText(savedPath);
    }

    //setAndSaveFile(savedPath, false);
}

void JobWidget::updatePreloadedFabFile()
{
    QSettings settings;
    QString savedPath = settings.value("last used fab file", "").toString();

    qDebug() << "last used fab file" << savedPath;
    ui->lineEdit_file->setText(savedPath);
}

void JobWidget::setAndSaveFile(QString filePath, bool doSave)
{
    if (!filePath.isEmpty())
    {
        if (doSave)
        {
            // QSettings constructor values were specified in main.cpp.
            QSettings settings;
            settings.setValue("last used fab file", filePath);
            settings.sync();
        }
        LoadFile(filePath);
    }
}

void JobWidget::estimatesLoaded(double time, double volume, int numcmd){
    int hours=0,min=0,sec=0;
    double vol=0;

    QString timeString;
    QString volumeString;
    QTextStream vs(&volumeString,QIODevice::WriteOnly);
    QTextStream ts(&timeString,QIODevice::WriteOnly);
    hours = floor(time/3600.0);
    time = time - hours*3600;
    min = floor(time/60.0);
    sec =floor(time - min*60)+1;
    ts<<hours<<":"<<min<<":"<<sec;
    vol = volume/1000.0;
    vs<<vol<<"cc";
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
