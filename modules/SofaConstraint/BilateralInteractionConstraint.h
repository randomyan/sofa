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
#ifndef SOFA_COMPONENT_CONSTRAINTSET_BILATERALINTERACTIONCONSTRAINT_H
#define SOFA_COMPONENT_CONSTRAINTSET_BILATERALINTERACTIONCONSTRAINT_H
#include "config.h"

#include <sofa/core/behavior/PairInteractionConstraint.h>
#include <sofa/core/behavior/MechanicalState.h>

#include <sofa/defaulttype/Mat.h>
#include <sofa/defaulttype/RigidTypes.h>
#include <sofa/defaulttype/Vec.h>
#include <sofa/defaulttype/VecTypes.h>

#include <sofa/core/objectmodel/Event.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/simulation/AnimateEndEvent.h>
#include <sofa/core/objectmodel/KeypressedEvent.h>
#include <sofa/core/objectmodel/KeyreleasedEvent.h>

#include <deque>

#include <SofaConstraint/BilateralConstraintResolution.h>

namespace sofa
{

namespace component
{

namespace constraintset
{


namespace bilateralinteractionconstraint
{
/// These 'using' are in a per-file namespace so they will not leak
/// and polluate the standard namespace.
using sofa::core::behavior::BaseConstraint ;
using sofa::core::behavior::ConstraintResolution ;
using sofa::core::behavior::PairInteractionConstraint ;
using sofa::core::objectmodel::Data ;
using sofa::core::ConstraintParams ;
using sofa::core::ConstVecCoordId;

using sofa::defaulttype::BaseVector ;
using sofa::defaulttype::Quaternion ;
using sofa::defaulttype::Vec3d ;

#ifdef SOFA_WITH_DOUBLE
    using sofa::defaulttype::Rigid3dTypes ;
    using sofa::defaulttype::Vec3dTypes ;
#endif //
#ifdef SOFA_WITH_FLOAT
    using sofa::defaulttype::Rigid3fTypes ;
    using sofa::defaulttype::Vec3fTypes ;
#endif //

template<class T>
class BilateralInteractionConstraintSpecialization {};


template<class DataTypes>
class BilateralInteractionConstraint : public PairInteractionConstraint<DataTypes>
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(BilateralInteractionConstraint,DataTypes),
               SOFA_TEMPLATE(PairInteractionConstraint,DataTypes));

    /// That any templates variation of BilateralInteractionConstraintSpecialization are friend.
    template<typename>
    friend class BilateralInteractionConstraintSpecialization ;

    typedef PairInteractionConstraint<DataTypes> Inherit;

    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::VecDeriv VecDeriv;
    typedef typename DataTypes::MatrixDeriv MatrixDeriv;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::Deriv Deriv;
    typedef typename Coord::value_type Real;
    typedef typename DataTypes::MatrixDeriv::RowIterator MatrixDerivRowIterator;

    typedef core::behavior::MechanicalState<DataTypes> MechanicalState;
    typedef BaseConstraint::PersistentID PersistentID;

    typedef Data<VecCoord>		DataVecCoord;
    typedef Data<VecDeriv>		DataVecDeriv;
    typedef Data<MatrixDeriv>    DataMatrixDeriv;

protected:
    std::vector<Deriv> dfree;
    Quaternion q;

    std::vector<unsigned int> cid;

    Data<helper::vector<int> > m1;
    Data<helper::vector<int> > m2;
    Data<VecDeriv> restVector;    
    VecCoord initialDifference;

    Data<double> d_numericalTolerance;
    Data<int> activateAtIteration;
    Data<bool> merge;
    Data<bool> derivative;
    Data<bool> keepOrientDiff;
    std::vector<Vec3d> prevForces;

    // grouped square constraints
    bool squareXYZ[3];
    Deriv dfree_square_total;


    bool activated;
    int iteration;

    BilateralInteractionConstraint(MechanicalState* object1,
                                   MechanicalState* object2) ;
    BilateralInteractionConstraint(MechanicalState* object) ;
    BilateralInteractionConstraint() ;

    virtual ~BilateralInteractionConstraint(){}
public:
    virtual void init();

    virtual void bwdInit() {}

    virtual void reinit();

    virtual void reset();

    void buildConstraintMatrix(const ConstraintParams* cParams,
                               DataMatrixDeriv &c1, DataMatrixDeriv &c2,
                               unsigned int &cIndex,
                               const DataVecCoord &x1, const DataVecCoord &x2);

