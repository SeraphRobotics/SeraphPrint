import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *


from Toolbar import *
from PrintBar import PrintBar
from FileBar import FileBar
from BayBar import BayBar
from JogBar import JogBar
from LoadPrinterBar import LoadPrinterBar



class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.toolbar = ToolBar()
        
        self.loadprinterbar = LoadPrinterBar()
        self.filebar = FileBar()
        self.baybar = BayBar()
        self.jogbar = JogBar()
        self.printbar = PrintBar()
        
        self.hline = QFrame()
        self.hline.setFrameShape(QFrame.HLine)
        self.hline.setFrameShadow(QFrame.Sunken)
        self.hline.setLineWidth(2)
        self.hline.setMidLineWidth(1)
        
        self.setCentralWidget(QWidget())
        self.centrallayout  = QVBoxLayout(self)
        self.centralWidget().setLayout(self.centrallayout)
        self.centrallayout.addWidget(self.toolbar)
        self.centrallayout.addWidget(self.hline)
        
        self.currentWidget = self.loadprinterbar
        self.centrallayout.addWidget(self.loadprinterbar)
        self.state = PRINTER
        self.makeConnections()
        
    def makeConnections(self):
        self.connect(self.loadprinterbar, SIGNAL("connected()"), lambda:self.setState(FILE))
        self.connect(self.filebar, SIGNAL("fileLoaded()"), lambda:self.setState(BAYS))
        self.connect(self.jogbar, SIGNAL("originSet()"), lambda:self.setState(PRINT))
        
        self.toolbar.ui.printerButton.clicked.connect(lambda:self.setState(PRINTER))
        self.toolbar.ui.fileButton.clicked.connect(lambda:self.setState(FILE))
        self.toolbar.ui.bayButton.clicked.connect(lambda:self.setState(BAYS))
        self.toolbar.ui.originButton.clicked.connect(lambda:self.setState(JOG))
        self.toolbar.ui.startButton.clicked.connect(lambda:self.setState(PRINTING))
        
    def setState(self, state):
        self.state = state
        self.centrallayout.removeWidget(self.currentWidget)
        self.currentWidget.hide()
        if (state == PRINTER):
            self.currentWidget = self.loadprinterbar
        elif (state == FILE):
            self.currentWidget = self.filebar
        elif (state == BAYS):
            self.currentWidget = self.baybar
        elif (state == JOG):
            self.currentWidget = self.jogbar   
        elif (state == PRINTING):
            self.currentWidget = self.printbar
        self.centrallayout.addWidget(self.currentWidget)
        self.toolbar.setState(state)
        self.currentWidget.show()
    
    

    
    
if __name__ == "__main__":
    from TestBay import Bay
    app = QApplication(sys.argv)

    myform = MainWindow()
    
    myform.loadprinterbar.populatePorts(["COM1", "COM2"])
    
    
    bay0 = Bay(0)
    bay1 = Bay(1)
    bay2 = Bay(2)


    myform.baybar.setMaterials(("Cheese", "Silicone", "Frosting"))
    myform.baybar.setBays([bay0, bay1, bay2])
    
    
    myform.show()
    

    
    sys.exit(app.exec_())
