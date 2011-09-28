class Motor():
    def __init__(self):
        
        self.minP = 0
        self.maxP = 1000
        self.minV = 0
        self.maxV = 100
        self.minA = 1
        self.maxA = 100
        self.reversed = True
        self.currentV = 10
        self.currentA = 10
        self.currentP = 1
        self.countsPerRev = 10
    
    def resetPotion(self):
        self.currentP = 0
        
    def getCountsPerRev(self):
        return self.countsPerRev
    
    def setReversed(self,  bool):
        self.reversed = bool
        
    def isReversed(self):
        return self.reversed
        
    def getAcceleration(self):
        return self.currentA
    
    def setAcceleration(self, a):
        self.currentA = a
        
    def getMinAcceleration(self):
        return self.minA
        
    def getMaxAcceleration(self):
        return self.maxA
    
    
    def getVelocity(self):
        return self.currentV
    
    def setVelocity(self, v):
        self.currentV = v
    
    def getMinVelocity(self):
        return self.minA
        
    def getMaxVelocity(self):
        return self.maxA
    
    
    def getPosition(self):
        return self.currentP
    
    def getMinPosition(self):
        return self.minP
        
    def getMaxPosition(self):
        return self.maxP
