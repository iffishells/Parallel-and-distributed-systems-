import threading
import random as rn
import time

## inherit threading class in thread module
class Philospher(threading.Thread):
    
    running = True # use to check if everyone is finished eating
    
    def __init__(self,index,forkOnleft , forkOnright):
        ## constructor 
        ## have must have initlize the base class instructor like  threading
        threading.Thread.__init(self)
        self.index =index
        self.forkOnleft = forkOnleft
        self.forkOnright = forkOnright
        
    def run(self):
        
        while(self.running):
            time.sleep(30)