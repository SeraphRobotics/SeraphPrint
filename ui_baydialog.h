/********************************************************************************
** Form generated from reading UI file 'baydialog.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAYDIALOG_H
#define UI_BAYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BayDialog
{
public:
    QFrame *line1;
    QFrame *line2;
    QLabel *bayLabel;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *upButton;
    QPushButton *downButton;
    QSpacerItem *horizontalSpacer2;
    QSpacerItem *horizontalSpacer1;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout;
    QLabel *incrementLabel;
    QDoubleSpinBox *incrementSpin;
    QLabel *positionLabel;
    QDoubleSpinBox *positionSpin;
    QLabel *commandLabel;
    QDoubleSpinBox *commandSpin;
    QPushButton *acceptButton;
    QPushButton *moveButton;

    void setupUi(QDialog *BayDialog)
    {
        if (BayDialog->objectName().isEmpty())
            BayDialog->setObjectName(QString::fromUtf8("BayDialog"));
        BayDialog->resize(210, 377);
        line1 = new QFrame(BayDialog);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setGeometry(QRect(10, 190, 191, 16));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line2 = new QFrame(BayDialog);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setGeometry(QRect(20, 330, 184, 3));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        bayLabel = new QLabel(BayDialog);
        bayLabel->setObjectName(QString::fromUtf8("bayLabel"));
        bayLabel->setGeometry(QRect(16, 9, 184, 16));
        layoutWidget = new QWidget(BayDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 210, 171, 111));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        upButton = new QPushButton(layoutWidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(upButton->sizePolicy().hasHeightForWidth());
        upButton->setSizePolicy(sizePolicy);
        upButton->setMinimumSize(QSize(120, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Arrow/Aiga_uparrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon);

        gridLayout->addWidget(upButton, 0, 1, 1, 1);

        downButton = new QPushButton(layoutWidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        sizePolicy.setHeightForWidth(downButton->sizePolicy().hasHeightForWidth());
        downButton->setSizePolicy(sizePolicy);
        downButton->setMinimumSize(QSize(120, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Arrow/Aiga_downarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        downButton->setIcon(icon1);

        gridLayout->addWidget(downButton, 2, 1, 1, 1);

        horizontalSpacer2 = new QSpacerItem(20, 86, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer2, 0, 2, 3, 1);

        horizontalSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer1, 0, 0, 3, 1);

        layoutWidget_2 = new QWidget(BayDialog);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 50, 191, 131));
        formLayout = new QFormLayout(layoutWidget_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        incrementLabel = new QLabel(layoutWidget_2);
        incrementLabel->setObjectName(QString::fromUtf8("incrementLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, incrementLabel);

        incrementSpin = new QDoubleSpinBox(layoutWidget_2);
        incrementSpin->setObjectName(QString::fromUtf8("incrementSpin"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(incrementSpin->sizePolicy().hasHeightForWidth());
        incrementSpin->setSizePolicy(sizePolicy1);
        incrementSpin->setSuffix(QString::fromUtf8(" mm"));
        incrementSpin->setMinimum(0.01);
        incrementSpin->setMaximum(400);
        incrementSpin->setValue(1);

        formLayout->setWidget(0, QFormLayout::FieldRole, incrementSpin);

        positionLabel = new QLabel(layoutWidget_2);
        positionLabel->setObjectName(QString::fromUtf8("positionLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, positionLabel);

        positionSpin = new QDoubleSpinBox(layoutWidget_2);
        positionSpin->setObjectName(QString::fromUtf8("positionSpin"));
        sizePolicy1.setHeightForWidth(positionSpin->sizePolicy().hasHeightForWidth());
        positionSpin->setSizePolicy(sizePolicy1);
        positionSpin->setReadOnly(true);
        positionSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        positionSpin->setMinimum(-400);
        positionSpin->setMaximum(400);

        formLayout->setWidget(1, QFormLayout::FieldRole, positionSpin);

        commandLabel = new QLabel(layoutWidget_2);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, commandLabel);

        commandSpin = new QDoubleSpinBox(layoutWidget_2);
        commandSpin->setObjectName(QString::fromUtf8("commandSpin"));
        sizePolicy1.setHeightForWidth(commandSpin->sizePolicy().hasHeightForWidth());
        commandSpin->setSizePolicy(sizePolicy1);
        commandSpin->setSuffix(QString::fromUtf8(" mm"));
        commandSpin->setMinimum(-400);
        commandSpin->setMaximum(400);

        formLayout->setWidget(2, QFormLayout::FieldRole, commandSpin);

        acceptButton = new QPushButton(BayDialog);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(10, 340, 196, 32));
        moveButton = new QPushButton(BayDialog);
        moveButton->setObjectName(QString::fromUtf8("moveButton"));
        moveButton->setGeometry(QRect(10, 150, 194, 32));

        retranslateUi(BayDialog);

        QMetaObject::connectSlotsByName(BayDialog);
    } // setupUi

    void retranslateUi(QDialog *BayDialog)
    {
        BayDialog->setWindowTitle(QApplication::translate("BayDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        bayLabel->setText(QApplication::translate("BayDialog", "Bay 0", 0, QApplication::UnicodeUTF8));
        upButton->setText(QApplication::translate("BayDialog", "^", 0, QApplication::UnicodeUTF8));
        upButton->setShortcut(QApplication::translate("BayDialog", "Up", 0, QApplication::UnicodeUTF8));
        downButton->setText(QApplication::translate("BayDialog", "v", 0, QApplication::UnicodeUTF8));
        downButton->setShortcut(QApplication::translate("BayDialog", "Down", 0, QApplication::UnicodeUTF8));
        incrementLabel->setText(QApplication::translate("BayDialog", "Increment", 0, QApplication::UnicodeUTF8));
        positionLabel->setText(QApplication::translate("BayDialog", "Position", 0, QApplication::UnicodeUTF8));
        commandLabel->setText(QApplication::translate("BayDialog", "Command", 0, QApplication::UnicodeUTF8));
        acceptButton->setText(QApplication::translate("BayDialog", "Ok", 0, QApplication::UnicodeUTF8));
        moveButton->setText(QApplication::translate("BayDialog", "Move to Command", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BayDialog: public Ui_BayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAYDIALOG_H
