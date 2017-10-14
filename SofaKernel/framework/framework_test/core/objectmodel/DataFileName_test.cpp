/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU General Public License as published by the Free  *
* Software Foundation; either version 2 of the License, or (at your option)   *
* any later version.                                                          *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for    *
* more details.                                                               *
*                                                                             *
* You should have received a copy of the GNU General Public License along     *
* with this program. If not, see <http://www.gnu.org/licenses/>.              *
*******************************************************************************
* Contributors:                                                               *
*     - damien.marchal@univ-lille1.fr                                         *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <SofaTest/Sofa_test.h>
using sofa::Sofa_test ;

#include <SofaTest/TestMessageHandler.h>
using sofa::helper::logging::Message ;
using sofa::helper::logging::ExpectMessage ;

#include <sofa/core/objectmodel/BaseObjectDescription.h>
using sofa::core::objectmodel::BaseObjectDescription ;

#include <sofa/core/objectmodel/DataFileName.h>
using sofa::core::objectmodel::DataFileName ;

#include <sofa/helper/system/FileRepository.h>
using sofa::helper::system::DataRepository ;

#include <sofa/helper/system/SetDirectory.h>
using sofa::helper::system::SetDirectory ;

#define filename "UtilsTest.ini"

class DataFileName_test: public Sofa_test<>
{
    DataFileName d_filename;
public:
    void SetUp()
    {
        DataRepository.addFirstPath( FRAMEWORK_TEST_RESOURCES_DIR );
    }

    /// These two should return the same things
    void checkSetGetValues(){
        d_filename.setValue(filename) ;
        EXPECT_EQ( filename, d_filename.getValue()) ;

        d_filename.setValue( FRAMEWORK_TEST_RESOURCES_DIR "/" filename) ;
        EXPECT_EQ( FRAMEWORK_TEST_RESOURCES_DIR "/" filename, d_filename.getValue() ) ;
    }

    /// I see no reason why asking for the full path return a short path.
    void checkSetGetFullPath(){
        d_filename.setValue(filename) ;
        EXPECT_EQ( FRAMEWORK_TEST_RESOURCES_DIR "/" filename, d_filename.getFullPath() )  ;

        d_filename.setValue(FRAMEWORK_TEST_RESOURCES_DIR "/" filename) ;
        EXPECT_EQ( FRAMEWORK_TEST_RESOURCES_DIR "/" filename, d_filename.getFullPath() ) ;
    }

    void checkSetGetRelativePath(){
        d_filename.setValue(filename) ;
        EXPECT_EQ( filename, d_filename.getRelativePath() ) ;

        d_filename.setValue(FRAMEWORK_TEST_RESOURCES_DIR "/" filename) ;
        EXPECT_EQ( filename, d_filename.getRelativePath() ) ;
    }
};

TEST_F(DataFileName_test, checkSetGetValues)
{
    this->checkSetGetValues();
}

TEST_F(DataFileName_test, checkSetGetFullPath)
{
    this->checkSetGetFullPath();
}

TEST_F(DataFileName_test, checkSetGetRelativePath)
{
    this->checkSetGetRelativePath();
}
