cmake_minimum_required(VERSION 3.1)
project(SofaGuiQt)

set(MOC_HEADER_FILES
    AddObject.h
    DataFilenameWidget.h
    DataWidget.h
    DisplayFlagsDataWidget.h
    GenGraphForm.h
    LinkWidget.h
    MaterialDataWidget.h
    RGBAColorDataWidget.h
    ModifyObject.h
    QDataDescriptionWidget.h
    QDisplayDataWidget.h
    QDisplayLinkWidget.h
    QDisplayPropertyWidget.h
    QRGBAColorPicker.h
    QModelViewTableUpdater.h
    QMouseOperations.h
    QSofaListView.h
    QSofaRecorder.h
    QSofaStatWidget.h
    QTabulationModifyObject.h
    QTransformationWidget.h
    RealGUI.h
    SimpleDataWidget.h
    SofaMouseManager.h
    SofaPluginManager.h
    SofaVideoRecorderManager.h
    WDoubleLineEdit.h
)

# these header files do not need MOCcing
set(HEADER_FILES
    FileManagement.h
    GraphListenerQListView.h
    PickHandlerCallBacks.h
    QMenuFilesRecentlyOpened.h
    QModelViewTableDataContainer.h
    SofaGUIQt.h
    StructDataWidget.h
    TableDataWidget.h
    viewer/SofaViewer.h
    viewer/VisualModelPolicy.h
)

set(SOURCE_FILES
    AddObject.cpp
    DataFilenameWidget.cpp
    DataWidget.cpp
    DisplayFlagsDataWidget.cpp
    FileManagement.cpp
    GenGraphForm.cpp
    GraphListenerQListView.cpp
    LinkWidget.cpp
    MaterialDataWidget.cpp
    RGBAColorDataWidget.cpp
    ModifyObject.cpp
    PickHandlerCallBacks.cpp
    QDataDescriptionWidget.cpp
    QDisplayDataWidget.cpp
    QDisplayLinkWidget.cpp
    QDisplayPropertyWidget.cpp
    QRGBAColorPicker.cpp
    QMenuFilesRecentlyOpened.cpp
    QModelViewTableUpdater.cpp
    QMouseOperations.cpp
    QSofaListView.cpp
    QSofaRecorder.cpp
    QSofaStatWidget.cpp
    QTabulationModifyObject.cpp
    QTransformationWidget.cpp
    RealGUI.cpp
    SimpleDataWidget.cpp
    SofaMouseManager.cpp
    SofaPluginManager.cpp
    SofaVideoRecorderManager.cpp
    StructDataWidget.cpp
    TableDataWidget.cpp
    WDoubleLineEdit.cpp
    viewer/SofaViewer.cpp
)

set(UI_FILES
    BaseGenGraphForm.ui
    DialogAddObject.ui
    GUI.ui
    MouseManager.ui
    PluginManager.ui
    VideoRecorderManager.ui
)

if(SOFA_DUMP_VISITOR_INFO)
    list(APPEND MOC_HEADER_FILES

         WindowVisitor.h
         QVisitorControlPanel.h
         PieWidget.h)

    list(APPEND HEADER_FILES

         GraphVisitor.h)

    list(APPEND SOURCE_FILES

         GraphVisitor.cpp
         WindowVisitor.cpp
         QVisitorControlPanel.cpp
         PieWidget.cpp)

    list(APPEND UI_FILES VisitorGUI.ui)
endif()


if(SOFAGUI_ENABLE_QWT)

    list(APPEND MOC_HEADER_FILES
         GraphDataWidget.h
         QGraphStatWidget.h
         QEnergyStatWidget.h
         QMomentumStatWidget.h)

    list(APPEND SOURCE_FILES
         GraphDataWidget.cpp
         QGraphStatWidget.cpp
         QEnergyStatWidget.cpp
         QMomentumStatWidget.cpp
         )
endif()

# QtViewer
if(SOFAGUI_QTVIEWER)
    list(APPEND MOC_HEADER_FILES viewer/qt/QtViewer.h)
    list(APPEND SOURCE_FILES viewer/qt/QtViewer.cpp)
endif()

# QGLViewer
if(SOFAGUI_QGLVIEWER)
    find_package(QGLViewer)

    list(APPEND MOC_HEADER_FILES viewer/qgl/QtGLViewer.h)
    list(APPEND SOURCE_FILES viewer/qgl/QtGLViewer.cpp)
endif()

if(SOFA_DUMP_VISITOR_INFO)
endif()

set(QT_USE_IMPORTED_TARGETS 1)

find_package(Qt5 COMPONENTS Core QUIET)

if(Qt5Core_FOUND)
    message("SofaGUIQt: Using Qt5")
    set(QT5_NO_LINK_QTMAIN 1)

    find_package(Qt5 COMPONENTS Gui OpenGL REQUIRED)

    set(EXT_QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})
    # target_include_directories(${EXT_QT_INCLUDES})

    set(EXT_QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})

    qt5_wrap_cpp(MOC_FILES ${MOC_HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")
    qt5_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")


else()
    message("SofaGUIQt: Using Qt4")

    set(QT4_NO_LINK_QTMAIN 1)
    find_package(Qt4 QUIET COMPONENTS qtcore qtgui qtopengl qtxml REQUIRED)

    qt4_wrap_cpp(MOC_FILES ${MOC_HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")
    qt4_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")

    set(EXT_QT_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${QT_QTXML_LIBRARY})

endif()

add_library(${PROJECT_NAME} SHARED ${MOC_HEADER_FILES} ${HEADER_FILES} ${MOC_FILES} ${FORM_FILES} ${SOURCE_FILES})
# For files generated by the moc
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<INSTALL_INTERFACE:include>")
target_link_libraries(${PROJECT_NAME} PUBLIC SofaGuiCommon SofaBaseVisual SofaExporter SofaLoader SofaOpenglVisual SofaMiscForceField)
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXT_QT_LIBRARIES})
if(SOFAGUI_ENABLE_QWT)
    target_link_libraries(${PROJECT_NAME} PUBLIC qwt)
endif()
if(SOFAGUI_QGLVIEWER)
    target_link_libraries(${PROJECT_NAME} PUBLIC QGLViewer)
endif()

# target_compile_definitions(${PROJECT_NAME} PUBLIC "SOFA_QT4")
# target_compile_definitions(${PROJECT_NAME} PUBLIC "QT3_SUPPORT")

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_SOFAGUIQT")
if(SOFA_ENABLE_QWT)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_SOFAGUIQT")
endif()


sofa_install_targets(SofaGui SofaGuiQt "")

install(FILES ${HEADER_FILES} DESTINATION "include/sofa/gui/qt")
install(FILES ${MOC_HEADER_FILES} DESTINATION "include/sofa/gui/qt")
