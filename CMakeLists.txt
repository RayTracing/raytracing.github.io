#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekend
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )

# Source
set ( SOURCE_ONE_WEEKEND
  src/common/rtweekend.h
  src/common/vec3.h
  src/InOneWeekend/camera.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/material.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/main.cc
)

set ( SOURCE_NEXT_WEEK
  src/common/rtweekend.h
  src/common/rtw_stb_image.h
  src/common/vec3.h
  src/common/external/stb_image.h
  src/TheNextWeek/aabb.h
  src/TheNextWeek/aarect.h
  src/TheNextWeek/box.h
  src/TheNextWeek/bvh.h
  src/TheNextWeek/camera.h
  src/TheNextWeek/constant_medium.h
  src/TheNextWeek/hittable.h
  src/TheNextWeek/hittable_list.h
  src/TheNextWeek/material.h
  src/TheNextWeek/moving_sphere.h
  src/TheNextWeek/perlin.h
  src/TheNextWeek/ray.h
  src/TheNextWeek/sphere.h
  src/TheNextWeek/surface_texture.h
  src/TheNextWeek/texture.h
  src/TheNextWeek/main.cc
)

set ( SOURCE_REST_OF_YOUR_LIFE
  src/common/rtweekend.h
  src/common/rtw_stb_image.h
  src/common/vec3.h
  src/common/external/stb_image.h
  src/TheRestOfYourLife/aabb.h
  src/TheRestOfYourLife/aarect.h
  src/TheRestOfYourLife/box.h
  src/TheRestOfYourLife/bvh.h
  src/TheRestOfYourLife/camera.h
  src/TheRestOfYourLife/constant_medium.h
  src/TheRestOfYourLife/hittable.h
  src/TheRestOfYourLife/hittable_list.h
  src/TheRestOfYourLife/material.h
  src/TheRestOfYourLife/moving_sphere.h
  src/TheRestOfYourLife/onb.h
  src/TheRestOfYourLife/pdf.h
  src/TheRestOfYourLife/perlin.h
  src/TheRestOfYourLife/ray.h
  src/TheRestOfYourLife/sphere.h
  src/TheRestOfYourLife/surface_texture.h
  src/TheRestOfYourLife/texture.h
  src/TheRestOfYourLife/main.cc
)

set ( COMMON_DIR src )

add_executable(inOneWeekend      ${SOURCE_ONE_WEEKEND})
add_executable(theNextWeek       ${SOURCE_NEXT_WEEK})
add_executable(theRestOfYourLife ${SOURCE_REST_OF_YOUR_LIFE})

target_include_directories(inOneWeekend      PRIVATE ${COMMON_DIR})
target_include_directories(theNextWeek       PRIVATE ${COMMON_DIR})
target_include_directories(theRestOfYourLife PRIVATE ${COMMON_DIR})
