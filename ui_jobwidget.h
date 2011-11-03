/********************************************************************************
** Form generated from reading UI file 'jobwidget.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOBWIDGET_H
#define UI_JOBWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JobWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_fileL;
    QLabel *label_file;
    QPushButton *browseButton;
    QLabel *label_timeL;
    QLabel *label_time;
    QLabel *label_volumeL;
    QLabel *label_volume;
    QLabel *label_dimL;
    QSplitter *splitter;
    QLabel *label_dimX;
    QLabel *label_dimxL;
    QLabel *label_dimY;

    void setupUi(QWidget *JobWidget)
    {
        if (JobWidget->objectName().isEmpty())
            JobWidget->setObjectName(QString::fromUtf8("JobWidget"));
        JobWidget->resize(530, 300);
        layoutWidget = new QWidget(JobWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 100, 361, 103));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_fileL = new QLabel(layoutWidget);
        label_fileL->setObjectName(QString::fromUtf8("label_fileL"));

        gridLayout->addWidget(label_fileL, 0, 0, 1, 1);

        label_file = new QLabel(layoutWidget);
        label_file->setObjectName(QString::fromUtf8("label_file"));

        gridLayout->addWidget(label_file, 0, 1, 1, 2);

        browseButton = new QPushButton(layoutWidget);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        gridLayout->addWidget(browseButton, 0, 3, 1, 1);

        label_timeL = new QLabel(layoutWidget);
        label_timeL->setObjectName(QString::fromUtf8("label_timeL"));

        gridLayout->addWidget(label_timeL, 1, 0, 1, 1);

        label_time = new QLabel(layoutWidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        gridLayout->addWidget(label_time, 1, 1, 1, 3);

        label_volumeL = new QLabel(layoutWidget);
        label_volumeL->setObjectName(QString::fromUtf8("label_volumeL"));

        gridLayout->addWidget(label_volumeL, 2, 0, 1, 1);

        label_volume = new QLabel(layoutWidget);
        label_volume->setObjectName(QString::fromUtf8("label_volume"));

        gridLayout->addWidget(label_volume, 2, 1, 1, 3);

        label_dimL = new QLabel(layoutWidget);
        label_dimL->setObjectName(QString::fromUtf8("label_dimL"));

        gridLayout->addWidget(label_dimL, 3, 0, 1, 1);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label_dimX = new QLabel(splitter);
        label_dimX->setObjectName(QString::fromUtf8("label_dimX"));
        splitter->addWidget(label_dimX);
        label_dimxL = new QLabel(splitter);
        label_dimxL->setObjectName(QString::fromUtf8("label_dimxL"));
        splitter->addWidget(label_dimxL);
        label_dimY = new QLabel(splitter);
        label_dimY->setObjectName(QString::fromUtf8("label_dimY"));
        splitter->addWidget(label_dimY);

        gridLayout->addWidget(splitter, 3, 1, 1, 3);


        retranslateUi(JobWidget);

        QMetaObject::connectSlotsByName(JobWidget);
    } // setupUi

    void retranslateUi(QWidget *JobWidget)
    {
        JobWidget->setWindowTitle(QApplication::translate("JobWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_fileL->setText(QApplication::translate("JobWidget", "File:", 0, QApplication::UnicodeUTF8));
        label_file->setText(QApplication::translate("JobWidget", "(none)", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("JobWidget", "Browse", 0, QApplication::UnicodeUTF8));
        label_timeL->setText(QApplication::translate("JobWidget", "Estimated time:", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("JobWidget", "n/a", 0, QApplication::UnicodeUTF8));
        label_volumeL->setText(QApplication::translate("JobWidget", "Estimated volume:", 0, QApplication::UnicodeUTF8));
        label_volume->setText(QApplication::translate("JobWidget", "n/a", 0, QApplication::UnicodeUTF8));
        label_dimL->setText(QApplication::translate("JobWidget", "Dimensions:", 0, QApplication::UnicodeUTF8));
        label_dimX->setText(QApplication::translate("JobWidget", "n/a", 0, QApplication::UnicodeUTF8));
        label_dimxL->setText(QApplication::translate("JobWidget", "x", 0, QApplication::UnicodeUTF8));
        label_dimY->setText(QApplication::translate("JobWidget", "n/a", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class JobWidget: public Ui_JobWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOBWIDGET_H
