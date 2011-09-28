import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from BayBar_ui import Ui_Form

from BayWidget import BayWidget


class BayBar(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.bays = ()
        self.materials = []
        self.baywidgetlist = []
        
    def setBays(self, Bays):
        self.bays =Bays
        self.clearList()
        for bay in Bays:
            self.baywidgetlist.append(BayWidget(bay, self.materials, self))
        self.updateScrollBox()
            
    def clearList(self):
        for widget in self.baywidgetlist:
            self.ui.scrollAreaWidgetContents.layout().removeWidget(widget)
            widget.close()
        
        self.baywidgetlist=[]
        
    def updateScrollBox(self):
        for widget in self.baywidgetlist:
            self.ui.scrollAreaWidgetContents.layout().addWidget(widget)
            self.connect(widget,SIGNAL("materialChanged(string)"),self.materialLoaded)
    
    def materialLoaded(self, material):
        materialname = material()
        for widget in self.baywidgetlist:
            if (widget != self.sender()):
                widget.stateCheck(materialname)

    def setMaterials(self,  list):
        self.materials = list
        for widget in self.baywidgetlist:
            widget.setMaterialList(list)

if __name__ == "__main__":
    app = QApplication(sys.argv)

    from TestBay import Bay
    app = QApplication(sys.argv)
    
    bay0 = Bay(0)
    bay1 = Bay(1)
    bay2 = Bay(2)

    myform = BayBar()
    myform.setMaterials(("1", "2"))
    myform.setBays([bay0, bay1, bay2])
    
    
    myform.show()
    


    
    sys.exit(app.exec_())
