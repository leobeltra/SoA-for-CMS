cmake_minimum_required(VERSION 3.18)
project(SoA_CMS)

set(CMAKE_CXX_STANDARD 20)

# Find Boost
find_package(Boost REQUIRED)

# Abilita la lingua CUDA se CUDA è installato
find_package(CUDA REQUIRED)

enable_language(CUDA)

# If Alpaka is installed under /usr/local, you could manually specify the path:
# find_package(Alpaka REQUIRED)

# Add Alpaka directory
# add_subdirectory(alpaka)
add_subdirectory(/opt/alpaka alpaka-build)

add_subdirectory(/opt/Catch2 Catch2-build)

add_subdirectory(/opt/eigen eigen-build)
# Include directories
include_directories(include)

# Source files
file(GLOB TEST_SOURCES "tests/*.cc")

file (GLOB TEST_CUDA "tests/*.cu")

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
    target_include_directories(${test_name} PRIVATE /opt/Catch2/single_include/catch2 /opt/eigen)

    # Link libraries to each test executable
    target_link_libraries(${test_name} PRIVATE Boost::boost alpaka::alpaka Catch2::Catch2)
endforeach()

add_executable(CudaSoA ${TEST_CUDA})

set_target_properties(CudaSoA PROPERTIES LINKER_LANGUAGE CUDA)

target_include_directories(CudaSoA PRIVATE /opt/Catch2/single_include/catch2 /opt/eigen)

target_link_libraries(CudaSoA PRIVATE Boost::boost alpaka::alpaka /opt/eigen)
	



