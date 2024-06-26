cmake_minimum_required(VERSION 3.1)
project(SofaGeneralEngine)

################################ COMPONENTS HERE ARE THE NG-SET ####################################
set(HEADER_FILES
    config.h
    initGeneralEngine.h
)

set(SOURCE_FILES
    initGeneralEngine.cpp
)

############################## COMPONENTS HERE ARE THE LIGHT-SET ###################################
if(SOFA_BUILD_COMPONENTSET_LIGHT)
    list(APPEND HEADER_FILES

        )
    list(APPEND SOURCE_FILES

        )
endif()

############################## COMPONENTS HERE ARE THE STANDARD-SET ################################
if(SOFA_BUILD_COMPONENTSET_STANDARD)
    list(APPEND HEADER_FILES AverageCoord.h
                             AverageCoord.inl
                             ClusteringEngine.h
                             ClusteringEngine.inl
                             ComplementaryROI.h
                             ComplementaryROI.inl
                             ComplementaryROI.h
                             ComplementaryROI.inl
                             DilateEngine.h
                             DilateEngine.inl
                             DifferenceEngine.h
                             DifferenceEngine.inl
                             ExtrudeEdgesAndGenerateQuads.h
                             ExtrudeEdgesAndGenerateQuads.inl
                             ExtrudeQuadsAndGenerateHexas.h
                             ExtrudeQuadsAndGenerateHexas.inl
                             ExtrudeSurface.h
                             ExtrudeSurface.inl
                             GenerateCylinder.h
                             GenerateCylinder.inl
                             GenerateGrid.h
                             GenerateGrid.inl
                             GenerateRigidMass.h
                             GenerateRigidMass.inl
                             GenerateSphere.h
                             GenerateSphere.inl
                             GroupFilterYoungModulus.h
                             GroupFilterYoungModulus.inl
                             HausdorffDistance.h
                             HausdorffDistance.inl
                             IndexValueMapper.h
                             IndexValueMapper.inl
                             Indices2ValuesMapper.h
                             Indices2ValuesMapper.inl
                             IndicesFromValues.h
                             IndicesFromValues.inl
                             JoinPoints.h
                             JoinPoints.inl
                             MapIndices.h
                             MapIndices.inl
                             MathOp.h
                             MathOp.inl
                             MergeMeshes.h
                             MergeMeshes.inl
                             MergePoints.h
                             MergePoints.inl
                             MergeROIs.h
                             MergeSets.h
                             MergeSets.inl
                             MergeVectors.h
                             MergeVectors.inl
                             MeshBarycentricMapperEngine.h
                             MeshBarycentricMapperEngine.inl
                             MeshClosingEngine.h
                             MeshClosingEngine.inl
                             MeshBoundaryROI.h
                             MeshROI.h
                             MeshROI.inl
                             MeshSampler.h
                             MeshSampler.inl
                             MeshSplittingEngine.h
                             MeshSplittingEngine.inl
                             MeshSubsetEngine.h
                             MeshSubsetEngine.inl
                             NormEngine.h
                             NormEngine.inl
                             NormalsFromPoints.h
                             NormalsFromPoints.inl
                             PairBoxRoi.h
                             PairBoxRoi.inl
                             PlaneROI.h
                             PlaneROI.inl
                             PointsFromIndices.h
                             PointsFromIndices.inl
                             ProximityROI.h
                             ProximityROI.inl
                             QuatToRigidEngine.h
                             QuatToRigidEngine.inl
                             ROIValueMapper.h
                             RandomPointDistributionInSurface.h
                             RandomPointDistributionInSurface.inl
                             RigidToQuatEngine.h
                             RigidToQuatEngine.inl
                             SelectLabelROI.h
                             SelectConnectedLabelsROI.cpp
                             ShapeMatching.h
                             ShapeMatching.inl
                             SmoothMeshEngine.h
                             SmoothMeshEngine.inl
                             SphereROI.h
                             SphereROI.inl
                             Spiral.h
                             Spiral.inl
                             SubsetTopology.h
                             SubsetTopology.inl
                             SumEngine.h
                             SumEngine.inl
                             TextureInterpolation.h
                             TextureInterpolation.inl
                             TransformEngine.h
                             TransformEngine.inl
                             TransformMatrixEngine.h
                             TransformPosition.h
                             TransformPosition.inl
                             ValuesFromIndices.h
                             ValuesFromIndices.inl
                             ValuesFromPositions.h
                             ValuesFromPositions.inl
                             Vertex2Frame.h
                             Vertex2Frame.inl
                             )
    list(APPEND SOURCE_FILES AverageCoord.cpp
                             ClusteringEngine.cpp
                             ComplementaryROI.cpp
                             ComplementaryROI.cpp
                             DilateEngine.cpp
                             DifferenceEngine.cpp
                             ExtrudeEdgesAndGenerateQuads.cpp
                             ExtrudeQuadsAndGenerateHexas.cpp
                             ExtrudeSurface.cpp
                             GenerateCylinder.cpp
                             GenerateGrid.cpp
                             GenerateRigidMass.cpp
                             GenerateSphere.cpp
                             GroupFilterYoungModulus.cpp
                             HausdorffDistance.cpp
                             IndexValueMapper.cpp
                             Indices2ValuesMapper.cpp
                             IndicesFromValues.cpp
                             JoinPoints.cpp
                             MapIndices.cpp
                             MathOp.cpp
                             MergeMeshes.cpp
                             MergePoints.cpp
                             MergeROIs.cpp
                             MergeSets.cpp
                             MergeVectors.cpp
                             MeshBarycentricMapperEngine.cpp
                             MeshClosingEngine.cpp
                             MeshBoundaryROI.cpp
                             MeshROI.cpp
                             MeshSampler.cpp
                             MeshSplittingEngine.cpp
                             MeshSubsetEngine.cpp
                             NormEngine.cpp
                             NormalsFromPoints.cpp
                             PairBoxRoi.cpp
                             PlaneROI.cpp
                             PointsFromIndices.cpp
                             ProximityROI.cpp
                             QuatToRigidEngine.cpp
                             ROIValueMapper.cpp
                             RandomPointDistributionInSurface.cpp
                             RigidToQuatEngine.cpp
                             SelectLabelROI.cpp
                             SelectConnectedLabelsROI.cpp
                             ShapeMatching.cpp
                             SmoothMeshEngine.cpp
                             SphereROI.cpp
                             Spiral.cpp
                             SubsetTopology.cpp
                             SumEngine.cpp
                             TextureInterpolation.cpp
                             TransformEngine.cpp
                             TransformMatrixEngine.cpp
                             TransformPosition.cpp
                             ValuesFromIndices.cpp
                             ValuesFromPositions.cpp
                             Vertex2Frame.cpp
                             )
endif()

############################### COMPONENTS HERE ARE DEPRECATED ####################################
if(SOFA_BUILD_COMPONENTSET_FULL)
    #list(APPEND HEADER_FILES MeshG.h)
    #list(APPEND SOURCE_FILES MeshGenerationFromImage.cpp)
endif()

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaMeshCollision SofaGeneralMeshCollision)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_GENERAL_ENGINE")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

sofa_install_targets(SofaGeneral ${PROJECT_NAME} ${PROJECT_NAME})
