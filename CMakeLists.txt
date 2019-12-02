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
set ( COMMON_ALL
  src/common/rtweekend.h
  src/common/vec3.h
)

set ( SOURCE_ONE_WEEKEND
  ${COMMON_ALL}
  src/InOneWeekend/camera.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/material.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/main.cc
)

set ( SOURCE_NEXT_WEEK
  ${COMMON_ALL}
  src/common/rtw_stb_image.h
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
  ${COMMON_ALL}
  src/common/rtw_stb_image.h
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

# Executables
add_executable(inOneWeekend      ${SOURCE_ONE_WEEKEND})
add_executable(theNextWeek       ${SOURCE_NEXT_WEEK})
add_executable(theRestOfYourLife ${SOURCE_REST_OF_YOUR_LIFE})
add_executable(cos_cubed         src/TheRestOfYourLife/cos_cubed.cc         ${COMMON_ALL})
add_executable(cos_density       src/TheRestOfYourLife/cos_density.cc       ${COMMON_ALL})
add_executable(integrate_x_sq    src/TheRestOfYourLife/integrate_x_sq.cc    ${COMMON_ALL})
add_executable(pi                src/TheRestOfYourLife/pi.cc                ${COMMON_ALL})
add_executable(sphere_importance src/TheRestOfYourLife/sphere_importance.cc ${COMMON_ALL})
add_executable(sphere_plot       src/TheRestOfYourLife/sphere_plot.cc       ${COMMON_ALL})

target_include_directories(inOneWeekend      PRIVATE src)
target_include_directories(theNextWeek       PRIVATE src)
target_include_directories(theRestOfYourLife PRIVATE src)
target_include_directories(cos_cubed         PRIVATE src)
target_include_directories(cos_density       PRIVATE src)
target_include_directories(integrate_x_sq    PRIVATE src)
target_include_directories(pi                PRIVATE src)
target_include_directories(sphere_importance PRIVATE src)
target_include_directories(sphere_plot       PRIVATE src)
