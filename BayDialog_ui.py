# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'BayDialog.ui'
#
# Created: Wed Jul 13 19:06:10 2011
#      by: PyQt4 UI code generator 4.5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_BayDialog(object):
    def setupUi(self, BayDialog):
        BayDialog.setObjectName("BayDialog")
        BayDialog.resize(157, 340)
        BayDialog.setModal(True)
        self.verticalLayout = QtGui.QVBoxLayout(BayDialog)
        self.verticalLayout.setObjectName("verticalLayout")
        self.materialLabel = QtGui.QLabel(BayDialog)
        self.materialLabel.setObjectName("materialLabel")
        self.verticalLayout.addWidget(self.materialLabel)
        self.materialCombo = QtGui.QComboBox(BayDialog)
        self.materialCombo.setObjectName("materialCombo")
        self.verticalLayout.addWidget(self.materialCombo)
        self.formLayout = QtGui.QFormLayout()
        self.formLayout.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
        self.formLayout.setObjectName("formLayout")
        self.incrementLabel = QtGui.QLabel(BayDialog)
        self.incrementLabel.setObjectName("incrementLabel")
        self.formLayout.setWidget(0, QtGui.QFormLayout.LabelRole, self.incrementLabel)
        self.incrementSpin = QtGui.QDoubleSpinBox(BayDialog)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.incrementSpin.sizePolicy().hasHeightForWidth())
        self.incrementSpin.setSizePolicy(sizePolicy)
        self.incrementSpin.setSuffix(" mm")
        self.incrementSpin.setMinimum(0.01)
        self.incrementSpin.setMaximum(400.0)
        self.incrementSpin.setProperty("value", QtCore.QVariant(1.0))
        self.incrementSpin.setObjectName("incrementSpin")
        self.formLayout.setWidget(0, QtGui.QFormLayout.FieldRole, self.incrementSpin)
        self.positionLabel = QtGui.QLabel(BayDialog)
        self.positionLabel.setObjectName("positionLabel")
        self.formLayout.setWidget(1, QtGui.QFormLayout.LabelRole, self.positionLabel)
        self.positionSpin = QtGui.QDoubleSpinBox(BayDialog)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.positionSpin.sizePolicy().hasHeightForWidth())
        self.positionSpin.setSizePolicy(sizePolicy)
        self.positionSpin.setReadOnly(True)
        self.positionSpin.setButtonSymbols(QtGui.QAbstractSpinBox.NoButtons)
        self.positionSpin.setMinimum(-400.0)
        self.positionSpin.setMaximum(400.0)
        self.positionSpin.setObjectName("positionSpin")
        self.formLayout.setWidget(1, QtGui.QFormLayout.FieldRole, self.positionSpin)
        self.commandLabel = QtGui.QLabel(BayDialog)
        self.commandLabel.setObjectName("commandLabel")
        self.formLayout.setWidget(2, QtGui.QFormLayout.LabelRole, self.commandLabel)
        self.commandSpin = QtGui.QDoubleSpinBox(BayDialog)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.commandSpin.sizePolicy().hasHeightForWidth())
        self.commandSpin.setSizePolicy(sizePolicy)
        self.commandSpin.setSuffix(" mm")
        self.commandSpin.setMinimum(-400.0)
        self.commandSpin.setMaximum(400.0)
        self.commandSpin.setObjectName("commandSpin")
        self.formLayout.setWidget(2, QtGui.QFormLayout.FieldRole, self.commandSpin)
        self.moveButton = QtGui.QPushButton(BayDialog)
        self.moveButton.setObjectName("moveButton")
        self.formLayout.setWidget(3, QtGui.QFormLayout.LabelRole, self.moveButton)
        self.verticalLayout.addLayout(self.formLayout)
        self.line1 = QtGui.QFrame(BayDialog)
        self.line1.setFrameShape(QtGui.QFrame.HLine)
        self.line1.setFrameShadow(QtGui.QFrame.Sunken)
        self.line1.setObjectName("line1")
        self.verticalLayout.addWidget(self.line1)
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.upButton = QtGui.QPushButton(BayDialog)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.upButton.sizePolicy().hasHeightForWidth())
        self.upButton.setSizePolicy(sizePolicy)
        self.upButton.setMinimumSize(QtCore.QSize(120, 50))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/Arrow/Aiga_uparrow.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.upButton.setIcon(icon)
        self.upButton.setObjectName("upButton")
        self.gridLayout.addWidget(self.upButton, 0, 1, 1, 1)
        self.downButton = QtGui.QPushButton(BayDialog)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.downButton.sizePolicy().hasHeightForWidth())
        self.downButton.setSizePolicy(sizePolicy)
        self.downButton.setMinimumSize(QtCore.QSize(120, 50))
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/Arrow/Aiga_downarrow.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.downButton.setIcon(icon1)
        self.downButton.setObjectName("downButton")
        self.gridLayout.addWidget(self.downButton, 2, 1, 1, 1)
        spacerItem = QtGui.QSpacerItem(20, 86, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 0, 2, 3, 1)
        spacerItem1 = QtGui.QSpacerItem(20, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem1, 0, 0, 3, 1)
        self.verticalLayout.addLayout(self.gridLayout)
        self.line2 = QtGui.QFrame(BayDialog)
        self.line2.setFrameShape(QtGui.QFrame.HLine)
        self.line2.setFrameShadow(QtGui.QFrame.Sunken)
        self.line2.setObjectName("line2")
        self.verticalLayout.addWidget(self.line2)
        self.acceptButton = QtGui.QPushButton(BayDialog)
        self.acceptButton.setObjectName("acceptButton")
        self.verticalLayout.addWidget(self.acceptButton)

        self.retranslateUi(BayDialog)
        QtCore.QObject.connect(self.acceptButton, QtCore.SIGNAL("clicked()"), BayDialog.accept)
        QtCore.QMetaObject.connectSlotsByName(BayDialog)

    def retranslateUi(self, BayDialog):
        BayDialog.setWindowTitle(QtGui.QApplication.translate("BayDialog", "Bay", None, QtGui.QApplication.UnicodeUTF8))
        self.materialLabel.setText(QtGui.QApplication.translate("BayDialog", "Material", None, QtGui.QApplication.UnicodeUTF8))
        self.incrementLabel.setText(QtGui.QApplication.translate("BayDialog", "Increment", None, QtGui.QApplication.UnicodeUTF8))
        self.positionLabel.setText(QtGui.QApplication.translate("BayDialog", "Position", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLabel.setText(QtGui.QApplication.translate("BayDialog", "Command", None, QtGui.QApplication.UnicodeUTF8))
        self.moveButton.setText(QtGui.QApplication.translate("BayDialog", "Move to Command", None, QtGui.QApplication.UnicodeUTF8))
        self.upButton.setShortcut(QtGui.QApplication.translate("BayDialog", "Up", None, QtGui.QApplication.UnicodeUTF8))
        self.downButton.setShortcut(QtGui.QApplication.translate("BayDialog", "Down", None, QtGui.QApplication.UnicodeUTF8))
        self.acceptButton.setText(QtGui.QApplication.translate("BayDialog", "Ok", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc
