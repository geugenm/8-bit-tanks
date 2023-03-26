cmake_minimum_required(VERSION 3.22.1)

project(game VERSION 1.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

# Set include directories
set(INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${INCLUDE}/)

# Define library paths
set(LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/libraries)
set(EASYLOGGINGPP_INCLUDE_DIR ${LIBRARIES}/easyloggingpp)
set(EASYLOGGINGPP_SOURCES ${LIBRARIES}/easyloggingpp/easylogging++.cc)

# Find required libraries
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add easyloggingpp library
add_library(lib.easyloggingpp STATIC ${EASYLOGGINGPP_SOURCES})
target_include_directories(lib.easyloggingpp PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})

# Get a list of all .cpp files in the sources directory
file(GLOB_RECURSE SOURCES "sources/*.cpp")
file(GLOB_RECURSE SOURCES_ENTITY "sources/entity/*.cpp")

# Add executable and link with SFML and easyloggingpp libraries
add_executable(${PROJECT_NAME} ${SOURCES} ${SOURCES_ENTITY})

target_link_libraries(${PROJECT_NAME}
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        lib.easyloggingpp
        )

# Copy resources to the output directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
        )
