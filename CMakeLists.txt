#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project ( RTWeekend LANGUAGES CXX )

# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Source

set ( EXTERNAL
  src/external/stb_image.h
)

set ( SOURCE_ONE_WEEKEND
  src/InOneWeekend/main.cc
  src/InOneWeekend/camera.h
  src/InOneWeekend/color.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/interval.h
  src/InOneWeekend/material.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/rtweekend.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/vec3.h
)

set ( SOURCE_NEXT_WEEK
  src/TheNextWeek/main.cc
  src/TheNextWeek/aabb.h
  src/TheNextWeek/bvh.h
  src/TheNextWeek/camera.h
  src/TheNextWeek/color.h
  src/TheNextWeek/constant_medium.h
  src/TheNextWeek/hittable.h
  src/TheNextWeek/hittable_list.h
  src/TheNextWeek/interval.h
  src/TheNextWeek/material.h
  src/TheNextWeek/perlin.h
  src/TheNextWeek/quad.h
  src/TheNextWeek/ray.h
  src/TheNextWeek/rtw_stb_image.h
  src/TheNextWeek/rtweekend.h
  src/TheNextWeek/sphere.h
  src/TheNextWeek/texture.h
  src/TheNextWeek/vec3.h
)

set ( SOURCE_REST_OF_YOUR_LIFE
  src/TheRestOfYourLife/main.cc
  src/TheRestOfYourLife/aabb.h
  src/TheRestOfYourLife/camera.h
  src/TheRestOfYourLife/color.h
  src/TheRestOfYourLife/constant_medium.h
  src/TheRestOfYourLife/hittable.h
  src/TheRestOfYourLife/hittable_list.h
  src/TheRestOfYourLife/interval.h
  src/TheRestOfYourLife/material.h
  src/TheRestOfYourLife/onb.h
  src/TheRestOfYourLife/pdf.h
  src/TheRestOfYourLife/perlin.h
  src/TheRestOfYourLife/quad.h
  src/TheRestOfYourLife/ray.h
  src/TheRestOfYourLife/rtw_stb_image.h
  src/TheRestOfYourLife/rtweekend.h
  src/TheRestOfYourLife/sphere.h
  src/TheRestOfYourLife/texture.h
  src/TheRestOfYourLife/vec3.h
)

include_directories(src)

# Specific compiler flags below. We're not going to add options for all possible compilers, but if
# you're new to CMake (like we are), the following may be a helpful example if you're using a
# different compiler or want to set different compiler options.

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # /wd #### - Disable warning
    # /we #### - treat warning as error
    add_compile_options("/W4")      # Enable level-4 warnings
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
    add_compile_options("/wd 4100") # unreferenced formal parameter
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()

# Executables
add_executable(inOneWeekend      ${EXTERNAL} ${SOURCE_ONE_WEEKEND})
add_executable(theNextWeek       ${EXTERNAL} ${SOURCE_NEXT_WEEK})
add_executable(theRestOfYourLife ${EXTERNAL} ${SOURCE_REST_OF_YOUR_LIFE})
add_executable(cos_cubed         src/TheRestOfYourLife/cos_cubed.cc         )
add_executable(cos_density       src/TheRestOfYourLife/cos_density.cc       )
add_executable(integrate_x_sq    src/TheRestOfYourLife/integrate_x_sq.cc    )
add_executable(pi                src/TheRestOfYourLife/pi.cc                )
add_executable(estimate_halfway  src/TheRestOfYourLife/estimate_halfway.cc  )
add_executable(sphere_importance src/TheRestOfYourLife/sphere_importance.cc )
add_executable(sphere_plot       src/TheRestOfYourLife/sphere_plot.cc       )
