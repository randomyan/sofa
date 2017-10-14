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
#ifndef SOFA_CORE_OBJECTMODEL_CONTEXTOBJECT_H
#define SOFA_CORE_OBJECTMODEL_CONTEXTOBJECT_H

#include <sofa/core/objectmodel/BaseObject.h>

namespace sofa
{

namespace core
{

namespace objectmodel
{

/**
 *  \brief Base class for simulation objects that modify the shared context (such as gravity, local coordinate system, ...).
 *
 */
class SOFA_CORE_API ContextObject : public virtual BaseObject
{
public:
    SOFA_ABSTRACT_CLASS(ContextObject, BaseObject);
    SOFA_BASE_CAST_IMPLEMENTATION(ContextObject)
protected:
    ContextObject()
        : BaseObject()
    {}

    virtual ~ContextObject()
    {}
public:
    /// modify the Context
    virtual void apply()=0;


    virtual bool insertInNode( objectmodel::BaseNode* node );
    virtual bool removeInNode( objectmodel::BaseNode* node );

};


} // namespace objectmodel

} // namespace core

} // namespace sofa

#endif

