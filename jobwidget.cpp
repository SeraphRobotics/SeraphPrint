#include "jobwidget.h"
#include "ui_jobwidget.h"
#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <qdebug>

JobWidget::JobWidget(QWidget *parent) : QWidget(parent), ui(new Ui::JobWidget)
{
    ui->setupUi(this);

    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoadClicked()));

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

        qDebug() << "About to emit signal in setAndSaveFile!"; // <<<<<<<<<<
        emit sendAndLoadFile(filePath);
    }
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

    //setAndSaveFile(filename, true);
}
