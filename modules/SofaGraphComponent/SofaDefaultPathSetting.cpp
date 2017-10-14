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

#include <SofaGraphComponent/SofaDefaultPathSetting.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/core/ObjectFactory.h>
#include <sofa/helper/system/FileRepository.h>
#include <sofa/helper/system/SetDirectory.h>

namespace sofa
{

namespace component
{

namespace configurationsetting
{

SOFA_DECL_CLASS(SofaDefaultPathSetting)
int SofaDefaultPathSettingClass = core::RegisterObject("Default Paths for Sofa Application")
        .add< SofaDefaultPathSetting >()
        .addAlias("SofaDefaultPath")
        ;

SofaDefaultPathSetting::SofaDefaultPathSetting():
    recordPath(initData(&recordPath, "recordPath", "Path where will be saved the data of the recorded simulation"))
    , gnuplotPath(initData(&gnuplotPath, "gnuplotPath", "Path where will be saved the gnuplot files"))
{

}
}

}

}
