cmake_minimum_required(VERSION 3.12)
project(twilight)

set(CMAKE_CXX_STANDARD 14)

# Where the 'app' and 'blend2d' are.
set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}"
        CACHE PATH "Application directory")

set(BLEND2D_DIR "${APP_DIR}/../blend2d"
        CACHE PATH "Location of 'blend2d'")

# Enable Blend2D static build.
set(BLEND2D_STATIC TRUE)
include("${BLEND2D_DIR}/CMakeLists.txt")

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# GL
find_library(GL REQUIRED)

# DL
find_library(dl REQUIRED)
#include_directories(${LIBDL_INCLUDE_DIRS})

# RtMidi
#find_package(RtMidi REQUIRED)
find_library (RTMIDI rtmidi)

# Your application target.
add_executable(twilight main.cc beams/beam.cc beams/beam.h beams/tunnel.cc beams/tunnel.h graphics/sdl_application.cc graphics/sdl_application.h beams/fps.cc beams/fps.h observer/dispatch.cc observer/dispatch.h midi/midi_device.cc midi/midi_device.h midi/midi_apc_40.cc midi/midi_apc_40.h midi/midi_manager.cc midi/midi_manager.h observer/observer.cc observer/observer.h observer/subject.cc observer/subject.h twilight.h beams/color.cc beams/color.h gui/gui.cc gui/gui.h ../imgui/examples/imgui_impl_sdl.cpp ../imgui/examples/imgui_impl_opengl3.cpp ../imgui/imgui.cpp ../imgui/imgui_demo.cpp ../imgui/imgui_draw.cpp ../imgui/imgui_widgets.cpp ../imgui/examples/libs/gl3w/GL/gl3w.c clock/clock.cc clock/clock.h clock/clock_manager.cc clock/clock_manager.h)
include_directories(. ../imgui/ ../imgui/examples/ ../imgui/examples/libs/gl3w/ ../imgui/examples/example_sdl_opengl3)

# Add Blend2D dependency to your application. The dependency
# should provide everything needed - include paths, libraries,
# compiler flags, and compiler definitions.
target_link_libraries(twilight Blend2D::Blend2D)
target_link_libraries(twilight ${SDL2_LIBRARIES})
target_link_libraries(twilight ${RTMIDI})
target_link_libraries(twilight dl)
target_link_libraries(twilight GL)
