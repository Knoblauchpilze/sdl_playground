cmake_minimum_required (VERSION 3.7)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

add_compile_options (-Wall -Wextra -Werror -pedantic)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

project (sdl_playground)

add_executable (sdl_playground)

find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)

target_sources (sdl_playground PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)

target_include_directories (sdl_playground PRIVATE
	)

target_link_libraries(sdl_playground
	core_utils
	sdl_engine
	sdl_core
	sdl_graphic
	sdl_app_core
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	)
