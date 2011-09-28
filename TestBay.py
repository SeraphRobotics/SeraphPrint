from TestMotor import Motor

class Bay():
    def __init__(self, id):
        self.motor = Motor()
        self.material = ""
        self.materialList =[]
        self._id = id
    
    def setMaterial(self,  materialName):
        self.material = materialName
        
    def getMaterial(self):
        return self.material
    
    def getId(self):
        return self._id
    
    def setMaterialList(self, list):
        self.materialList=list
    
    def getMaterialList(self):
        return self.materialList
