from __future__ import print_function

import ctypes
import sys

class PyObject(ctypes.Structure):
    '''ctypes representation of PyObject_HEAD'''
    
    _fields_ = (
        ('ob_refcnt', ctypes.c_size_t),
        ('ob_type', ctypes.c_void_p),
    )

class SofaPySPtr(ctypes.Structure):
    '''ctypes representation of sofa PySPtr'''
    _fields_ = (
        ('head', PyObject),
        ('obj', ctypes.c_void_p),
    )

class DataPointer(ctypes.Structure):
    '''result type for c function get_data_pointer'''
    _fields_ = (
        ('ptr', ctypes.c_void_p),
        ('size', ctypes.c_uint),
    )
    
    
def sofa_pointer( obj ):
    '''returns pointer to wrapped sofa object as a ctype.c_void_p'''

    # obj -> pyobject*
    pyobj = ctypes.c_void_p(id(obj))

    # pyobject* -> pysptr
    pysptr = ctypes.cast( pyobj, ctypes.POINTER(SofaPySPtr)).contents

    # obtain wrapped object
    sofaobj = pysptr.obj
    
    return sofaobj


def load_dll():
    '''load symbols from compliant dll. you need to load compliant plugin first.'''

    ext = 'so'
    prefix = 'lib'

    import platform
    system = platform.system()

    if system == 'Windows':
        ext = 'dll'
    elif system == 'Darwin':
        ext = 'dylib'

    dll_name = '{0}Compliant.{1}'.format(prefix, ext)

    global dll
    try:
        dll = ctypes.CDLL(dll_name)
    except:
        # try debug
        dll_name = '{0}Compliant_d.{1}'.format(prefix, ext)
        dll = ctypes.CDLL(dll_name)

    # dll.get_data_pointer.restype = DataPointer
    # dll.get_data_pointer.argtypes = (ctypes.c_void_p, )

    global py_callback_type
    py_callback_type = ctypes.CFUNCTYPE(None, ctypes.c_int)

    dll.set_py_callback.restype = None
    dll.set_py_callback.argtypes = (ctypes.c_void_p, py_callback_type)



# TODO add more basic types
# check that type sizes are equivalent with c++ sizes
ctypeFromName = {
    'double': ctypes.c_double,
    'float': ctypes.c_float,
    'bool': ctypes.c_bool,
    'char': ctypes.c_char,
    'uchar': ctypes.c_ubyte,
    'short': ctypes.c_short,
    'ushort': ctypes.c_ushort,
    'int': ctypes.c_int,
    'uint': ctypes.c_uint,
    'long': ctypes.c_long,
    'ulong': ctypes.c_ulong,
}


import numpy as np
from numpy import ctypeslib

def as_numpy( data ):
    '''maps data content as a numpy array'''

    ptr, shape, typename = data.getValueVoidPtr()

    type = ctypeFromName.get(typename,None)
    if not type: raise Exception("can't map data of type " + typename)

    array = ctypes.cast( ctypes.c_void_p(ptr), ctypes.POINTER(type))
    return ctypeslib.as_array(array, shape )






# convenience
def numpy_data(obj, name):
    data = obj.findData(name)
    return as_numpy(data)




def numpy_property(*name):

    @property
    def res(self):
        return reduce(getattr, name, self)

    @res.setter
    def res(self, value):
        reduce(getattr, name, self)[:] = value
        
    return res

from itertools import izip

def numpy_item_property(*name):

    class ItemProperty(object):

        def __init__(self, data):
            self.data = data
            
        def __getitem__(self, index):
            return self.data[index]

        def __setitem__(self, index, value):
            self.data[index][:] = value

        def __len__(self):
            return len(self.data)

        def __iter__(self):
            for x in self.data: yield x

        def __str__(self):
            return np.array_str(np.array(self.data))
            
    @property
    def res(self):
        data = reduce(getattr, name, self)
        return ItemProperty(data)

    @res.setter
    def res(self, value):
        data = reduce(getattr, name, self)
        for x, v in zip(data, value):
            x[:] = v
    
    return res

