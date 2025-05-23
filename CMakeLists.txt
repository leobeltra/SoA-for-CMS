cmake_minimum_required(VERSION 3.18)
project(SoA_CMS)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

find_package(CUDA REQUIRED)

enable_language(CUDA)

add_subdirectory(/opt/alpaka alpaka-build)

add_subdirectory(/opt/Catch2 Catch2-build)

add_subdirectory(/opt/eigen eigen-build)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(/opt/benchmark benchmark-build)

include_directories(include)

file(GLOB TEST_SOURCES "tests/*.cc")

file (GLOB TEST_CUDA "tests/*.cu")

foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})


    target_include_directories(${test_name} PRIVATE /opt/Catch2/single_include/catch2 /opt/eigen /opt/benchmark)


    target_link_libraries(${test_name} PRIVATE Boost::boost alpaka::alpaka Catch2::Catch2 benchmark::benchmark)
endforeach()

add_executable(CudaSoA ${TEST_CUDA})

set_target_properties(CudaSoA PROPERTIES LINKER_LANGUAGE CUDA)

target_compile_options(CudaSoA PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-relaxed-constexpr>)

target_include_directories(CudaSoA PRIVATE /opt/Catch2/single_include/catch2 /opt/eigen)

target_link_libraries(CudaSoA PRIVATE Boost::boost alpaka::alpaka /opt/eigen)
	
