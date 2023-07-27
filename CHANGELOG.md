Change Log -- Ray Tracing in One Weekend
====================================================================================================

# v3.2.3 (2020-12-07)

### Common
  - Change: Markdeep library URL updated to new location

### The Next Week
  - Fix: Correct parameter name typo for `bvh_node` constructor parameter `src_objects`


----------------------------------------------------------------------------------------------------
# v3.2.2 (2020-10-31)

### Common
  - Fix: Added `fmin` to book text for `cos_theta` of `refract` (#732)
  - Fix: Standardized naming for ray-t and time parameters (#746)
  - Fix: `random_unit_vector()` was incorrect (#697)
  - Fix: Synchronize text and copies of `hittable.h`
  - Fix: Synchronize copies of `hittable_list.h`, `material.h`, `sphere.h`
  - Change: refactor `sphere::hit()` method to reuse common blocks of code.
  - Change: Improved the explanation and calculation of sphere UV coordinates (#533)

### In One Weekend
  - Fix: Catch cases where `lambertian::scatter()` yields degenerate scatter rays (#619)
  - Fix: Syntax error in listing 58 (Dielectric material class with reflection) (#768)
  - Fix: Correct wording for ray traversal text (#766)
  - Change: Wrote brief explanation waving away negative t values in initial normal sphere

### The Next Week
  - Fix: Catch cases where `lambertian::scatter()` yields degenerate scatter rays (#619)

### The Rest of Your Life
  - Fix: Missing `override` keyword for `xz_rect::pdf_value()` and `xz_rect::random()` methods
    (#748)
  - Fix: Synchronize book and source for `cornell_box()` function.
  - Fix: Introduction of light code was introduced out of sequence (#738, #740)
  - Fix: `ray_color()` was creating a new light for every ray bounce (#759)


----------------------------------------------------------------------------------------------------
# v3.2.1 (2020-10-03)

### Common
  - Change: Refactored dielectric class for clarity
  - Fix: Update local Markdeep library (for offline reading) to v1.11. The prior version had
    incorrect content (#712)
  - Fix: Image texture destructor should call `STBI_FREE` instead of delete (#734)

### In One Weekend
  - Delete: Remove premature `cstdlib` include; not needed until we use `rand()` (#687)
  - Fix: Replace old anti-alias result image with before-and-after image (#679)
  - Fix: Listing 29: Added missing `rtweekend.h` include (#691)
  - Fix: Undefined `vup` variable in camera definition (#686)
  - Fix: Listing 51: Add missing `hittable.h`, `rtweekend.h` includes (#693)
  - Fix: Listing 59: ["Full glass material"] Diverged from source
  - Fix: Fix error in citation section (#721)
  - Fix: Listings 33, 39: Add  consistent function signature for `trilinear_interp` (#722)

### The Next Week
  - Change: `bvh_node` no longer reorders the source vector of scene objects; uses local copy
    instead (#701)
  - Delete: Remove unused u,v,w variables in initial `perlin::noise()` function (#684)
  - Fix: Listing  5: Neglected to add ray time for metal and dielectric materials (#133)
  - Fix: Listing 15: In `bvh.h`, add missing `hittable_list.h` include (#690)
  - Fix: Listing 33, 34, 38: Change implicit casts to explicit ones (#692)
  - Fix: Listing 40: Change `perlin.h` in the caption to `texture.h` (#698)
  - Fix: Listing 70: Add missing `bvh.h` (#694)
  - Fix: Listing 70 and `main.cc`: Change a fuzz value of a metal sphere to 1.0 which is the maximum
    value (#694)
  - Fix: Fix error in citation section (#721)

### The Rest of Your Life
  - Fix: Fix errors in citation section (#721)
  - Fix: Area equation in section 3.3 Constructing a PDF and nearby text (#735)
  - Add: Listing 36: Add missing updates to dielectric class for updating specular in scatter record


----------------------------------------------------------------------------------------------------
# v3.2.0 (2020-07-18)

We're still chasing that elusive stable project state where we're mostly done with large changes,
yet we keep finding more and more to tweak and improve. Besides the usual batch of corrections and
small improvements, for this change we plodded through the complete code progression for both books
one and two (_In One Weekend_ and _The Next Week_). This caught a _lot_ of issues (to our dismay),
and allowed us to generate a complete set of new render images for both books, to catch up with all
of the changes we've been making. The end result is that readers should find a significantly better
agreement between the book and their code as they progress, and their renders should also generally
match.

Besides the new rendered images, we also much improved the image parameters, which were frequently
missing from the previous version, leaving readers to guess at their values, or go to the code to
try to figure out how we created some of the images. In general, our working renders are now 400
pixels wide, usually 16:9 aspect ratio. We now use an explicit aspect ratio and deduce the image
height and other camera values, so you can tweak your render size just by changing the image width
(instead of updating a bunch of dependent parameters).

One interesting late change we made was adding explicit C++ `override` labels to subclass methods.
We did this mostly to aid code readers, but were surprised to find that it actually caught a pretty
significant bug hiding in our code (see entry in common changes below).

You'll also see a new citation section at the end of the books, to encourage uniform citations out
in the world, making it easier for people to refer to and track these books.

As is typical, though we roughly follow [semantic versioning](https://semver.org/), we're
considering this release a minor change instead of a major one. It's a common reflex, because people
generally have a (misguided) aversion to bumping the major version a lot. We consider it minor
because most of the changes are quite local, some classes get new constructors and any variances
should be quite simple and easy to fix up. Still, one might consider this more properly a major
version bump.

For our next larger-than-patch release, we're beginning a large revisit of book 3,
_Ray Tracing: The Rest of Your Life_. There's a lot of work to do, and this will likely be a
significant change and improvement. We're hoping that changes to books one and two will be small,
but that's never worked out for us before. Ah, dreams.

### Common
  - Delete: vestigial `vec3::write_color()` method (now in color.h)
  - Change: All images and figures renamed to follow more logical convention, using the following
    pattern: `{fig,img}-<book>.<sequence>-<title>.<filetype>` (#495)
  - Change: `main()` function gets organized into image, world, camera, and render chunks
  - Change: Added header guards to the text of all three books whenever a new header file was
    introduced, consistent with source code (#645)
  - New: Added constructors that take `color` arguments in addition to the constructors
    taking `shared_ptr<texture>` arguments, simplifying calling code. Applies to `checker_texture`,
    `constant_medium`, `diffuse_light`, `lambertian`, and `isotropic` (#516, #644)
  - Change: Added `override` keywords throughout. This keyword marks a subclass method as one that
    is intended to override a superclass method. It makes the code a bit easier to understand, and
    ensures that your function is actually overriding the method you think it is. Which is good,
    because it already caught an existing bug in _The Rest of Your Life_ source. This change
    includes commenting out the book 3 `isotropic::scatter()` method, which was accidentally ignored
    anyway. (#639, #669)
  - Fix: Found a bug in book 3 source `isotropic::scatter()` method. Commented out, using default
    (as it was previously). (#669)
  - New: each book gets a section of recommended citation examples (#500)

### In One Weekend
  - Change: Updated all rendered images except for 1.13, 1.14 (#179, #547, #548, #549, #550, #551,
    #552, #553, #554, #555, #556, #557, #560, #561, #562, #563, #564, #565, #566)
  - Change: Standard working render width changed to 400 pixels
  - Change: Image 6 is now a before-and-after pair to illustrate antialiasing
  - Change: Listing 48: Refactored material and geometry declarations
  - Change: Listing 52: Refactored assignment of `etai_over_etat`
  - Change: Listing 56: Refactored material declarations
  - Change: Listing 61: Refactored material and geometry declarations
  - Fix: Corrected various missed change highlights in code listings
  - Fix: Listing 7: Added missing `color.h`, `vec3.h` includes
  - Fix: Listing 18: Add missing `double t` member of struct `hit_record` (#428)
  - Fix: Listing 24: Add missing `color.h` include
  - Fix: Listing 30: Add missing `camera.h` include
  - Fix: Listing 42: Don't need to include `ray.h` when using `rtweekend.h`
  - Fix: Listing 48: Add missing `material.h` include
  - Fix: Listing 51: `refract()` function was missing `fabs()` on `sqrt()` argument (#559)
  - Fix: Listing 61: Include updated `cam` declaration, show context w/highlighting
  - Fix: Listing 62: Highlight rename of `camera::get_ray()` parameters to s, t (#616)
  - Fix: Listing 63: Show reverted scene declarations
  - Fix: Listing 68: Show final scene render parameters with highlighting
  - Fix: Rewrote refracted ray perpendicular and parallel components for correctness (#526)
  - New: Listing 50: Show the updated material definitions

### The Next Week
  - Delete: Deleted the section covering the old `flip_face` class, renumbered images as this
    eliminated the rendering with missing Cornell box faces (#270, #482, #661)
  - Delete: scenes 7 & 9 from the original (`cornell_balls` and `cornell_final`), as these were not
    covered in the book. Made the source and book consistent with each other. There are now a total
    of eight scenes for the second book (#653, #620)
  - Change: Listing 10: Separate out world & camera definitions in main (#646)
  - Change: Updated most rendered images for book 2: 2.01-2.03, 2.07-2.13, 2.15-2.22.
  - Change: Scenes get custom image parameters (#650)
  - Fix: Reduced code duplication in `dielectric::scatter()` function
  - Fix: "Intance" typo in Chapter 8.1 to "Instance" (#629)
  - Fix: Listing 7: Show reverted viewing parameters from book 1 final scene
  - Fix: Typo in listing caption for filename `moving-sphere.h`

### The Rest of Your Life
  - Change: use `vup` for camera, as in other two books
  - Fix: world and camera setup in `main()`, and include full body in book listing (#646)
  - New: `flip_face` moved to book 3, where it's needed for the light source (#661)


----------------------------------------------------------------------------------------------------
# v3.1.2 (2020-06-03)

### In One Weekend
  - Fix: Correct typo: "Intance Translation" -> "Instance Translation"
  - Fix: Corrected geometry type when computing distance between two points, final scene (#609)

### The Rest of Your Life
  - Fix: Missing closing parenthesis in listing 10 (#603)
  - Fix: Tiny improvements to the lambertian::scatter() development (#604)
  - Fix: Correct geometry type and unit vector method in `ray_color()`, listing 20 (#606)
  - Fix: Listing 26: alternate `random_double()` switched `distribution`, `generator` (#621)
  - Fix: Listing 28, 30: `light_shape` should have default material, not `0` (#607)
  - Fix: Listing 30: `mixture_pdf` needs `shared_ptr` arguments (#608)


----------------------------------------------------------------------------------------------------
# v3.1.1 (2020-05-16)

### Common
  - Fix: Refactoring the camera code in v3.1.0 missed updating the viewport to match, resulting in
    distorted renders (#536)
  - Change: Camera code improvements to make it more robust when any particular value changes. Also,
    the code develops in a smoother series of iterations as the book progresses. (#536)

### In One Weekend
  - Fix: Camera initialization with explicit up vector (#537)
  - Fix: Changed some text around the camera model and the camera defocus blur model (#536)
  - Change: The C++ `<random>` version of `random_double()` no longer depends on `<functional>`
    header.
  - Change: Refactored `random_scene()`. More named intermediate values, sync'ed with source.
    (#489)

### The Next Week
  - Fix: Added clarification about updating lambertian variables from `color` to `solid_color`.
  - Fix: Corrected for-loop indices (they differed from the version in book 1) in `random_scene()`.
  - Fix: Introduce "Texture Coordinates for Spheres" in Chapter 4 to support (u,v) coordinates in
    `hit_record` (#496)
  - Fix: Small correction: we now use `std::sort` instead of `qsort` (#490)
  - Change: Refactored `random_scene()`. More named intermediate values, sync'ed with version in
    _In One Weekend_ and with source. Added highlight for update from last version in book 1. (#489)
  - Change: The C++ `<random>` version of `random_double()` no longer depends on `<functional>`
    header


----------------------------------------------------------------------------------------------------
# v3.1.0 (2020-05-03)

This minor upgrade adds some fixes and changes that are a bit more than just patches. The text now
has subchapter headings to help readers browse content and get a bit more context. We're introducing
new type aliases `point3` and `color` for `vec3` to better indicate the underlying mathematical
types of parameters and variables. Overall, a bunch of small improvements that we'd recommend
adopting, but may warrant comparison with any current projects.

### Common
  - Fix: Include cmath in vec3.h (#501)
  - Fix: Scattered improvements to the text
  - New: Subchapters throughout all three books (#267)
  - New: Add explanation for padding `aarect` in the zero dimension (#488)
  - Change: Minor change to use new `point3` and `color` type aliases for `vec3` (#422)
  - Change: Renamed `constant_texture` to `solid_color`, add RGB constructor (#452)
  - Change: Moved `vec3::write_color()` method to utility function in `color.h` header (#502)
  - Change: Switch from `ffmin`/`ffmax` to standard `fmin`/`fmax` (#444, #491)
  - Change: Math notation to bold uppercase points, bold lowercase no-barb vectors (#412)
  - Change: Books use Markdeep's image class=pixel for rendered image fidelity (#498)

### In One Weekend
  - Fix: Improve image size and aspect ratio calculation to make size changes easier
  - Fix: Added `t` parameter back into `hit_record` at correct place
  - Fix: image basic vectors off by one
  - Fix: Update image and size for first PPM image
  - Fix: Update image and size for blue-to-white gradient image
  - Fix: Update image and size for simple red sphere render
  - Fix: Update image and size for sphere with normal-vector coloring
  - Fix: Correct typo in "What's next?" list to rejoin split paragraph on "Lights." Adjust numbering
    in rest of list.
  - Change: Define image aspect ratio up front, then image height from that and the image width
  - Change: Default image sizes changed from 200x100 to 384x216
  - Change: First image size changed to 256x256

### The Next Week
  - Change: Large rewrite of the `image_texture` class. Now handles image loading too. (#434)


----------------------------------------------------------------------------------------------------
# v3.0.2 (2020-04-11)

### Common
  - Fix: code styling for source code both inline and in fenced blocks (#430)
  - Change: Every book source now includes from a single common acknowledgments document

### In One Weekend
  - Fix: Correct typo: "consine" to "cosine"

### The Next Week
  - Fix: `shared_ptr` dereference and simplify code in `hittable_list::bounding_box()` (#435)
  - Fix: Erroneous en-dash in code block. Replace `–>` with `->` (#439)
  - Fix: Introduce `u`,`v` surface coordinates to `hit_record` (#441)
  - Fix: Add highlight to new `hittable::bounding_box()` method (#442)

### The Rest of Your Life
  - Fix: unitialized variable in first version of `integrate_x_sq.cc`
  - Fix: remove unreferenced variables in several sample programs
  - Fix: correct program computation of the integral of x^2 (#438)


----------------------------------------------------------------------------------------------------
# v3.0.1 (2020-03-31)

### Common
  - Fix: Display rendered images as pixelated instead of smoothed (#179)
  - Delete: delete old README files specific to each book (#410)

### In One Weekend
  - Fix: Remove duplicated text and reword on the camera up vector (#420)


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

### In One Weekend
  - Change: Reworked Lambertian reflection text (#155)
  - Change: Revised the figure for computing a random reflection vector (#142)
  - New: Clarified text around the ideal Lambertian distribution (#155)
  - New: Additional explanatory text to the dielectric chapter
  - New: Image for hemispherical rendering
  - New: Image for dealing with front and back faces (#326)
  - Fix: Update `ray_color()` code blocks to match current source (#391)

### The Next Week
  - Change: Added proper handling of front vs back face intersection (#270)
  - New: "The Next Week" main program added swtich statement for different scenes
  - New: "The Next Week" main program now defines all image/camera parameters for each scene
  - Fix: Fixed bug in `noise_texture::value()` (#396)
  - Fix: Correct first Perlin noise() function in "The Next Week".
  - Fix: Fix OCR error in `texture::value()` function (#399)
  - Fix: Remove premature declaration of `moving_sphere::bounding_box()` (#405)

### The Rest of Your Life
  - Change: Improved naming of auxilliary programs in _The Rest of Your Life_ source
  - Fix: Delete unused variable `p` in main() (#317)
  - Delete: Several unused source files from `src/TheRestOfYourLife`


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

### In One Weekend
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

### The Next Week
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

### The Rest of Your Life
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