    void getConstraintViolation(const ConstraintParams* cParams,
                                BaseVector *v,
                                const DataVecCoord &x1, const DataVecCoord &x2,
                                const DataVecDeriv &v1, const DataVecDeriv &v2);

    void getVelocityViolation(BaseVector *v,
                              const DataVecCoord &x1, const DataVecCoord &x2,
                              const DataVecDeriv &v1, const DataVecDeriv &v2);

    virtual void getConstraintResolution(const ConstraintParams* cParams,
                                         std::vector<ConstraintResolution*>& resTab,
                                         unsigned int& offset);

    void handleEvent(sofa::core::objectmodel::Event *event);

    void draw(const core::visual::VisualParams* vparams);

    void clear(int reserve = 0) ;

    virtual void addContact(Deriv norm, Coord P, Coord Q, Real contactDistance,
                            int m1, int m2, Coord Pfree, Coord Qfree,
                            long id=0, PersistentID localid=0);

    void addContact(Deriv norm, Coord P, Coord Q, Real contactDistance,
                    int m1, int m2, long id=0, PersistentID localid=0) ;

    void addContact(Deriv norm, Real contactDistance, int m1, int m2,
                    long id=0, PersistentID localid=0) ;

private:
     void unspecializedInit() ;
};

#ifdef SOFA_WITH_DOUBLE
template<>
void BilateralInteractionConstraint<Rigid3dTypes>::buildConstraintMatrix(const ConstraintParams *cParams,
                                                                                      DataMatrixDeriv &c1_d, DataMatrixDeriv &c2_d,
                                                                                      unsigned int &cIndex
        , const DataVecCoord &x1, const DataVecCoord &x2);

template<>
void BilateralInteractionConstraint<Rigid3dTypes>::getConstraintViolation(const ConstraintParams *cParams,
                                                                                       BaseVector *v, const DataVecCoord &x1_d, const DataVecCoord &x2_d
        , const DataVecDeriv &v1_d, const DataVecDeriv &v2_d);

template<>
void BilateralInteractionConstraint<Rigid3dTypes>::addContact(Deriv /*norm*/,
                                                                           Coord P, Coord Q, Real /*contactDistance*/,
                                                                           int m1, int m2, Coord /*Pfree*/,
                                                                           Coord /*Qfree*/, long /*id*/, PersistentID /*localid*/);

#endif

#ifdef SOFA_WITH_FLOAT
template<>
void BilateralInteractionConstraint<Rigid3fTypes>::buildConstraintMatrix(const ConstraintParams *cParams,
                                                                                      DataMatrixDeriv &c1_d, DataMatrixDeriv &c2_d,
                                                                                      unsigned int &cIndex
        , const DataVecCoord &x1_d, const DataVecCoord &x2_d);

template<>
void BilateralInteractionConstraint<Rigid3fTypes>::getConstraintViolation(const ConstraintParams *cParams,
                                                                                       BaseVector *v,
                                                                                       const DataVecCoord &x1_d, const DataVecCoord &x2_d
        , const DataVecDeriv &v1_d, const DataVecDeriv &v2_d);

template<>
void BilateralInteractionConstraint<Rigid3fTypes>::addContact(Deriv /*norm*/, Coord P, Coord Q, Real /*contactDistance*/, int m1, int m2, Coord /*Pfree*/, Coord /*Qfree*/, long /*id*/, PersistentID /*localid*/);
#endif

#if defined(SOFA_EXTERN_TEMPLATE) && !defined(SOFA_BUILD_CONSTRAINT)
#ifdef SOFA_WITH_DOUBLE
extern template class SOFA_CONSTRAINT_API BilateralInteractionConstraint< Vec3dTypes >;
extern template class SOFA_CONSTRAINT_API BilateralInteractionConstraint< Rigid3dTypes >;
#endif
#ifdef SOFA_WITH_FLOAT
extern template class SOFA_CONSTRAINT_API BilateralInteractionConstraint< Vec3fTypes >;
extern template class SOFA_CONSTRAINT_API BilateralInteractionConstraint< Rigid3fTypes >;
#endif
#endif

} // namespace bilateralinteractionconstraint

/// Import the following into the constraintset namespace to preserve
/// compatibility with the existing sofa source code.
using bilateralinteractionconstraint::BilateralInteractionConstraint ;
using bilateralinteractionconstraint::BilateralInteractionConstraintSpecialization ;

} // namespace constraintset

} // namespace component

} // namespace sofa

#endif // SOFA_COMPONENT_CONSTRAINTSET_BILATERALINTERACTIONCONSTRAINT_H
