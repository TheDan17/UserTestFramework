cmake_minimum_required(VERSION 3.5)

project(TestingWords VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        main/program.h main/program.cpp
        main/model.h main/model.cpp
        main/controller.h main/controller.cpp
        main/view.h main/view.cpp

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(TestingWords
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}

    test/test.h test/test.cpp
    test/testline.h test/testline.cpp
    test/testparams.h test/testparams.cpp

    test_core/testfactory.h test_core/testfactory.cpp
    test_core/testconfigs.h test_core/testconfigs.cpp
    test_core/testsession.h test_core/testsession.cpp

    test_data/testdata.h test_data/testdata.cpp
    test_data/testdataset.h test_data/testdataset.cpp
    test_data/testdatasetstore.h test_data/testdatasetstore.cpp

    ui/testlistwidget.h ui/testlistwidget.cpp
    ui/testrowwidget.h ui/testrowwidget.cpp
    ui/testsummarydialog.h ui/testsummarydialog.cpp ui/testsummarydialog.ui
)


target_link_libraries(TestingWords PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TestingWords PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TestingWords
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestingWords)
endif()
