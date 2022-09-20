# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set CMake project name
project(OSMESA)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-O3 O3_COMPILER_FLAG)

find_package(Threads REQUIRED)
if (CMAKE_USE_PTHREADS_INIT)
  add_definitions(-DPTHREADS)
endif (CMAKE_USE_PTHREADS_INIT)

include(CheckLibraryExists)
check_library_exists(m cos "" HAVE_M_LIBRARY)
if (HAVE_M_LIBRARY)
  set(M_LIBRARY m)
endif (HAVE_M_LIBRARY)

# The point is to be separate from system OpenGL,
# so define the mangling headers to produce mgl_
# prefixing
add_definitions(-DUSE_MGL_NAMESPACE)


add_subdirectory(src)


set(EX_OPT_DEFAULT ON)
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)
  set(EX_OPT_DEFAULT OFF)
endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)

option(OSMESA_BUILD_EXAMPLES "Build example programs" ${EX_OPT_DEFAULT})

if (OSMESA_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif (OSMESA_BUILD_EXAMPLES)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
