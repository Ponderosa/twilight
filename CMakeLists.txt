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

# RtMidi
#find_package(RtMidi REQUIRED)
find_library (RTMIDI rtmidi)

# Your application target.
add_executable(twilight main.cc beams/beam.cc beams/beam.h beams/tunnel.cc beams/tunnel.h graphics/sdl_application.cc graphics/sdl_application.h beams/fps.cc beams/fps.h observer/dispatch.cc observer/dispatch.h midi/midi_device.cc midi/midi_device.h midi/midi_apc_40.cc midi/midi_apc_40.h midi/midi_manager.cc midi/midi_manager.h observer/observer.cc observer/observer.h observer/subject.cc observer/subject.h twilight.h beams/color.cc beams/color.h observer/parameter.cc observer/parameter.h observer/animator.cc observer/animator.h)
include_directories(.)

# Add Blend2D dependency to your application. The dependency
# should provide everything needed - include paths, libraries,
# compiler flags, and compiler definitions.
target_link_libraries(twilight Blend2D::Blend2D)
target_link_libraries(twilight ${SDL2_LIBRARIES})
target_link_libraries(twilight ${RTMIDI})
