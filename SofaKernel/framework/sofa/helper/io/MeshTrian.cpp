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
#include <sofa/helper/io/MeshTrian.h>
#include <sofa/helper/system/FileRepository.h>
#include <sofa/helper/system/Locale.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include <cstdio>

/// This allow MeshTrian to interact with the messaging system.
MSG_REGISTER_CLASS(sofa::helper::io::MeshTrian, "MeshTrian")

namespace sofa
{

namespace helper
{

namespace io
{

using namespace sofa::defaulttype;

SOFA_DECL_CLASS(MeshTrian)

Creator<Mesh::FactoryMesh,MeshTrian> MeshTrianClass("trian");

void MeshTrian::init (std::string filename)
{
    if (!sofa::helper::system::DataRepository.findFile(filename))
    {
        msg_error() << "File '" << filename << "' not found." ;
        return;
    }
    FILE *f = fopen(filename.c_str(), "r");
    if (f)
    {
        readTrian (f);
        fclose(f);
    }
    else
        msg_error() << "File '" << filename << "' not found." ;
}

void MeshTrian::readTrian (FILE* file)
{
    // Make sure that fscanf() uses a dot '.' as the decimal separator.
    helper::system::TemporaryLocale locale(LC_NUMERIC, "C");

    int nbp=0;

    if (fscanf(file, "%d\n", &nbp) == EOF)
        msg_error() << "fscanf function has encountered an error." ;

    vertices.resize(nbp);
    Vec3d fromFile;
    for (int p=0; p<nbp; p++)
    {
        if (fscanf(file, "%lf %lf %lf\n", &fromFile[0], &fromFile[1], &fromFile[2]) == EOF)
            msg_error() << "fscanf function has encountered an error." ;
        vertices[p][0] = (SReal)fromFile[0];
        vertices[p][1] = (SReal)fromFile[1];
        vertices[p][2] = (SReal)fromFile[2];
    }

    int nbf=0;
    if (fscanf(file, "%d\n", &nbf) == EOF )
        msg_error() << "fscanf function has encountered an error." ;

    facets.resize(nbf);
    for (int f=0; f<nbf; f++)
    {
        facets[f].resize(3);
        facets[f][0].resize(3);
        facets[f][1].resize(3);
        facets[f][2].resize(3);
        int dummy = 0;
        if ( fscanf(file, "%d %d %d %d %d %d\n", &facets[f][0][0], &facets[f][0][1], &facets[f][0][2], &dummy, &dummy, &dummy) == EOF )
            msg_error() << "fscanf function has encountered an error." ;
    }

    if (vertices.size()>0)
    {
        // compute bbox
        Vector3 minBB = vertices[0];
        Vector3 maxBB = vertices[0];
        for (unsigned int i=1; i<vertices.size(); i++)
        {
            Vector3 p = vertices[i];
            for (int c=0; c<3; c++)
            {
                if (minBB[c] > p[c])
                    minBB[c] = p[c];
                if (maxBB[c] < p[c])
                    maxBB[c] = p[c];
            }
        }
    }

}

} // namespace io

} // namespace helper

} // namespace sofa

