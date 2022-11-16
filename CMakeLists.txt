# ---------------------------------------------------------------------------- #

cmake_minimum_required(VERSION 3.11)
include(FetchContent)

project(profiler VERSION 1.0.0 DESCRIPTION "profiler: ...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Setup the options that CMake can take in
option(PROFILER_INSTALL "Install profiler's header and library" ON)
option(PROFILER_BUILD_TESTS "Build profiler's unit tests" ON)

# Setup the basic C++ Compiler flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Wl,--no-as-needed -ldl")

# Test whether -Wthread-safety is available. See
# https://clang.llvm.org/docs/ThreadSafetyAnalysis.html
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Wthread-safety HAVE_CLANG_THREAD_SAFETY)

# ---------------------------------------------------------------------------- #
# profiler

add_library(profiler SHARED "")

set_target_properties(
        profiler
        PROPERTIES
        # CXX_VISIBILITY_PRESET hidden
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(profiler PUBLIC include)

if (HAVE_CLANG_THREAD_SAFETY)
    target_compile_options(profiler PUBLIC -Wthread-safety)
endif (HAVE_CLANG_THREAD_SAFETY)

# needed by (LevelDB's?) port_stdcxx.h
find_package(Threads REQUIRED)
target_link_libraries(profiler Threads::Threads)

target_sources(
    profiler
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/posix_passthrough.hpp
)

target_sources(
        profiler
        PRIVATE
        src/posix_file_system.cpp
        src/posix_passthrough.cpp
)


target_link_libraries(profiler)

# ---------------------------------------------------------------------------- #
# install

if (PROFILER_INSTALL)
    include(GNUInstallDirs)
    install(
            TARGETS profiler
            EXPORT profilerTargets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
    install(DIRECTORY include TYPE INCLUDE)
endif (PROFILER_INSTALL)

# ---------------------------------------------------------------------------- #
