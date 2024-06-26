cmake_minimum_required(VERSION 3.5)

project(QT_Local_shop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_Local_shop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        product.h product.cpp
        customer.h customer.cpp



        registerwindow.h registerwindow.cpp registerwindow.ui

        images.qrc
        inventorywindow.h inventorywindow.cpp inventorywindow.ui
        logwindow.h logwindow.cpp logwindow.ui
        producttablemodel.h producttablemodel.cpp
        invevntoryaddproductdialog.h invevntoryaddproductdialog.cpp invevntoryaddproductdialog.ui
        inventoryrestockdlg.h inventoryrestockdlg.cpp inventoryrestockdlg.ui
        registeradddlg.h registeradddlg.cpp registeradddlg.ui
        registerproductmodel.h registerproductmodel.cpp
        deals_aggregator.h deals_aggregator.cpp
        customertablemodel.h customertablemodel.cpp
        SalesTreeModel.h SalesTreeModel.cpp
        saleswidget.h saleswidget.cpp
        confirmorderdialog.h confirmorderdialog.cpp confirmorderdialog.ui
        datamanager.h datamanager.cpp
        financialreport.h financialreport.cpp financialreport.ui



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QT_Local_shop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT_Local_shop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT_Local_shop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT_Local_shop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QT_Local_shop)
endif()
set_target_properties(QT_Local_shop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QT_Local_shop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT_Local_shop)
endif()
