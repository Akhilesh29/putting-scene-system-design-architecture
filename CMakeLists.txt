cmake_minimum_required(VERSION 3.15)
project(PuttingScene VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Redis++ REQUIRED)
find_package(libpqxx REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Threads REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${REDIS++_INCLUDE_DIRS}
    ${LIBPQXX_INCLUDE_DIRS}
    ${NLOHMANN_JSON_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/services/EventServiceImpl.cpp
    # Add other source files here
)

# Create the library
add_library(putting_scene STATIC ${SOURCES})

# Link libraries
target_link_libraries(putting_scene
    PRIVATE
    ${REDIS++_LIBRARIES}
    ${LIBPQXX_LIBRARIES}
    ${NLOHMANN_JSON_LIBRARIES}
    Threads::Threads
)

# Create the executable
add_executable(putting_scene_app src/main.cpp)
target_link_libraries(putting_scene_app PRIVATE putting_scene)

# Installation
install(TARGETS putting_scene putting_scene_app
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Testing
enable_testing()
add_subdirectory(tests) 