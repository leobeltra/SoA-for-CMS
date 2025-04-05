cmake_minimum_required(VERSION 3.18)
project(SoA_CMS)

set(CMAKE_CXX_STANDARD 20)

# Find Boost
find_package(Boost REQUIRED)

# If Alpaka is installed under /usr/local, you could manually specify the path:
# find_package(Alpaka REQUIRED)

# Add Alpaka directory
# add_subdirectory(alpaka)
add_subdirectory(/opt/alpaka alpaka-build)

add_subdirectory(/opt/Catch2 Catch2-build)
# Include directories
include_directories(include)

# Source files
file(GLOB TEST_SOURCES "tests/*.cc")

# Executable
# add_executable(soa ${SOURCES})

# target_include_directories(soa PRIVATE /opt/Catch2/single_include/catch2)

# Link libraries
# target_link_libraries(soa PRIVATE Boost::boost alpaka::alpaka Catch2::Catch2)

# Create separate executables for each test file
foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})

    # Include Catch2 for each test target
    target_include_directories(${test_name} PRIVATE /opt/Catch2/single_include/catch2)

    # Link libraries to each test executable
    target_link_libraries(${test_name} PRIVATE Boost::boost alpaka::alpaka Catch2::Catch2)
endforeach()
