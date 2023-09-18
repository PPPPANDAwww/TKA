cmake_minimum_required(VERSION 3.27)

project(TKA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /opt/homebrew/bin/cmake)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_INCLUDE_PATH /opt/homebrew/Cellar/qt/6.5.1_3/include)

#include_directories(/opt/homebrew/Cellar/vtk/9.2.6_4/include /opt/homebrew/Cellar/qt/6.5.1_3/include)

find_package(VTK 9.2 REQUIRED COMPONENTS CommonCore FiltersCore IOImage CommonComputationalGeometry)
find_package(Qt6 COMPONENTS Core Gui OpenGL Multimedia MultimediaWidgets OpenGLWidgets Widgets)


add_executable(TKA main.cpp mainwindow.cpp 
            playcontroler.cpp player.cpp 
            threedimage.cpp videodlg.cpp
            src.qrc
)

target_compile_options(TKA PRIVATE -arch arm64)

target_link_libraries(TKA Qt6::Core Qt6::Gui Qt6::OpenGL 
                Qt6::Multimedia Qt6::MultimediaWidgets 
                Qt6::OpenGLWidgets Qt6::Widgets 
    ${VTK_LIBRARIES}
)