cmake_minimum_required(VERSION 3.5)

project(typeless VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h mainwindow.cpp
        graph.h graph.cpp
        tools.h tools.cpp
        minheap.h minheap.cpp
        typelessui.h typelessui.cpp
        keyboardwidget.h keyboardwidget.cpp
        optimizekeyboard.h optimizekeyboard.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(typeless
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(typeless SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(typeless
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(typeless PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

set_target_properties(typeless PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(typeless)
endif()

######################################################################
############### Deployment
######################################################################

if(WIN32)
    set(COMPONENT_NAME_MAIN "Typeless")
    set(COMPONENT_NAME_DEPENDENCIES "RuntimeLibs")

    include(GNUInstallDirs)
    install(TARGETS typeless DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${COMPONENT_NAME_MAIN})

    set(CMAKE_INSTALL_RUNTIME_COMPONENT ${COMPONENT_NAME_DEPENDENCIES})
    include(InstallRequiredSystemLibraries)

    set(CPACK_GENERATOR "IFW")

    set(CPACK_VERSION_MAJOR "1")
    set(CPACK_VERSION_MINOR "0")

    set(CPACK_IFW_PACKAGE_NAME "Typeless")
    set(CPACK_IFW_PACKAGE_TITLE "Typeless Installer")
    set(CPACK_IFW_PACKAGE_PUBLISHER "He-Arc - Typeless")
    set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Aero")

    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake.in" "${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake" @ONLY)

    set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake)

    include(CPack)
    include(CPackIFW)

    CPACK_ADD_COMPONENT(${COMPONENT_NAME_MAIN})

    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} ESSENTIAL FORCED_INSTALLATION)

    message("Made installer")
endif()
