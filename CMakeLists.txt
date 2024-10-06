# # https://cmake.org/examples/

# # CMakeLists files in this project can
# # refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# # to the root binary directory of the project as ${HELLO_BINARY_DIR}.

# # Minimum CMake version required
# cmake_minimum_required(VERSION 3.24)

# # environment variable set for visual studio generator 
# set(CMAKE_GENERATOR_PLATFORM x64)

# # Project name and the programming language used
# project(opengl_renderer_test VERSION 1.0 LANGUAGES CXX)

# # Set the C++ standard to C++14
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# #
# message(FATAL_ERROR "return 0")

# # cmake_current_source_dir  : where CMakeLists.txt lives
# # project_name              : refers to project name defined on project()
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
#             PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# # Include directories (your header files location)
# include_directories(headers)
# include_directories(headers/abstract)
# include_directories(headers/core)
# include_directories(headers/events)
# include_directories(headers/maps)
# include_directories(headers/templates)
# include_directories(headers/test)
# include_directories(headers/utils)





