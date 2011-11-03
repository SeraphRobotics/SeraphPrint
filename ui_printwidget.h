/********************************************************************************
** Form generated from reading UI file 'printwidget.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTWIDGET_H
#define UI_PRINTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrintWidget
{
public:
    QPushButton *playButton;
    QLabel *label_info;
    QLabel *label_move;
    QPushButton *stopButton;

    void setupUi(QWidget *PrintWidget)
    {
        if (PrintWidget->objectName().isEmpty())
            PrintWidget->setObjectName(QString::fromUtf8("PrintWidget"));
        PrintWidget->resize(537, 300);
        playButton = new QPushButton(PrintWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(130, 100, 141, 111));
        label_info = new QLabel(PrintWidget);
        label_info->setObjectName(QString::fromUtf8("label_info"));
        label_info->setGeometry(QRect(140, 243, 291, 20));
        label_move = new QLabel(PrintWidget);
        label_move->setObjectName(QString::fromUtf8("label_move"));
        label_move->setGeometry(QRect(140, 40, 271, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_move->setFont(font);
        stopButton = new QPushButton(PrintWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(290, 100, 141, 111));

        retranslateUi(PrintWidget);

        QMetaObject::connectSlotsByName(PrintWidget);
    } // setupUi

    void retranslateUi(QWidget *PrintWidget)
    {
        PrintWidget->setWindowTitle(QApplication::translate("PrintWidget", "Form", 0, QApplication::UnicodeUTF8));
        playButton->setText(QApplication::translate("PrintWidget", "Start", 0, QApplication::UnicodeUTF8));
        label_info->setText(QApplication::translate("PrintWidget", "Ready.", 0, QApplication::UnicodeUTF8));
        label_move->setText(QApplication::translate("PrintWidget", "Move the toolhead to the start position.", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("PrintWidget", "Force Stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrintWidget: public Ui_PrintWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTWIDGET_H
