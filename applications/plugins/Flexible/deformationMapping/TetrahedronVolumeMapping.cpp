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
#define SOFA_COMPONENT_MAPPING_TetrahedronVolumeMapping_CPP

#include <Flexible/config.h>
#include "TetrahedronVolumeMapping.h"
#include <sofa/core/ObjectFactory.h>


namespace sofa
{
namespace component
{
namespace mapping
{

SOFA_DECL_CLASS(TetrahedronVolumeMapping)

using namespace defaulttype;

// Register in the Factory
int TetrahedronVolumeMappingClass = core::RegisterObject("Map deformation gradients to the invariants of the right Cauchy Green deformation tensor: I1, I2 and J")

        .add< TetrahedronVolumeMapping< Vec3Types, Vec1Types > >(true)
        ;

template class SOFA_Flexible_API TetrahedronVolumeMapping< Vec3Types, Vec1Types >;

} // namespace mapping
} // namespace component
} // namespace sofa

