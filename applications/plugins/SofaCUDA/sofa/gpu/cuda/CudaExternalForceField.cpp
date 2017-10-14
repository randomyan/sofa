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
#include "CudaTypes.h"
#include "CudaExternalForceField.inl"
#include <sofa/core/ObjectFactory.h>
//#include <typeinfo>


namespace sofa
{

namespace gpu
{

namespace cuda
{

SOFA_DECL_CLASS(CudaExternalForceField)
int ExternalForceFieldCudaClass = core::RegisterObject("Supports GPU-side computations using CUDA")
        .add< component::interactionforcefield::ExternalForceField<CudaVec3fTypes> >()
        .add< component::interactionforcefield::ExternalForceField<CudaVec3f1Types> >()
        ;



} // namespace interactionforcefield

} // namespace component

} // namespace sofa

