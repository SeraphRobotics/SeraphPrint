
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from BayDialog_ui import Ui_BayDialog





class BayDialog(QDialog):
    def __init__(self, Bay,  parent=None):
        QDialog.__init__(self, parent)
        self.ui = Ui_BayDialog()
        self.ui.setupUi(self)
        self.bay = Bay
        self.ui.positionSpin.setValue(self.bay.motor.getPosition())

        self.ui.materialCombo.clear()
        self.ui.materialCombo.addItem("")
        for material in self.bay.getMaterialList():
            self.ui.materialCombo.addItem(material)
            
        index= self.ui.materialCombo.findText(self.bay.getMaterial())
        if index!=-1: self.ui.materialCombo.setCurrentIndex(index)


        self.connect(self.ui.upButton, SIGNAL("released()"), self.volUp)
        self.connect(self.ui.downButton, SIGNAL("released()"), self.volDown)
        self.connect(self.ui.materialCombo,  SIGNAL("currentIndexChanged(int)"), self.updateBayMaterial)
        
    def volUp(self):
        currentCommand = self.ui.commandSpin.value()
        increment = self.ui.incrementSpin.value()
        self.ui.commandSpin.setValue(currentCommand-increment)
        self.ui.positionSpin.setValue(currentCommand-increment)
        
    def volDown(self):
        currentCommand = self.ui.commandSpin.value()
        increment = self.ui.incrementSpin.value()
        self.ui.commandSpin.setValue(currentCommand+increment)
        self.ui.positionSpin.setValue(currentCommand+increment)
    
    def updateBayMaterial(self):
        material = self.ui.materialCombo.currentText()
        self.bay.setMaterial(material)


if __name__ == "__main__":
    from TestBay import Bay
    app = QApplication(sys.argv)
    
    bay = Bay(0)
    bay.setMaterialList(("one", "two"))
    bay.setMaterial("two")
    myform = BayDialog(bay)
    myform.show()
    
    sys.exit(app.exec_())


