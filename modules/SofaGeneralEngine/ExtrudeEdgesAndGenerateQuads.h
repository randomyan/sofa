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
#ifndef SOFA_COMPONENT_ENGINE_EXTRUDEEDGESANDGENERATEQUADS_H
#define SOFA_COMPONENT_ENGINE_EXTRUDEEDGESANDGENERATEQUADS_H
#include "config.h"

#if !defined(__GNUC__) || (__GNUC__ > 3 || (_GNUC__ == 3 && __GNUC_MINOR__ > 3))
#pragma once
#endif

#include <sofa/defaulttype/Vec.h>
#include <sofa/core/DataEngine.h>
#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/behavior/MechanicalState.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/defaulttype/Vec3Types.h>

namespace sofa
{

namespace component
{

namespace engine
{

/**
 * This engine extrudes an edge-based curve into a quad surface patch
 */
template <class DataTypes>
class ExtrudeEdgesAndGenerateQuads : public core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(ExtrudeEdgesAndGenerateQuads,DataTypes),core::DataEngine);

    typedef typename DataTypes::Coord     Coord;
    typedef typename DataTypes::VecCoord  VecCoord;
    typedef typename DataTypes::Real      Real;
    typedef defaulttype::Vec<3,Real>      Vec3;

protected:

    ExtrudeEdgesAndGenerateQuads();

    virtual ~ExtrudeEdgesAndGenerateQuads() {}
public:

    virtual void init();
    virtual void bwdInit();
    virtual void reinit();
    virtual void update();

    virtual std::string getTemplateName() const
    {
        return templateName(this);
    }

    static std::string templateName(const ExtrudeEdgesAndGenerateQuads<DataTypes>* = NULL)
    {
        return DataTypes::Name();
    }

    bool                                             initialized;
    Data<Coord>                                      d_direction;
    Data<Real>                                       d_thickness;
    Data<Real>                                       d_thicknessIn;
    Data<Real>                                       d_thicknessOut;
    Data<int>                                        d_nbSections;
    Data<VecCoord>                                   d_curveVertices;
    Data<helper::vector<sofa::core::topology::BaseMeshTopology::Edge> >   d_curveEdges;
    Data<VecCoord>                                   d_extrudedVertices;
    Data<helper::vector<sofa::core::topology::BaseMeshTopology::Edge> >   d_extrudedEdges;
    Data<helper::vector<sofa::core::topology::BaseMeshTopology::Quad> >   d_extrudedQuads;

protected:

    void checkInput();
};

#if defined(SOFA_EXTERN_TEMPLATE) && !defined(SOFA_COMPONENT_ENGINE_EXTRUDEEDGESANDGENERATEQUADS_CPP)
#ifdef SOFA_WITH_DOUBLE
extern template class SOFA_GENERAL_ENGINE_API ExtrudeEdgesAndGenerateQuads<defaulttype::Vec3dTypes>;
#endif //SOFA_WITH_DOUBLE
#ifdef SOFA_WITH_FLOAT
extern template class SOFA_GENERAL_ENGINE_API ExtrudeEdgesAndGenerateQuads<defaulttype::Vec3fTypes>;
#endif //SOFA_WITH_FLOAT
#endif

} // namespace engine

} // namespace component

} // namespace sofa

#endif
