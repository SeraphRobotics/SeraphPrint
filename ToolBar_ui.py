# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Toolbar.ui'
#
# Created: Wed Jul 13 21:41:14 2011
#      by: PyQt4 UI code generator 4.5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(703, 68)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Form.sizePolicy().hasHeightForWidth())
        Form.setSizePolicy(sizePolicy)
        Form.setMinimumSize(QtCore.QSize(703, 68))
        Form.setMaximumSize(QtCore.QSize(16777215, 68))
        self.horizontalLayout = QtGui.QHBoxLayout(Form)
        self.horizontalLayout.setSizeConstraint(QtGui.QLayout.SetDefaultConstraint)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.printerButton = QtGui.QPushButton(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.printerButton.sizePolicy().hasHeightForWidth())
        self.printerButton.setSizePolicy(sizePolicy)
        self.printerButton.setMinimumSize(QtCore.QSize(125, 50))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.printerButton.setFont(font)
        self.printerButton.setFlat(True)
        self.printerButton.setObjectName("printerButton")
        self.horizontalLayout.addWidget(self.printerButton)
        self.line = QtGui.QFrame(Form)
        self.line.setFrameShape(QtGui.QFrame.VLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName("line")
        self.horizontalLayout.addWidget(self.line)
        self.fileButton = QtGui.QPushButton(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.fileButton.sizePolicy().hasHeightForWidth())
        self.fileButton.setSizePolicy(sizePolicy)
        self.fileButton.setMinimumSize(QtCore.QSize(125, 50))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.fileButton.setFont(font)
        self.fileButton.setFlat(True)
        self.fileButton.setObjectName("fileButton")
        self.horizontalLayout.addWidget(self.fileButton)
        self.line_4 = QtGui.QFrame(Form)
        self.line_4.setFrameShape(QtGui.QFrame.VLine)
        self.line_4.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_4.setObjectName("line_4")
        self.horizontalLayout.addWidget(self.line_4)
        self.bayButton = QtGui.QPushButton(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.bayButton.sizePolicy().hasHeightForWidth())
        self.bayButton.setSizePolicy(sizePolicy)
        self.bayButton.setMinimumSize(QtCore.QSize(125, 50))
        self.bayButton.setFlat(True)
        self.bayButton.setObjectName("bayButton")
        self.horizontalLayout.addWidget(self.bayButton)
        self.line_2 = QtGui.QFrame(Form)
        self.line_2.setFrameShape(QtGui.QFrame.VLine)
        self.line_2.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.horizontalLayout.addWidget(self.line_2)
        self.originButton = QtGui.QPushButton(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.originButton.sizePolicy().hasHeightForWidth())
        self.originButton.setSizePolicy(sizePolicy)
        self.originButton.setMinimumSize(QtCore.QSize(125, 50))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.originButton.setFont(font)
        self.originButton.setFlat(True)
        self.originButton.setObjectName("originButton")
        self.horizontalLayout.addWidget(self.originButton)
        self.line_3 = QtGui.QFrame(Form)
        self.line_3.setFrameShape(QtGui.QFrame.VLine)
        self.line_3.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_3.setObjectName("line_3")
        self.horizontalLayout.addWidget(self.line_3)
        self.startButton = QtGui.QPushButton(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.startButton.sizePolicy().hasHeightForWidth())
        self.startButton.setSizePolicy(sizePolicy)
        self.startButton.setMinimumSize(QtCore.QSize(125, 50))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.startButton.setFont(font)
        self.startButton.setFlat(True)
        self.startButton.setObjectName("startButton")
        self.horizontalLayout.addWidget(self.startButton)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.printerButton.setText(QtGui.QApplication.translate("Form", "Load Printer", None, QtGui.QApplication.UnicodeUTF8))
        self.fileButton.setText(QtGui.QApplication.translate("Form", "Print File", None, QtGui.QApplication.UnicodeUTF8))
        self.bayButton.setText(QtGui.QApplication.translate("Form", "Load Bays", None, QtGui.QApplication.UnicodeUTF8))
        self.originButton.setText(QtGui.QApplication.translate("Form", "Set Origin", None, QtGui.QApplication.UnicodeUTF8))
        self.startButton.setText(QtGui.QApplication.translate("Form", "Start Print", None, QtGui.QApplication.UnicodeUTF8))

