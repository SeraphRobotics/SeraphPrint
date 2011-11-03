/********************************************************************************
** Form generated from reading UI file 'materialswidget.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIALSWIDGET_H
#define UI_MATERIALSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaterialsWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *MaterialsWidget)
    {
        if (MaterialsWidget->objectName().isEmpty())
            MaterialsWidget->setObjectName(QString::fromUtf8("MaterialsWidget"));
        MaterialsWidget->resize(535, 300);
        horizontalLayoutWidget = new QWidget(MaterialsWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 69, 511, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(MaterialsWidget);

        QMetaObject::connectSlotsByName(MaterialsWidget);
    } // setupUi

    void retranslateUi(QWidget *MaterialsWidget)
    {
        MaterialsWidget->setWindowTitle(QApplication::translate("MaterialsWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaterialsWidget: public Ui_MaterialsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIALSWIDGET_H
