/********************************************************************************
** Form generated from reading UI file 'connectwidget.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTWIDGET_H
#define UI_CONNECTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectWidget
{
public:
    QSplitter *splitter;
    QPushButton *connectButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_portL;
    QComboBox *portBox;
    QLabel *label_configL;
    QComboBox *configBox;
    QPushButton *configButton;

    void setupUi(QWidget *ConnectWidget)
    {
        if (ConnectWidget->objectName().isEmpty())
            ConnectWidget->setObjectName(QString::fromUtf8("ConnectWidget"));
        ConnectWidget->resize(545, 300);
        splitter = new QSplitter(ConnectWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(110, 110, 321, 79));
        splitter->setOrientation(Qt::Horizontal);
        connectButton = new QPushButton(splitter);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        splitter->addWidget(connectButton);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_portL = new QLabel(layoutWidget);
        label_portL->setObjectName(QString::fromUtf8("label_portL"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_portL);

        portBox = new QComboBox(layoutWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, portBox);

        label_configL = new QLabel(layoutWidget);
        label_configL->setObjectName(QString::fromUtf8("label_configL"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_configL);

        configBox = new QComboBox(layoutWidget);
        configBox->setObjectName(QString::fromUtf8("configBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, configBox);


        verticalLayout->addLayout(formLayout);

        configButton = new QPushButton(layoutWidget);
        configButton->setObjectName(QString::fromUtf8("configButton"));

        verticalLayout->addWidget(configButton);

        splitter->addWidget(layoutWidget);

        retranslateUi(ConnectWidget);

        QMetaObject::connectSlotsByName(ConnectWidget);
    } // setupUi

    void retranslateUi(QWidget *ConnectWidget)
    {
        ConnectWidget->setWindowTitle(QApplication::translate("ConnectWidget", "Form", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("ConnectWidget", "Connect to Printer", 0, QApplication::UnicodeUTF8));
        label_portL->setText(QApplication::translate("ConnectWidget", "COM Port:", 0, QApplication::UnicodeUTF8));
        label_configL->setText(QApplication::translate("ConnectWidget", "Config:", 0, QApplication::UnicodeUTF8));
        configButton->setText(QApplication::translate("ConnectWidget", "Load New Printer Configuration", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectWidget: public Ui_ConnectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTWIDGET_H
