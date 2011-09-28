import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from BayWidget_ui import Ui_Form

from BayDialog import BayDialog


class BayWidget(QWidget):
    def __init__(self,Bay, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self._setBayId(Bay.getId())
        self.bay = Bay
        self.list=()
        
    def __init__(self, Bay, materiallist,  parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.bay = Bay
        self._setBayId(Bay.getId())
        self.list=()

        self.bay.setMaterialList(materiallist)
        self.setMaterialList(materiallist)
        self.ui.materialCombo.currentIndexChanged.connect(self._materialChange)
        

        self.connect(self.ui.editButton, SIGNAL("clicked()"), self._launchDialog)
        
        
    def _materialChange(self):
        self.bay.setMaterial(self.ui.materialCombo.currentText())
        self.emit(SIGNAL("materialChanged(string)"), self.material)
    
    def _setBayId(self, id):
        self._id = id
        self.ui.bayLabel.setText("Bay %i"%id)
        
    def _launchDialog(self):
        dialog = BayDialog(self.bay)
        dialog.exec_()
        index= self.ui.materialCombo.findText(self.bay.getMaterial())
        if (index!=-1): self.ui.materialCombo.setCurrentIndex(index)

    

        
    def setMaterialList(self,  list):
        self.ui.materialCombo.clear()
        self.ui.materialCombo.addItem("")
        self.bay.setMaterialList(list)
        for i in range(0, len(list)):
            self.ui.materialCombo.addItem(list[i])
        
    def material(self):
        return self.bay.getMaterial()
    
    def stateCheck(self, material):
        if (self.bay.getMaterial() == material):
            self.ui.materialCombo.setCurrentIndex(0)
        

if __name__ == "__main__":
    from TestBay import Bay
    app = QApplication(sys.argv)
    
    bay = Bay(1)
    myform = BayWidget(bay, ("1", "2"))
    myform.show()

    
    sys.exit(app.exec_())
