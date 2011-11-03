/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Nov 2 17:31:43 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBlah;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *connectButton;
    QPushButton *jobButton;
    QPushButton *materialsButton;
    QPushButton *printButton;
    QPushButton *backButton;
    QPushButton *forwardButton;
    QLabel *tempLabel;
    QWidget *currentWidget;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(531, 496);
        actionBlah = new QAction(MainWindow);
        actionBlah->setObjectName(QString::fromUtf8("actionBlah"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 531, 32));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(12);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        connectButton = new QPushButton(horizontalLayoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setEnabled(false);
        connectButton->setMinimumSize(QSize(60, 0));
        connectButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(connectButton);

        jobButton = new QPushButton(horizontalLayoutWidget);
        jobButton->setObjectName(QString::fromUtf8("jobButton"));
        jobButton->setEnabled(false);
        jobButton->setMinimumSize(QSize(34, 23));

        horizontalLayout->addWidget(jobButton);

        materialsButton = new QPushButton(horizontalLayoutWidget);
        materialsButton->setObjectName(QString::fromUtf8("materialsButton"));
        materialsButton->setEnabled(false);
        materialsButton->setMinimumSize(QSize(65, 0));

        horizontalLayout->addWidget(materialsButton);

        printButton = new QPushButton(horizontalLayoutWidget);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setEnabled(false);
        printButton->setMinimumSize(QSize(41, 0));

        horizontalLayout->addWidget(printButton);

        backButton = new QPushButton(centralWidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setEnabled(false);
        backButton->setGeometry(QRect(20, 290, 114, 32));
        forwardButton = new QPushButton(centralWidget);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setGeometry(QRect(400, 290, 114, 32));
        tempLabel = new QLabel(centralWidget);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));
        tempLabel->setGeometry(QRect(250, 230, 131, 20));
        currentWidget = new QWidget(centralWidget);
        currentWidget->setObjectName(QString::fromUtf8("currentWidget"));
        currentWidget->setGeometry(QRect(20, 50, 491, 221));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(currentWidget->sizePolicy().hasHeightForWidth());
        currentWidget->setSizePolicy(sizePolicy);
        currentWidget->setMinimumSize(QSize(491, 221));
        forwardButton->raise();
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 531, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionBlah->setText(QApplication::translate("MainWindow", "blah", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        jobButton->setText(QApplication::translate("MainWindow", "Job", 0, QApplication::UnicodeUTF8));
        materialsButton->setText(QApplication::translate("MainWindow", "Materials", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("MainWindow", "< Back", 0, QApplication::UnicodeUTF8));
        forwardButton->setText(QApplication::translate("MainWindow", "Forward >", 0, QApplication::UnicodeUTF8));
        tempLabel->setText(QApplication::translate("MainWindow", "Connect Widget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
