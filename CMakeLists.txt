cmake_minimum_required(VERSION 3.22.1)

project(geugenm.8bitTanks VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${INCLUDE}/)

# Define paths
set(LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/libraries)
set(EASYLOGGINGPP_INCLUDE_DIR ${LIBRARIES}/easyloggingpp)
set(EASYLOGGINGPP_SOURCES ${LIBRARIES}/easyloggingpp/easylogging++.cc)

# Find SFML library
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add easyloggingpp library
add_library(lib.easyloggingpp STATIC ${EASYLOGGINGPP_SOURCES})
target_include_directories(lib.easyloggingpp PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})


# Add executable and link with SFML and easyloggingpp libraries
add_executable(${PROJECT_NAME} sources/Main.cpp include/entity/Projectile.h include/entity/Turret.h include/MovementVectors.h include/Config.h include/entity/Hull.h include/Cursor.h include/MainWindow.h)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} lib.easyloggingpp)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

