import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from FileBar_ui import Ui_Form

class FileBar(QWidget):
    """ The UI Widget which controls the loading on the file to be printed"""
    def __init__(self, parent=None):
        """default constructor"""
        QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ui.changeFilePushButton.released.connect(self.onChangeFile)
        
    def setTime(self,  time):
        """set the time estimate value"""
        self.ui.timeSpinBox.setValue(time)
        
    def setFile(self,  fileString):
        """Handels the changes when a file is set
        """
        self.ui.volumeTreeWidget.clear()
        self.ui.fabFileLineEdit.setText(fileString)
        time = estimateTime(fileString)
        vols = estimateVolumes(fileString)
        for key in vols.keys():
            treeitem = QTreeWidgetItem()
            treeitem.setText(0, vols[key][0])
            treeitem.setText(1, QString.number(vols[key][1]))
            self.ui.volumeTreeWidget.addTopLevelItem(treeitem)
        self.setTime(time)
        self.emit(SIGNAL("fileLoaded()"))
        
    def onChangeFile(self):
        '''Launches a file dialog to load .xdfl files
        '''
        fileString = QFileDialog.getOpenFileName(self, "Load XDFL File to Print",".","*.xdfl" )#TODO: this needs to be redone
        if(fileString):
            self.setFile(fileString)


def estimateTime(fileString):
    '''a dumby function atm that will read in the properties of the material and calculates the total time the print should take
    it will return a number for the estimate time
    ''' 
    return 10.0;
    
def estimateVolumes(fileString):
    """ a function to return the volumes of hte diffrent materials used
    the return value is a dictionary with keys of the material id. 
    the dictionary contains a tuple 
    with the first value being the name of the material and the second being the volume in mm^3
    """
    dict = {}
    dict[1] = ("Silicone", 10.0)
    dict[2] = ("Cheese", 1.0)
    dict[3] = ("frosting", 12.0)
    return dict
    




if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = FileBar()
    myform.show()
    ##myform.setFile("testing/123.fab")
    sys.exit(app.exec_())
