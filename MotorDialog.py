import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from MotorDialog_ui import Ui_Dialog
from TestMotor import Motor

class FileBar(QDialog):
    """ The UI Widget which controls the loading on the file to be printed"""
    def __init__(self,name, motor,  parent=None):
        """default constructor"""
        QDialog.__init__(self, parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.motor = motor
        self.setName(name)
        
        self.setVRange(motor.getMinVelocity(), motor.getMaxVelocity())
        self.setARange(motor.getMinAcceleration(), motor.getMaxAcceleration())
        
        self.setA(motor.getAcceleration())
        self.setV(motor.getVelocity())
        
        self.ui.reverseCheckButton.setChecked(motor.isReversed())
        
        self.connect(self.ui.velocitySlider, SIGNAL("valueChanged(int)"), self.vChanged)
        self.connect(self.ui.velocitySpin, SIGNAL("valueChanged(double)"), self.vChanged)
        self.connect(self.ui.accelerationSlider, SIGNAL("valueChanged(int)"), self.aChanged)
        self.connect(self.ui.accelerationSpin, SIGNAL("valueChanged(double)"), self.aChanged)
        
        self.connect(self.ui.reverseCheckButton, SIGNAL("stateChanged(int)"), lambda x:self.motor.setReversed(self.ui.reverseCheckButton.isChecked()))
    
    def setName(self, name):
        self.ui.motorLabel.setText(name)
    
    def setVRange(self, min, max):
        self.ui.velocitySlider.setRange(min*100, max*100)
        self.ui.velocitySpin.setRange(min, max)
    
    def setARange(self, min, max):
        self.ui.accelerationSlider.setRange(min*100, max*100)
        self.ui.accelerationSpin.setRange(min, max)       

    def setA(self, value):
        self.ui.accelerationSlider.setValue(value*100)
        self.ui.accelerationSpin.setValue(value)       
    
    def setV(self, value):
        self.ui.velocitySlider.setValue(value*100)
        self.ui.velocitySpin.setValue(value)
    
    def vChanged(self, value):
        if self.sender() == self.ui.velocitySlider:
            self.ui.velocitySpin.setValue(value/100.00)
            self.motor.setVelocity(value/100.00)
        else:
            self.ui.velocitySlider.setValue(100*value)
            self.motor.setVelocity(value*100)

    
    def aChanged(self, value):
        if self.sender() == self.ui.accelerationSlider:
            self.ui.accelerationSpin.setValue(value/100.00)
            self.motor.setAcceleration(value/100.00)
        else:
            self.ui.accelerationSlider.setValue(100*value)
            self.motor.setAcceleration(value*100)    
        

if __name__ == "__main__":
    app = QApplication(sys.argv)

    myform = FileBar("test", Motor())
    myform.show()
    ##myform.setFile("testing/123.fab")
    sys.exit(app.exec_())
