 
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
#ifndef SOFA_COMPONENT_ENGINE_SumEngine_H
#define SOFA_COMPONENT_ENGINE_SumEngine_H

#include "config.h"
#include <sofa/core/DataEngine.h>
#include <sofa/defaulttype/Vec.h>

namespace sofa
{

namespace component
{

namespace engine
{

/// Computing the Sum between two vector of dofs
/// output = input - substractor
template <class TDataType>
class SumEngine : public core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(SumEngine,TDataType),core::DataEngine);

    typedef TDataType DataType;
    typedef helper::vector<DataType> VecData;


    SumEngine();

    virtual ~SumEngine() {}

    void init();

    void reinit();

    void update();

    virtual std::string getTemplateName() const
    {
        return templateName(this);
    }

    static std::string templateName(const SumEngine<TDataType>* = NULL)
    {
        return defaulttype::DataTypeInfo<TDataType>::name();
    }


protected:

    Data<VecData> d_input;
    Data<DataType> d_output;

};

#if defined(SOFA_EXTERN_TEMPLATE) && !defined(SOFA_COMPONENT_ENGINE_SumEngine_CPP)
#ifndef SOFA_FLOAT
extern template class SOFA_GENERAL_ENGINE_API SumEngine<defaulttype::Vec1d>;
extern template class SOFA_GENERAL_ENGINE_API SumEngine<defaulttype::Vec3d>;
#endif
#ifndef SOFA_DOUBLE
extern template class SOFA_GENERAL_ENGINE_API SumEngine<defaulttype::Vec1f>;
extern template class SOFA_GENERAL_ENGINE_API SumEngine<defaulttype::Vec3f>;
#endif
#endif

} // namespace engine

} // namespace component

} // namespace sofa

#endif
