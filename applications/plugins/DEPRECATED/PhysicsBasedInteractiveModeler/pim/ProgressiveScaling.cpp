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
#define PLUGINS_PIM_PROGRESSIVESCALING_CPP
#include "ProgressiveScaling.inl"
#include <sofa/core/behavior/Constraint.inl>
#include <sofa/core/ObjectFactory.h>
#include <sofa/defaulttype/Vec3Types.h>
#include <sofa/defaulttype/RigidTypes.h>

namespace plugins
{

namespace pim
{

SOFA_DECL_CLASS(ProgressiveScaling)

int ProgressiveScalingClass = sofa::core::RegisterObject("Progresive scaling")
#ifndef SOFA_FLOAT
        .add< ProgressiveScaling<Vec3dTypes> >()
//.add< ProgressiveScaling<Rigid3dTypes> >()
#endif //SOFA_FLOAT
#ifndef SOFA_DOUBLE
        .add< ProgressiveScaling<Vec3fTypes> >()
//.add< ProgressiveScaling<Rigid3fTypes> >()
#endif //SOFA_DOUBLE
        ;

#ifndef SOFA_FLOAT
template class SOFA_COMPONENT_ENGINE_API ProgressiveScaling<Vec3dTypes>;
//template class SOFA_COMPONENT_ENGINE_API ProgressiveScaling<Rigid3dTypes>;
#endif //SOFA_FLOAT
#ifndef SOFA_DOUBLE
template class SOFA_COMPONENT_ENGINE_API ProgressiveScaling<Vec3fTypes>;
//template class SOFA_COMPONENT_ENGINE_API ProgressiveScaling<Rigid3fTypes>;
#endif //SOFA_DOUBLE

} // namespace pim

} // namespace plugins
