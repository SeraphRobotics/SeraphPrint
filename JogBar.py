import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from JogBar_ui import Ui_Form



class JogBar(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ui.originButton.clicked.connect(lambda x:self.emit(SIGNAL("originSet()")))
    
    
        

if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = JogBar()
    myform.show()
    
    sys.exit(app.exec_())
