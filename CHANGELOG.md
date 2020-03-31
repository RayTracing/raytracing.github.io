Change Log -- Ray Tracing in One Weekend
====================================================================================================

----------------------------------------------------------------------------------------------------
# v3.0.1 (In Progress)

### Common
- Fix: Display rendered images as pixelated instead of smoothed (#179)
- Delete: delete old README files specific to each book (#410)

### _In One Weekend_
- Fix: Update image and size for first PPM image
- Fix: Update image and size for blue-to-white gradient image
- Fix: Update image and size for simple red sphere render
- Fix: Update image and size for sphere with normal-vector coloring
- Fix: Improve image size and aspect ratio calculation to make size changes easier
- Fix: Duplicated text on the topic of the camera up vector (#420)


----------------------------------------------------------------------------------------------------
# v3.0.0 (2020-03-23)

With the migration to a web format accomplished in v2.0.0, we immediately began work on a new major
release: v3.0.0. This release tackles the following key themes:

  - Establishing a common build system for the three projects. We chose CMake for its broad support
    for multiple platforms, as well as multiple build tools and IDEs. This change includes a
    reorganization of the project source files, and unifying a lot of code across projects.

  - A major upgrade of the project source code, addressing a number of large changes that we had
    deferred for later.

  - A number of larger changes to the book content, refining some approaches and ideas, and
    addressing some areas in the text that needed improvement.

Following this release, we expect to switch to a much more incremental approach, mostly with
patch-level (fix) changes and some minor-level (addition) changes.

### Common to All Project Source
- Change: Default floating-point type changed from `float` to `double` (#150)
- Change: Materials are now referenced with `std::shared_ptr` pointers
- Change: Complete elimination of bare pointers and `new`/`delete`
- Change: `hittable_list` uses `std::vector` plus `std::shared_ptr` pointers
- Change: Header cleanup across the source code (#218, #220)
- Change: Cleaned up standard C++ header use (#19)
- Change: Improved random number generator utilities
- Change: Replace MAXFLOAT with (portable) infinity (#195, #216)
- Change: A _lot_ of code cleanup, refactoring, renaming (#192)
- Change: Disable compile warnings for external `stb_image.h` on Windows
- Change: Replace pi with portable version (#207)
- Change: `ray_color()` function now has max depth passed in, rather than hard-coding it (#143)
- Change: Added `random_in_unit_sphere()`, `random_unit_vector()`, `random_in_hemisphere()` to
  vec3.h. Fixed places where we were using one but should have been using another. (#145)
- Change: General rework of the `vec3` header (#153, #156, #215)
- Change: Clarify sphere intersection code, plus slight perf improvement (#113)
- Change: `ray::point_at_parameter()` renamed to `ray::at()`
- Change: Moved `ffmin()`, `ffmax()` from `aabb.h` to `rtweekend.h`
- Change: Move low-level utility functions to more appropriate headers
- Change: `squared_length()` renamed to `length_squared()`
- Change: Update `sphere::hit()` function.
- Change: Refraction variables renamed to match reflection variable names
- Change: Simplify lambertian scatter direction calculation
- New: CMake configuration & build
- New: Added progress output for main programs (#139)
- New: `src/common` directory for code shared across books
- New: Common project-wide header: `src/common/rtweekend.h`
- New: File constants.h with portable math constants (#151)
- New: `vec3::write_color` - provides a robust output method for color data (#93)
- New: `degrees_to_radians()` utility function (#217)
- New: `random_int()`, `random_double()`, and `vec3::random()` utility functions
- New: Added safety value when surface texture has null data
- New: Main programs now define and handle parameterized background color
- Fix: Diffuse PDF computation uses random point _on_ sphere, rather than _inside_
- Fix: Improve color [0,1] -> [0,255] mapping

### Common to All Books
- Change: Code in source and in book reformatted to a consistent 96-column line length (#219)
- Change: Lots more highlighting of changed code in books to aid reading
- Change: Math typesetting fixes throughout the books (#13)
- Change: Books now use Markdeep's chapter indirection syntax
- Change: Updated several output images to match code updates
- Change: Books general styling improvements (#197)
- Change: Refactored acknowledgements. These are now moved to and duplicated in each book
- New: Added code listing captions, including source file name, for all books (#238)
- New: Added captions to all figures (#238)
- New: Local copy of `markdeep.min.js` for offline reading
- Fix: Fixed various minor problems in the text

### _In One Weekend_
- Change: Reworked Lambertian reflection text (#155)
- Change: Revised the figure for computing a random reflection vector (#142)
- New: Clarified text around the ideal Lambertian distribution (#155)
- New: Additional explanatory text to the dielectric chapter
- New: Image for hemispherical rendering
- New: Image for dealing with front and back faces (#326)
- Fix: Update `ray_color()` code blocks to match current source (#391)

### _The Next Week_
- Change: Added proper handling of front vs back face intersection (#270)
- New: "The Next Week" main program added swtich statement for different scenes
- New: "The Next Week" main program now defines all image/camera parameters for each scene
- Fix: Fixed bug in `noise_texture::value()` (#396)
- Fix: Correct first Perlin noise() function in "The Next Week".
- Fix: Fix OCR error in `texture::value()` function (#399)
- Fix: Remove premature declaration of `moving_sphere::bounding_box()` (#405)

### _The Rest of Your Life_
- Change: Improved naming of auxilliary programs in _The Rest of Your Life_ source
- Fix: Delete unused variable `p` in main() (#317)
- Deleted: Several unused source files from `src/TheRestOfYourLife`


----------------------------------------------------------------------------------------------------
# v2.0.0 (2019-10-07)

This major release marks an overhaul of the entire series, moving from a primarily PDF format to a
web accessible format using Markdeep (https://casual-effects.com/markdeep/). This represents a huge
overhaul to the contents, particularly around source code blocks in the text, mathematical
typesetting and source-code cleanup.

### Common
- Change: Moved existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ content to io repo
- Change: Rewrote vec3.h `cross` function for clarity
- New: General release to web
- New: Created single monolithic raytracing.github.io repo
- New: License change to CC0 in COPYING.txt
- New: CHANGELOG.md
- New: CONTRIBUTING.md
- New: COPYING.txt
- New: README.md
- New: raytracing.github.io links to all the three books
- New: CSS for all books
- New: CSS for the print variant of the books
- Fix: All instances of `hitable` have become `hittable`
- Fix: Replaced `drand48()` with portable `random_double` number generation
- Delete: Deprecated existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ repos

### _In One Weekend_
- Change: README files updated for top level, source, and books
- Change: Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 3, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 3, Consistent use of spaces in code blocks
- Change: Text, Chapter 3, Reordered `vec3` class functions to + - * /
- Change: Text, Chapter 4, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 6, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 7, Consistent use of spaces in code blocks
- Change: Text, Chapter 9, Consistent use of spaces in code blocks
- Change: Text, Chapter 9, Put function signatures and `{` on the same line
- Change: Text, Chapter 10, Consistent use of spaces in code blocks
- Change: Text, Chapter 10, Put function signatures and `{` on the same line
- Change: Text, Chapter 11, Consistent use of spaces in code blocks
- Change: Text, Chapter 13, Put function signatures and `{` on the same line
- New: Markdeep page created for entire body of text
- New: Markdeep MathJax for formulae and equations for body of text
- New: raytracing.github.io/books/RayTracingInOneWeekend.html
- Fix: Text, Chapter 7, Add `#include "random.h"` in code blocks
- Fix: Text, Chapter 10, Added metal fuzziness parameter for initial dielectric
- Fix: Text, Chapter 13, Added metal fuzziness parameter
- Fix: Code, Removed extraneous `;` from `vec3::&operator[]` signature
- Delete: Code, `vec3 p = r.point_at_parameter(2.0);` in main.cc

### _The Next Week_
- Change: Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Consistent use of spaces in code blocks
- Change: Text, Chapter 3, Consistent use of spaces in code blocks
- Change: Text, Chapter 4, Consistent use of spaces in code blocks
- Change: Text, Chapter 5, Consistent use of spaces in code blocks
- Change: Text, Chapter 5, added "texture" to "We can use that texture on some spheres"
- Change: Text, Chapter 7, Consistent use of spaces in code blocks
- Change: Text, Chapter 7, "This is yz and xz" changed to "This is xz and yz"
- Change: Text, Chapter 8, Changed "And the changes to Cornell is" to "... Cornell are"
- Change: Text, Chapter 9, Changed short `if` statements to two lines for Consistency
- Change: Text, Chapter 10, Consistent use of spaces in code blocks
- Change: Code and Text, Chapter 9, cleaned up implementation of `constant_medium::hit`
- Change: Code and Text, Chapter 9, Rewrote debug functionality in `constant_medium::hit`
- New: raytracing.github.io/books/RayTracingTheNextWeek.html
- New: README.md, source README.md
- New: Markdeep page created for entire body of text
- New: Markdeep MathJax created for formulae and equations for body of text
- New: Earth map picture for use in rendering
- Fix: Text, Chapter 2, The `lambertian` class definition now uses `vec3` instead of `texture`
- Fix: Text, Chapter 7, Changed `cornell_box` hittable array size to 5
- Fix: Code and Text, Chapter 3, Changed `List[0]` to `List[i]` in `hittable_list::bounding_box()`
- Fix: Code and Text, Chapter 3, Replaced `fmax` and `fmin` with `ffmax` and `ffmin`
- Fix: Code, Add missing headers to `constant_medium.h` to fix g++ compiler error

### _The Rest of Your Life_
- Change: Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 3, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 8, Changed calculation of `a` axis to pseudocode
- Change: Text, Chapter 8, Consistent use of spaces in code blocks
- New: raytracing.github.io/books/RayTracingTheRestOfYourLife.html
- New: README.md, source README.md
- New: Markdeep page created for entire body of text
- New: Markdeep MathJax created for formulae and equations for body of text
- Fix: Text, Chapter order starting from chapter 2
- Fix: Text, Renamed figures and images to match new chapter numbering
- Fix: Text, Chapter 4, Rewrote formula for "Color" to "Color = A * color(direction"
- Fix: Code and Text, Chapter 6, `material::scattering_pdf` now returns type float
- Fix: Code and Text, Chapter 6, removal of factor of 2 to `random_cosine_direction` calculation


----------------------------------------------------------------------------------------------------
# v1.123.0  (2018-08-26)

- New: First GitHub release of _Ray Tracing: The Rest of Your Life_.


----------------------------------------------------------------------------------------------------
# v1.54.0  (2018-08-26)

- New: First GitHub release of _Ray Tracing in One Weekend_.


----------------------------------------------------------------------------------------------------
# v1.42.0  (2018-08-26)

- New: First GitHub release of _Ray Tracing: The Next Week_.

