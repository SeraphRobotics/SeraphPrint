/********************************************************************************
** Form generated from reading UI file 'baywidget.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAYWIDGET_H
#define UI_BAYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BayWidget
{
public:
    QPushButton *editButton;
    QComboBox *materialCombo;
    QLabel *bayLabel;

    void setupUi(QWidget *BayWidget)
    {
        if (BayWidget->objectName().isEmpty())
            BayWidget->setObjectName(QString::fromUtf8("BayWidget"));
        BayWidget->resize(170, 106);
        editButton = new QPushButton(BayWidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(10, 70, 151, 32));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editButton->sizePolicy().hasHeightForWidth());
        editButton->setSizePolicy(sizePolicy);
        materialCombo = new QComboBox(BayWidget);
        materialCombo->setObjectName(QString::fromUtf8("materialCombo"));
        materialCombo->setGeometry(QRect(10, 40, 151, 26));
        sizePolicy.setHeightForWidth(materialCombo->sizePolicy().hasHeightForWidth());
        materialCombo->setSizePolicy(sizePolicy);
        bayLabel = new QLabel(BayWidget);
        bayLabel->setObjectName(QString::fromUtf8("bayLabel"));
        bayLabel->setGeometry(QRect(10, 20, 105, 16));

        retranslateUi(BayWidget);

        QMetaObject::connectSlotsByName(BayWidget);
    } // setupUi

    void retranslateUi(QWidget *BayWidget)
    {
        BayWidget->setWindowTitle(QApplication::translate("BayWidget", "Form", 0, QApplication::UnicodeUTF8));
        editButton->setText(QApplication::translate("BayWidget", "Edit", 0, QApplication::UnicodeUTF8));
        bayLabel->setText(QApplication::translate("BayWidget", "Bay 0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BayWidget: public Ui_BayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAYWIDGET_H
