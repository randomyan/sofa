import __builtin__
import sys
import inspect
import traceback
import Sofa

## @contributors
##   - Matthieu Nesme
##   - Maxime Tournier
##   - damien.marchal@univ-lille1.fr
##
## @date 2017

# Keep a list of the modules always imported in the Sofa-PythonEnvironment
try:
    __SofaPythonEnvironment_importedModules__
except:
    __SofaPythonEnvironment_importedModules__ = sys.modules.copy()

    # some modules could be added here manually and can be modified procedurally
    # e.g. plugin's modules defined from c++
    __SofaPythonEnvironment_modulesExcludedFromReload = []



def unloadModules():
    """ call this function to unload python modules and to force their reload
        (useful to take into account their eventual modifications since
        their last import).
    """
    global __SofaPythonEnvironment_importedModules__
    toremove = [name for name in sys.modules if not name in __SofaPythonEnvironment_importedModules__ and not name in __SofaPythonEnvironment_modulesExcludedFromReload ]
    for name in toremove:
        del(sys.modules[name]) # unload it


def formatStackForSofa(o):
    """ format the stack trace provided as a parameter into a string like that:
        in filename.py:10:functioname()
          -> the line of code.
        in filename2.py:101:functioname1()
            -> the line of code.
        in filename3.py:103:functioname2()
              -> the line of code.
    """
    ss='Python Stack: \n'
    for entry in o:
        ss+= ' in ' + str(entry[1]) + ':' + str(entry[2]) + ':'+ entry[3] + '()  \n'
        ss+= '  -> '+ entry[4][0] + '  \n'
        return ss

def getStackForSofa():
    """returns the current stack with a "informal" formatting. """
    ## we exclude the first level in the stack because it is the getStackForSofa() function itself.
    ss=inspect.stack()[1:]
    return formatStackForSofa(ss)

def getPythonCallingPointAsString():
    """returns the last entry with an "informal" formatting. """
    ## we exclude the first level in the stack because it is the getStackForSofa() function itself.
    ss=inspect.stack()[-1:]
    return formatStackForSofa(ss)

def getPythonCallingPoint():
    """returns the tupe with closest filename & line. """
    ## we exclude the first level in the stack because it is the getStackForSofa() function itself.
    ss=inspect.stack()[1]
    return (ss[1], ss[2])

def sofaExceptHandler(type, value, tb):
    """This exception handler, convert python exceptions & traceback into more classical sofa error messages of the form:
       Message Description
       Python Stack:
          File file1.py line 4  ...
          File file1.py line 10 ...
          File file1.py line 40 ...
          File file1.py line 23 ...
            faulty line
    """
    s="\nPython Stack: \n"
    for line in traceback.format_tb(tb):
        s += line

    Sofa.msg_error(str(value)+" "+s, "line", 7)

sys.excepthook=sofaExceptHandler

class Controller(Sofa.PythonScriptController):

    def __init__(self, node, *args, **kwargs):
        Sofa.msg_warning('SofaPython', 'SofaPython.Controller is intended as compatibility class only')

        # setting attributes from kwargs
        for name, value in kwargs.iteritems():
            setattr(self, name, value)

        # call createGraph for compatibility purposes
        self.createGraph(node)

        # check whether derived class has 'onLoaded'
        cls = type(self)
        if not cls.onLoaded is Sofa.PythonScriptController.onLoaded:
            Sofa.msg_warning('SofaPython',
                             '`onLoaded` is defined in subclass but will not be called in the future' )
