import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from LoadPrinterBar_ui import Ui_Form



class LoadPrinterBar(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ports=[]
        self.configFilePath =""
        
        self.ui.connectButton.clicked.connect(self.makeConnection)
        self.ui.changeButton.clicked.connect(self.loadConfigFile)
    
    def makeConnection(self):
        if (len(self.ports)>0): self.emit(SIGNAL("connected()")) #sent when the machine makes a connection
        else:self.emit(SIGNAL("failedToConnect()")) # sent when falure occurs
        
    def loadConfigFile(self):
        fileString = QFileDialog.getOpenFileName(self, "Load Printer config",".","*.config" )#TODO: this needs to be redone
        if fileString: self.configPath = fileString
    
    def setConfigFile(self,  fileString):
        self.configFilePath = fileString
    
    def populatePorts(self, portlist):
        self.ports=portlist
        self.ui.portCombo.clear()
        for port in portlist:
            self.ui.portCombo.addItem(port)
    
    

        
if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = LoadPrinterBar()
    myform.populatePorts(["COM1", "COM2"])
    myform.show()
    
    sys.exit(app.exec_())

