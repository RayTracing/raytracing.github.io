cmake_minimum_required ( VERSION 3.1.0 )

project ( RAYTRACING_GITHUB_IO
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )

# Source
set ( IN_ONE_WEEKEND_SOURCE
  src/common/constants.h
  src/common/vec3.h
  src/InOneWeekend/camera.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/material.h
  src/InOneWeekend/random.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/main.cc
)

set ( THE_NEXT_WEEK_SOURCE
  src/common/constants.h
  src/common/stb_image.h
  src/common/vec3.h
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
  src/TheNextWeek/random.h
  src/TheNextWeek/ray.h
  src/TheNextWeek/sphere.h
  src/TheNextWeek/surface_texture.h
  src/TheNextWeek/texture.h
  src/TheNextWeek/main.cc
)

set ( THE_REST_OF_YOUR_LIFE_SOURCE
  src/common/constants.h
  src/common/stb_image.h
  src/common/vec3.h
  src/TheRestOfYourLife/aabb.h
  src/TheRestOfYourLife/aarect.h
  src/TheRestOfYourLife/box.h
  src/TheRestOfYourLife/bucamera.h
  src/TheRestOfYourLife/bvh.h
  src/TheRestOfYourLife/camera.h
  src/TheRestOfYourLife/constant_medium.h
  src/TheRestOfYourLife/foomaterial.h
  src/TheRestOfYourLife/hittable.h
  src/TheRestOfYourLife/hittable_list.h
  src/TheRestOfYourLife/material.h
  src/TheRestOfYourLife/moving_sphere.h
  src/TheRestOfYourLife/onb.h
  src/TheRestOfYourLife/pdf.h
  src/TheRestOfYourLife/perlin.h
  src/TheRestOfYourLife/random.h
  src/TheRestOfYourLife/ray.h
  src/TheRestOfYourLife/sphere.h
  src/TheRestOfYourLife/surface_texture.h
  src/TheRestOfYourLife/texture.h
  src/TheRestOfYourLife/main.cc
)

set ( COMMON_DIR src )

add_executable(inOneWeekend      ${IN_ONE_WEEKEND_SOURCE})
add_executable(theNextWeek       ${THE_NEXT_WEEK_SOURCE})
add_executable(theRestOfYourLife ${THE_REST_OF_YOUR_LIFE_SOURCE})

target_include_directories(inOneWeekend      PRIVATE ${COMMON_DIR})
target_include_directories(theNextWeek       PRIVATE ${COMMON_DIR})
target_include_directories(theRestOfYourLife PRIVATE ${COMMON_DIR})
