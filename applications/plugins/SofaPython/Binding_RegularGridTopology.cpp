/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#include "Binding_RegularGridTopology.h"
#include "Binding_GridTopology.h"
#include "PythonToSofa.inl"

using namespace sofa::component::topology;
using namespace sofa::core::objectmodel;


/// getting a RegularGridTopology* from a PyObject*
static inline RegularGridTopology* get_RegularGridTopology(PyObject* obj) {
    return sofa::py::unwrap<RegularGridTopology>(obj);
}


static PyObject * RegularGridTopology_setPos(PyObject *self, PyObject * args)
{
    RegularGridTopology* obj = get_RegularGridTopology( self );
    double xmin,xmax,ymin,ymax,zmin,zmax;
    if (!PyArg_ParseTuple(args, "dddddd",&xmin,&xmax,&ymin,&ymax,&zmin,&zmax))
    {
        return NULL;
    }
    obj->setPos(xmin,xmax,ymin,ymax,zmin,zmax);
    Py_RETURN_NONE;
}



SP_CLASS_METHODS_BEGIN(RegularGridTopology)
SP_CLASS_METHOD(RegularGridTopology,setPos)
SP_CLASS_METHODS_END


SP_CLASS_TYPE_SPTR(RegularGridTopology,RegularGridTopology,GridTopology)



