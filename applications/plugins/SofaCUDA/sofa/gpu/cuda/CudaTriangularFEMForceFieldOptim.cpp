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
#include "CudaTriangularFEMForceFieldOptim.inl"
#include <sofa/core/ObjectFactory.h>
#include <sofa/core/behavior/ForceField.inl>
#include <SofaGeneralSimpleFem/TriangularFEMForceFieldOptim.inl>

namespace sofa
{

namespace component
{

namespace forcefield
{

template class SOFA_GPU_CUDA_API TriangularFEMForceFieldOptim<sofa::gpu::cuda::CudaVec3fTypes>;
}

}


namespace gpu
{

namespace cuda
{

SOFA_DECL_CLASS(CudaTriangularFEMForceFieldOptim)

int TriangularFEMForceFieldOptimCudaClass = core::RegisterObject("Supports GPU-side computations using CUDA")
        .add< component::forcefield::TriangularFEMForceFieldOptim<CudaVec3fTypes> >()
        ;

} // namespace cuda

} // namespace gpu

} // namespace sofa
