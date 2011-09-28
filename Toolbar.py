import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from ToolBar_ui import Ui_Form

PRINTER, FILE, BAYS, JOG, PRINT,  PRINTING = range(6)


class ToolBar(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.state = PRINTER
        self.stateChanged = pyqtSignal()

        self.setState(PRINTER)
        

        
    #THIS IS FOR TESTING ONLY
    def makeConnections(self):
        self.ui.printerButton.clicked.connect(lambda: self.setState(FILE))
        self.ui.fileButton.clicked.connect(lambda: self.setState(BAYS))
        self.ui.bayButton.clicked.connect(lambda: self.setState(JOG))
        self.ui.originButton.clicked.connect(lambda: self.setState(PRINT))
        self.ui.startButton.clicked.connect(lambda: self.setState(PRINTING))


    def state(self):
        return self.state
    
    def setState(self, state):
        self.state=state
        if state == PRINTER: 
            self.statePrinter()
        elif state == FILE: 
            self.stateFile()
        elif state == BAYS:
            self.stateBays()
        elif state== JOG:
            self.stateJog()
        elif state==PRINT:
            self.statePrint()
        elif state == PRINTING:
            self.statePrinting()
        self.emit(SIGNAL("stateChanged(int)"), state)
        ##self.stateChanged.emit()
    

    def statePrinter(self):
        self.ui.printerButton.setEnabled(True)
        self.ui.fileButton.setEnabled(False)
        self.ui.bayButton.setEnabled(False)
        self.ui.originButton.setEnabled(False)
        self.ui.startButton.setEnabled(False)


    def stateFile(self):
        self.ui.printerButton.setEnabled(True)
        self.ui.fileButton.setEnabled(True)
        self.ui.bayButton.setEnabled(False)
        self.ui.originButton.setEnabled(False)
        self.ui.startButton.setEnabled(False)
    
    def stateBays(self):
        self.ui.printerButton.setEnabled(True)
        self.ui.fileButton.setEnabled(True)
        self.ui.bayButton.setEnabled(True)
        self.ui.originButton.setEnabled(True)
        self.ui.startButton.setEnabled(False)
        
    def stateJog(self):
        self.ui.printerButton.setEnabled(True)
        self.ui.fileButton.setEnabled(True)
        self.ui.bayButton.setEnabled(True)
        self.ui.originButton.setEnabled(True)
        self.ui.startButton.setEnabled(False)    

    def statePrint(self):
        self.ui.printerButton.setEnabled(True)
        self.ui.fileButton.setEnabled(True)
        self.ui.bayButton.setEnabled(True)
        self.ui.originButton.setEnabled(True)
        self.ui.startButton.setEnabled(True) 

    def statePrinting(self):
        self.ui.printerButton.setEnabled(False)
        self.ui.fileButton.setEnabled(False)
        self.ui.bayButton.setEnabled(False)
        self.ui.originButton.setEnabled(False)
        self.ui.startButton.setEnabled(False)  


if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = ToolBar()
    myform.makeConnections()
    myform.show()
    
    sys.exit(app.exec_())


