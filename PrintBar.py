import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from PrintBar_ui import Ui_printbar


class PrintBar(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_printbar()
        self.ui.setupUi(self)

    


if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = PrintBar()
    myform.show()
    

    
    sys.exit(app.exec_())


