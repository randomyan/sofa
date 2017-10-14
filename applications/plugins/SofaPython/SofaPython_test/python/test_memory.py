import Sofa
import sys




def createScene(rootNode):
    rootNode.createObject('PythonScriptController', filename=__file__, classname="AllocationTestController")
    return rootNode




class AllocationTestController(Sofa.PythonScriptController):

    node = None
    subnode = None

    def onLoaded(self,node):
        self.node = node


    def add(self):
        # adding components in the scene, that increment a counter at each construction
        for i in xrange(10):
            self.node.createObject('PythonTestAllocationCounter')

    def remove(self):
        # removing all components, the destructor should be called, decrementing the counter
        for o in self.node.getObjects():
            self.node.removeObject(o)

    def addSub(self):
        # adding components in subnode, that increment a counter at each construction
        self.subnode = self.node.createChild('subnode')
        for i in xrange(10):
            self.subnode.createObject('PythonTestAllocationCounter')

    def removeSub(self):
        # removing subnode should remove all its components
        self.node.removeChild(self.subnode)
        self.subnode = None # this is mandatory not to keep any pointer on the python side

    def detachSub(self):
        self.subnode.detachFromGraph()
        self.subnode = None # this is mandatory not to keep any pointer on the python side