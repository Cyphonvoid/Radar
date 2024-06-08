

class Flag():

    def __init__(self, value=None):
        self.status = False
        if(isinstance(value, bool)):
            self.status = value
    
    def set_true(self):
        self.status = True
    
    def set_false(self):
        self.status = False
    
    def check(self):
        return self.status
    