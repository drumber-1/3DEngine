cmake_minimum_required(VERSION 2.6)

project(3DEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Move resources if needed
if (NOT 3DEngine_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    file(GLOB_RECURSE RES ${3DEngine_SOURCE_DIR}/res/*)
    foreach(ITEM IN LISTS RES)
        string(REPLACE ${3DEngine_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} NEW_ITEM ${ITEM})
        message(STATUS ${NEW_ITEM})
        configure_file(${ITEM} ${NEW_ITEM} COPYONLY)
    endforeach()
endif()


file(GLOB_RECURSE HDRS ${3DEngine_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SRCS ${3DEngine_SOURCE_DIR}/src/*.cpp)
add_executable(3DEngine ${HDRS} ${SRCS})

SET(3DEngine_CMAKE_DIR "${3DEngine_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include(${3DEngine_CMAKE_DIR}/FindASSIMP.cmake)

include_directories(
	${3DEngine_SOURCE_DIR}/headers
	${3DEngine_SOURCE_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2IMAGE_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
)

link_directories(
	${OpenGL_LIBRARY_DIRS}
	${GLEW_LIBRARY_DIRS}

)

add_definitions(
    ${OpenGL_DEFINITIONS}
    ${GLEW_DEFINITIONS}
)

target_link_libraries( 3DEngine
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2IMAGE_LIBRARIES}
	${ASSIMP_LIBRARIES}
)