# TODO enable gs based on update_gs presence in derived classes
class Mapping(object):
    '''wraps a PythonMultiMapping into something more usable'''

    _instances_ = []
    
    def __init__(self, node, **kwargs):

        
        self.node = node

        self.src = kwargs['input'] 
        self.dst = kwargs['output']

        kwargs['template'] = '{0},{1}'.format( self.src[0].getTemplateName(),
                                               self.dst.getTemplateName())
        
        kwargs['input'] = multi_mapping_input(node, *self.src)
        kwargs['output'] = object_link_relative(node, self.dst)


        self.obj = node.createObject('PythonMultiMapping', **kwargs)
        
        self.init()

        # callback
        def callback(state):

            try:
                if state == 0:
                    self.on_apply()
                elif state == 1:
                    self.on_stiffness(self._out_force)
                else: raise Exception('unknown callback state')
                
            except Exception as e:
                # print('callback error:', e)
                raise

        # keep a handle on self/closure to prevent gc
        Mapping._instances_.append(self)
        
        self._cb = py_callback_type(callback)
        dll.set_py_callback( sofa_pointer(self.obj), self._cb )

        # post-initialization
        self.on_init()
        
    def on_init(self):
        '''called after init'''

    def on_apply(self):
        '''called when value/jacobian are required'''
        pass
    
    def on_stiffness(self, out_force):
        '''called when geometric_stiffness is required'''
        pass
    
    def init(self):
        '''update stuff after input/output resize'''

        pos = 'position'        
        vel = 'velocity'

        self._out_vel = numpy_data(self.dst, vel)
        self._out_pos = numpy_data(self.dst, pos)

        self._in_vel = [ numpy_data(s, vel) for s in self.src ]
        self._in_pos = [ numpy_data(s, pos) for s in self.src ]
        
        # out dim
        self.m, out_dim = self._out_vel.shape
        
        # in dim
        self.n = sum( v.shape[0] for v in self.in_vel  )
        in_dim = self.in_vel[0].shape[1]
        
        # resize jacobian/value data
        size = self.m * self.n * in_dim * out_dim
        
        self.obj.jacobian = [0] * size
        self.obj.value = [0] * (self.m * out_dim )
        
        # map numpy arrays
        self._jacobian = numpy_data(self.obj, 'jacobian')
        self._value = numpy_data(self.obj, 'value')

        # reshape jacobian
        self._jacobian = self._jacobian.reshape(self.m * out_dim, self.n * in_dim)

        # geometric stiffness
        if self.obj.use_geometric_stiffness:

            size = self.n * in_dim * self.n * in_dim
            
            self.obj.geometric_stiffness = [0] * size
            self.obj.out_force = [0] * (self.m * out_dim)
            
            self._gs = numpy_data(self.obj, 'geometric_stiffness')
            self._gs = self._gs.reshape( self.n * in_dim, self.n * in_dim)
            self._out_force = numpy_data(self.obj, 'out_force')


    # properties
    jacobian = numpy_property('_jacobian')
    value = numpy_property('_value')

    out_vel = numpy_property('_out_vel')
    out_pos = numpy_property('_out_pos')    

    in_vel = numpy_item_property('_in_vel')
    in_pos = numpy_item_property('_in_pos')    

    geometric_stiffness = numpy_property('_gs')    


    def in_vel_stack(self):
        '''concatenation of all input velocities'''
        return np.hstack( tuple(v[i] for v in self.in_vel for i in xrange(len(v))) )
    
def cat(x):
    return ' '.join(map(str, x))


class Constraint(Mapping):
    '''wraps mapping/state/compliance to build arbitrary constraints
    (setting mapping output to zero, possibly with compilance)'''

    def __init__(self, name, node, dim, **kwargs):

        if ' ' in name: raise Exception('space in constraint name')
        
        if 'output' in kwargs:
            raise Exception('can not have output in constraints')

        # constraint node
        node = node.createChild(name)
        
        self.dim = dim

        # create dofs
        dofs = node.createObject('MechanicalObject',
                                 template = 'Vec1d',
                                 name = 'dofs',
                                 position = cat(np.zeros(dim)),
                                 velocity = cat(np.zeros(dim)))
        
        kwargs['output'] = dofs

        # create mapping
        Mapping.__init__(self, node, **kwargs)

        # compliance
        self.compliance = kwargs.get('compliance', 0)

        # TODO auto-update compliance ?
        self.ff = node.createObject('UniformCompliance',
                                    template = 'Vec1d',
                                    name = 'ff',
                                    compliance = self.compliance)
        
                                    
        

class ForceField(object):
    '''wraps mapping/state/ff to build arbitrary forcefields'''
    
    def __init__(self, node, **kwargs):
        # object.__init__(self)
        
        if 'output' in kwargs:
            raise Exception('can not have output in force field')

        self.node = node 
        self.dofs = node.createObject('MechanicalObject',
                                      template = 'Vec1d',
                                      name = 'dofs',
                                      position = '0')

        kwargs['output'] = self.dofs

        class Energy(Mapping):

            def on_apply(self):
                self.owner.on_force()

            def on_stiffness(self, out_force):
                self.owner.on_stiffness(out_force)

        self._mapping = Energy(node, **kwargs)
        self._mapping.owner = self
        
        self.init(False)

        self._ff = node.createObject('PotentialEnergy')
        

    def on_force(): pass
    def on_stiffness(self, arg): pass
        
    def init(self, init_mapping = True):
        if init_mapping: self._mapping.init()

        self._force = self._mapping.jacobian[0]
        self._energy = self._mapping.value[0]

        if self._mapping.obj.use_geometric_stiffness:
            self._stiffness = self._mapping.geometric_stiffness

            
    energy = numpy_property('_energy')
    force = numpy_property('_force')
    stiffness = numpy_property('_stiffness')

    out_pos = numpy_property('_mapping', 'out_pos')
    out_vel = numpy_property('_mapping', 'out_vel')    
    
    in_pos = numpy_item_property('_mapping', 'in_pos')
    in_vel = numpy_item_property('_mapping', 'in_vel')    
    
    
from Tools import node_path_rel as node_path_relative

def object_link_relative(node, obj):
    '''object link string relative to a given node'''
    return '@{0}/{1}'.format( node_path_relative(node, obj.getContext() ), obj.name )

def multi_mapping_input(node, *dofs ):
    '''multimapping input field from a list of dofs'''
    return ' '.join( object_link_relative(node, x) for x in dofs )


def find_node(node, path):
    '''find node given relative path'''
    
    path = path.split('@')[-1]
    path = path.split('/')

    for p in path:
        if p == '..':
            node = node.getParents()[0]
        else:
            node = node.getChild(p)

    return node

def find_object(node, path):
    '''find object given relative path'''
    
    split = path.split('/')

    path = '/'.join( split[:-1] )
    name = split[-1]

    res = find_node(node, path).getObject(name)
    return res
