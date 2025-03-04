Change Log / Ray Tracing in One Weekend
====================================================================================================

# v4.0.2 (in progress)

### Common
  - Fix    -- Fixed some dangling references to `random_in_unit_sphere()` (#1637)
  - Fix    -- Clarify `uniform_real_distribution` usage for `random_double()` (#1680)

### In One Weekend
  - Fix    -- Fix equation for refracted rays of non-unit length (#1644)
  - Fix    -- Typo "trigonometric qualities" -> "trigonometric identities"

### The Next Week

### The Rest of Your Life
  - Fix    -- Typo in equation in book 3, section 12.3 (#1686)


----------------------------------------------------------------------------------------------------
# v4.0.1 (2024-08-31)

### Common
  - Change -- Include hittable.h from material.h; drop `hit_record` forward declaration (#1609)
  - Change -- Refactor sphere to use ray representation for animate center (#1621)
  - Change -- All headers assume implicit rtweekend.h include (#1628)
  - Fix    -- Big improvement to print version listing font size (#1595) and more compact line
              height for code listings in both print and browser.
  - Fix    -- Slight improvement to `rotate_y::hit()` function (#1484)
  - Fix    -- Fixed possible bogus values from `random_unit_vector()` due to underflow (#1606)

### In One Weekend
  - Fix    -- Fixed usage of the term "unit cube" for a cube of diameter two (#1555, #1603)
  - Fix    -- Fixed broken highlighting on some code listings (#1600)

### The Next Week
  - Fix    -- Add missing ellipsis in listing 2.62 (#1612)

### The Rest of Your Life
  - Fix    -- Fix typo of "arbitrary" (#1589)
  - Fix    -- Fix X-axis label for figure 3.08 (Approximating the nonuniform f()) (#1532)
  - Fix    -- Corrected scatter angle theta range in section 3.5.3 (The Scattering PDF) (#1331)
  - Fix    -- Clarify the distinction between average and expected value (#1535)
  - New    -- Added a bit more explanation of Buffon's needle problem (#1529)


----------------------------------------------------------------------------------------------------
# v4.0.0 (2024-07-26)

From our last official v3.2.3 release (three and a half years ago!), this major release includes all
changes in the v4.0.0-alpha.1 and v4.0.0-alpha.2 releases, plus the changes listed immediately
below. Generally, this represents a large overhaul of all three books and their code, and will
require large changes to any code you've based on the prior v3.2.3 version. Going forward, we plan
to avoid such massive, long-running development branches, at the expense of more frequent minor and
major releases.

There's still a fair amount of work remaining on book three, which we'll work on after this release.

### Common
  - Change -- Use delegating constructors where helpful (#1489)
  - Change -- Standardized our use of `begin`/`end` standard C++ iterators (#1551)
  - Fix    -- CSS reformatting and fixes (#1567)
  - Fix    -- Add workaround for image and figure captions using latest Markdeep versions (#1583)
  - New    -- Add DOCTYPE declaration to all Markdeep documents (#1566)
  - New    -- Add explicit std:: namespacing almost everywhere (#1487)

### The Next Week
  - Delete -- Remove debug output code from `constant_medium::hit()` function (#1495)
  - Change -- Convert `perlin` class to use static arrays instead of dynamically allocated (#1483)
  - Fix    -- Workaround Markdeep issue for code listings with tag-like tokens (#1463)

### The Rest of Your Life
  - Change -- Simplified the `onb` class, and renamed or deleted functions (#1080)
  - Change -- Many small updates following walkthrough of book 3 (#988, #1317)
  - Change -- Use plain array for `estimate_halfway` program (#1523)
  - Change -- Refactored the ONB class to remove unused methods and generally simplify (#1088)
  - Change -- Use `ICD(d)` instead of `f(d)` for inverse cumulative distribution for clarity (#1537)
  - Fix    -- Add missing signature updates for `material::scatter()` functions
  - Fix    -- Avoid `hittable_list` of lights in book until code is ready (#1318)


----------------------------------------------------------------------------------------------------
# v4.0.0-alpha.2 (2024-04-07)

This alpha wraps up most of the major changes we expect to make to book 2 for the impending v4.0.0
release, along with a bunch of updates to the other two books. Since the alpha.1 release last
August, we've been lucky to have onboarded two new contributors: Arman Uguray and Nate Rupsis.
They've been helping out a ton with this release, and Arman is also developing his GPU Ray Tracing
book at the same time!

This release is a bit faster, thanks to some new BVH optimizations. We've eliminated the negative
radius sphere hack to model hollow spheres, instead accomplishing this with refraction indices. This
eliminates a bunch of places in the code where we had to accomodate this, and probably a bunch of
bugs we still haven't found. We now load texture images in linear color space, fixing a long-running
bug where we were gamma-correcting our textures twice -- you'll notice object texture maps look a
bit darker and less washed out. Refraction text has gotten a bit of an overhaul, and a better
example of total internal reflection. Of course, this also includes a load of small fixes, tweaks,
and improvements.

Our current plan is to get the final v4.0.0 release out the door by SIGGRAPH 2024, targeting July
28. With that, here are the latest changes since our alpha.1 release:

### Common
  - Delete -- Removed `rtw_stb_image.h` header from book 1 source, as it's unused there.
  - Change -- Increase compile warning levels for MSVC, and corrected newly-flagged code.
  - Change -- Default to using post-increment everywhere
  - Change -- We've removed the few cases where we used C++ default constructors. Instead, we either
              require all parameters, or use operator overloading to use default values.
  - Change -- For clarity across audiences with broad programming backgrounds, we now use
              `double(x)` instead of `static_cast<double>(x)`, and similarly for other types, for
              easier readability for non-C++ programmers.
  - Change -- The `ray` class constructors no longer use C++ default parameter values
  - Change -- Remove pixel sampling knowledge from `write_color()`. This simplifies `write_color()`
              to take only the desired output color, and made each phase in color computation easier
              to understand.
  - Change -- `ray::origin()` and `ray::direction()` getters now return const references, avoiding
              unnecessary copies.
  - Change -- Cleaned up the use of the `hit_record` class in `material.h`
  - Change -- All books now point to the project wiki instead of the in1weekend blog for further
              reading links.
  - Change -- New BVH optimization splits the bounds according to the longest bounding box
              dimension, yielding a 15-20% speedup (#1007)
  - Change -- Reversed the ray-sphere direction and calculations throughout equations and code for
              all books. This ended up simplifying equations and code in several places (#1191)
  - Change -- Pass `vec3`, `point3`, `ray`, and `color` parameters by const reference where
              possible (#1250)
  - Change -- Changed BVH construction (removed const qualifer for objects vector) so sorting is
              done in place, and copying of vector is avoided, yielding better BVH build performance
              (#1327, #1388, #1391)
  - Change -- Implement hollow spheres using refraction index instead of negative radii.
              Additionally, we now block negative radius spheres. This fixes a bunch of corner
              cases with inverted spheres (#1420)
  - Change -- Refactor pixel subsampling to make the sampling functions simpler and better focused
              in scope (#1421)
  - Change -- All constructor parameter names now match their member names if assigned directly. C++
              can handle this without ambiguity, and it means we don't have to come up with
              alternate names for everything (#1427)
  - Change -- `material::scatter()` gets a trivial default implementation (#1455)
  - Fix    -- Fixed section describing total internal reflection. It turns out that spheres with
              refraction index greater than the surrounding atmosphere cannot exhibit total internal
              reflection. Changed example to instead model a bubble of air in water, and updated the
              rendered images to match (#900)
  - Fix    -- Fix references from `random_in_hemisphere()` to `random_on_hemisphere()` (#1198)
  - Fix    -- The `linear_to_gamma()` function has been hardened against negative inputs (#1202)
  - Fix    -- Fixed default camera look-from and look-at values (#1341)
  - Fix    -- The `quad` bounding box now considers all four vertices instead of erroneously only
              using two (#1402)
  - New    -- Added PRINTING.md to give information about how to print these books to PDF or paper.
              We will also be including PDFs of each book with each new GitHub release going
              forward.

### In One Weekend
  - Change -- Update reference to "Fundamentals of Interactive Computer Graphics" to "Computer
              Graphics: Principles and Practice". This is the name used by newer editions of the
              book.
  - Change -- Updated the "Next Steps" section at the end of book 1 (#1209)
  - Change -- Update rtweekend.h header introduction and use (#1473)
  - Fix    -- Fix code listing ordering bug with `lambertian` texture support (#1258)
  - New    -- Improved help for the very first build and run.
  - New    -- Define albedo prior to first use (#1430)

### The Next Week
  - Change -- Lots of miscellaneous edits and clarifications to book two as we encountered them.
              This also includes various improvements to code listings to provide better context and
              address discrepancies between the listings and the actual source code.
  - Change -- `perlin::turb()` no longer defaults the value for the depth parameter.
  - Change -- AABB automatically pads to mininmum size for any dimension; no longer requires
              primitives to call aabb::pad() function.
  - Change -- Switch from ray = A + tb to ray = Q + td in AABB text.
  - Change -- Update checker scale to 0.32
  - Change -- Refactor AABB class. Renamed `aabb::axis()` to `aabb::axis_interval()`. Minor
              refactoring of `aabb::hit()` function. (#927, #1270)
  - Change -- Reworked the AABB chapter. Created skippable sections for planar coordinates
              derivation (#1236)
  - Fix    -- Updated book 2 images to match the latest code.
  - Fix    -- Images loaded for texture mapping are now converted from their original gamma to
              linear color space for use. Rendered images are still gamma corrected to 2.0 on
              output (#842)
  - Fix    -- Fix regression in calls to Perlin `turb()` functions with scaled points (these should
              be unscaled). (#1286)
  - New    -- Add section on alternative 2D primitives such as triangle, ellipse and annulus (#1204,
              #1205)

### The Rest of Your Life
  - Fix    -- Add missing backslash for LaTeX `operatorname` (#1311)
  - Fix    -- Fix LaTeX functions with underscore (#1330)


----------------------------------------------------------------------------------------------------
# v4.0.0-alpha.1 (2023-08-06)

It's been quite a while since our last release of v3.2.3 at the end of 2020. For this cycle, we've
tackled a load of significant backlog items, including rewrites of much of our underlying code. As
always, the primary idea isn't to provide the best or most optimal implementation, but instead to put
out simple, sometimes crude first approximations of the main components of writing a ray tracer.

Highlights include large rewrites and expansions of the book text, a large refactoring of our camera
class, folding `moving_sphere` functionality into `sphere`, adding a new `interval` class for use in
multiple contexts, creating a new general `quad` primitive to replace the old `*_rect` primitives,
and the addressing of hundreds of issues and requested features. The line-item changes below should
give you an idea of v4 includes.

In order to drive this release to resolution, we're releasing our alpha.1 version to coincide with
the start of SIGGRAPH 2023. We've pretty much finished with book one, though there's a fair amount
left for books two and three. Our plan is to keep crunching for a final v4.0.0 release by the end of
2023.

Since this is an alpha, we would greatly appreciate any feedback you might have. Let us know by
creating issues up on the GitHub project.

### Common
  - Delete -- `box`, `xy_rect`, `yz_rect`, `xz_rect` classes. These are replaced with new `quad`
              primitive (#292, #780, #681)
  - Change -- Use `class` instead of `struct` throughout for simpler C++ (#781)
  - Change -- Moved all class method definitions inside class definition (#802)
  - Change -- Class public/private access labels get consistent two-space indents (#782)
  - Change -- Updated classes to use private access for class-private variables (#869)
  - Change -- Made our code `inline` clean. We now use `inline` in all header function definitions
              to guard against copies in multiple C++ translation units (#803)
  - Change -- Retired the `src/common/` directory. Each book now has complete source in one
              directory
  - Change -- Significant rewrite and expansion of the `camera` class
  - Change -- `aabb` class constructor treats two params as extreme points in any orientation (#733)
  - Change -- `hittable:hit()` methods use new interval class for ray-t parameter
  - Change -- `interval::clamp()` replaces standalone `clamp` utility function
  - Change -- `aabb` class uses intervals for each axis (#796)
  - Change -- `hittable` member variable `ptr` renamed to `object`
  - Change -- General rename of `mat_ptr` to `mat` (material)
  - Change -- `hittable::bounding_box()` signature has changed to always return a value (#859)
  - Change -- Replaced random vector in `isotropic` with `random_unit_vector`
  - Change -- Use std::clog instead of std::cerr to log scanline progress (#935)
  - Change -- Updated figures throughout for improved clarity when possible
  - Change -- Generated images are now output gamma-corrected rather than in linear space
              (#980, #1033)
  - Change -- The `camera` class now handles images with width or height of one (#682, #1040)
  - Fix    -- CSS fix for cases where code listing overflows; change to fit content (#826)
  - Fix    -- Enabled compiler warnings for MSVC, Clang, GNU. Cleaned up warnings as fit (#865)
  - Fix    -- Remove redundant `virtual` keyword for methods with `override` (#805)
  - Fix    -- `rect` hit returning NaNs and infinities (#681)
  - Fix    -- Add `\mathit` to italic math variables to fix slight kerning issues in equations
              (#839)
  - Fix    -- Fixed issues in Bib(La)TeX entries.
  - New    -- Introduce new `interval` class used throughout codebase (#777)
  - New    -- `rtw_image` class for easier image data loading, better texture file search (#807)
  - New    -- 2D `quad` primitive of arbitrary orientation (#756)
  - New    -- `box()` utility function returns `hittable_list` of new `quad` primitives (#780)

### In One Weekend
  - Change -- Updated all rendered images in text
  - Change -- Significant update to the diffuse reflection section (#696, #992)
  - Change -- Updated and clarified text around ray generation and the camera model
  - New    -- More commentary about the choice between `double` and `float` (#752)
  - New    -- Software context around the shadow acne listing

### The Next Week
  - Delete -- The `moving_sphere` class is deprecated, and functionality moved to `sphere` (#1125)
  - Change -- Rearranged the texture-mapping presentation. The three types (solid, spatial, image)
              are now sequenced in that order, and the checker texture presented more explicitly as
              an illustration of a spatial texture.
  - Change -- Broad rewrite of time management for moving objects, primarily `camera` and
              `sphere`, but also impacting the API for `hittable::bounding_box()` (#799)
  - Change -- The `sphere` class now includes animation capability originally in `moving_sphere`
              (#1125)
  - Fix    -- Fixed `bvh_node` constructor definition signature (#872)
  - Fix    -- Fixed scaling for final Perlin noise texture (#896).
  - New    -- Add listing to use new `bvh_node` class in the `random_spheres` scene (#715).

### The Rest of Your Life
  - Fix    -- Added missing functionality for `isotropic` (#664)
  - Fix    -- Variable `direction` was used without being defined in listing 11 (#831)
  - Fix    -- Fixed uniform sampling (#934)


----------------------------------------------------------------------------------------------------
# v3.2.3 (2020-12-07)

### Common
  - Change -- Markdeep library URL updated to new location

### The Next Week
  - Fix    -- Correct parameter name typo for `bvh_node` constructor parameter `src_objects`


----------------------------------------------------------------------------------------------------
# v3.2.2 (2020-10-31)

### Common
  - Change -- Refactor `sphere::hit()` method to reuse common blocks of code.
  - Change -- Improved the explanation and calculation of sphere UV coordinates (#533)
  - Fix    -- Added `fmin` to book text for `cos_theta` of `refract` (#732)
  - Fix    -- Standardized naming for ray-t and time parameters (#746)
  - Fix    -- `random_unit_vector()` was incorrect (#697)
  - Fix    -- Synchronize text and copies of `hittable.h`
  - Fix    -- Synchronize copies of `hittable_list.h`, `material.h`, `sphere.h`

### In One Weekend
  - Change -- Wrote brief explanation waving away negative t values in initial normal sphere
  - Fix    -- Catch cases where `lambertian::scatter()` yields degenerate scatter rays (#619)
  - Fix    -- Syntax error in listing 58 (Dielectric material class with reflection) (#768)
  - Fix    -- Correct wording for ray traversal text (#766)

### The Next Week
  - Fix    -- Catch cases where `lambertian::scatter()` yields degenerate scatter rays (#619)

### The Rest of Your Life
  - Fix    -- Missing `override` keyword for `xz_rect::pdf_value()` and `xz_rect::random()` methods
              (#748)
  - Fix    -- Synchronize book and source for `cornell_box()` function.
  - Fix    -- Introduction of light code was introduced out of sequence (#738, #740)
  - Fix    -- `ray_color()` was creating a new light for every ray bounce (#759)


----------------------------------------------------------------------------------------------------
# v3.2.1 (2020-10-03)

### Common
  - Change -- Refactored dielectric class for clarity
  - Fix    -- Update local Markdeep library (for offline reading) to v1.11. The prior version had
              incorrect content (#712)
  - Fix    -- Image texture destructor should call `STBI_FREE` instead of delete (#734)

### In One Weekend
  - Delete -- Remove premature `cstdlib` include; not needed until we use `rand()` (#687)
  - Fix    -- Replace old anti-alias result image with before-and-after image (#679)
  - Fix    -- Listing 29: Added missing `rtweekend.h` include (#691)
  - Fix    -- Undefined `vup` variable in camera definition (#686)
  - Fix    -- Listing 51: Add missing `hittable.h`, `rtweekend.h` includes (#693)
  - Fix    -- Listing 59: ["Full glass material"] Diverged from source
  - Fix    -- Fix error in citation section (#721)
  - Fix    -- Listings 33, 39: Add  consistent function signature for `trilinear_interp` (#722)

### The Next Week
  - Delete -- Remove unused u,v,w variables in initial `perlin::noise()` function (#684)
  - Change -- `bvh_node` no longer reorders the source vector of scene objects; uses local copy
              instead (#701)
  - Fix    -- Listing  5: Neglected to add ray time for metal and dielectric materials (#133)
  - Fix    -- Listing 15: In `bvh.h`, add missing `hittable_list.h` include (#690)
  - Fix    -- Listing 33, 34, 38: Change implicit casts to explicit ones (#692)
  - Fix    -- Listing 40: Change `perlin.h` in the caption to `texture.h` (#698)
  - Fix    -- Listing 70: Add missing `bvh.h` (#694)
  - Fix    -- Listing 70 and `main.cc`: Change a fuzz value of a metal sphere to 1.0 which is the
              maximum value (#694)
  - Fix    -- Fix error in citation section (#721)

### The Rest of Your Life
  - Fix    -- Fix errors in citation section (#721)
  - Fix    -- Area equation in section 3.3 Constructing a PDF and nearby text (#735)
  - New    -- Listing 36: Add missing updates to dielectric class for updating specular in scatter
              record


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
  - Delete -- Vestigial `vec3::write_color()` method (now in color.h)
  - Change -- All images and figures renamed to follow more logical convention, using the following
              pattern: `{fig,img}-<book>.<sequence>-<title>.<filetype>` (#495)
  - Change -- `main()` function gets organized into image, world, camera, and render chunks
  - Change -- Added header guards to the text of all three books whenever a new header file was
              introduced, consistent with source code (#645)
  - Change -- Added `override` keywords throughout. This keyword marks a subclass method as one that
              is intended to override a superclass method. It makes the code a bit easier to
              understand, and ensures that your function is actually overriding the method you think
              it is. Which is good, because it already caught an existing bug in _The Rest of Your
              Life_ source. This change includes commenting out the book 3 `isotropic::scatter()`
              method, which was accidentally ignored anyway. (#639, #669)
  - Fix    -- Found a bug in book 3 source `isotropic::scatter()` method. Commented out, using
              default (as it was previously). (#669)
  - New    -- Added constructors that take `color` arguments in addition to the constructors
              taking `shared_ptr<texture>` arguments, simplifying calling code. Applies to
              `checker_texture`, `constant_medium`, `diffuse_light`, `lambertian`, and `isotropic`
              (#516, #644)
  - New    -- Each book gets a section of recommended citation examples (#500)

### In One Weekend
  - Change -- Updated all rendered images except for 1.13, 1.14 (#179, #547, #548, #549, #550, #551,
              #552, #553, #554, #555, #556, #557, #560, #561, #562, #563, #564, #565, #566)
  - Change -- Standard working render width changed to 400 pixels
  - Change -- Image 6 is now a before-and-after pair to illustrate antialiasing
  - Change -- Listing 48: Refactored material and geometry declarations
  - Change -- Listing 52: Refactored assignment of `etai_over_etat`
  - Change -- Listing 56: Refactored material declarations
  - Change -- Listing 61: Refactored material and geometry declarations
  - Fix    -- Corrected various missed change highlights in code listings
  - Fix    -- Listing 7: Added missing `color.h`, `vec3.h` includes
  - Fix    -- Listing 18: Add missing `double t` member of struct `hit_record` (#428)
  - Fix    -- Listing 24: Add missing `color.h` include
  - Fix    -- Listing 30: Add missing `camera.h` include
  - Fix    -- Listing 42: Don't need to include `ray.h` when using `rtweekend.h`
  - Fix    -- Listing 48: Add missing `material.h` include
  - Fix    -- Listing 51: `refract()` function was missing `fabs()` on `sqrt()` argument (#559)
  - Fix    -- Listing 61: Include updated `cam` declaration, show context w/highlighting
  - Fix    -- Listing 62: Highlight rename of `camera::get_ray()` parameters to s, t (#616)
  - Fix    -- Listing 63: Show reverted scene declarations
  - Fix    -- Listing 68: Show final scene render parameters with highlighting
  - Fix    -- Rewrote refracted ray perpendicular and parallel components for correctness (#526)
  - New    -- Listing 50: Show the updated material definitions

### The Next Week
  - Delete -- Deleted the section covering the old `flip_face` class, renumbered images as this
              eliminated the rendering with missing Cornell box faces (#270, #482, #661)
  - Delete -- Scenes 7 & 9 from the original (`cornell_balls` and `cornell_final`), as these were
              not covered in the book. Made the source and book consistent with each other. There
              are now a total of eight scenes for the second book (#653, #620)
  - Change -- Listing 10: Separate out world & camera definitions in main (#646)
  - Change -- Updated most rendered images for book 2: 2.01-2.03, 2.07-2.13, 2.15-2.22.
  - Change -- Scenes get custom image parameters (#650)
  - Fix    -- Reduced code duplication in `dielectric::scatter()` function
  - Fix    -- "Intance" typo in Chapter 8.1 to "Instance" (#629)
  - Fix    -- Listing 7: Show reverted viewing parameters from book 1 final scene
  - Fix    -- Typo in listing caption for filename `moving-sphere.h`

### The Rest of Your Life
  - Change -- Use `vup` for camera, as in other two books
  - Fix    -- World and camera setup in `main()`, and include full body in book listing (#646)
  - New    -- `flip_face` moved to book 3, where it's needed for the light source (#661)


----------------------------------------------------------------------------------------------------
# v3.1.2 (2020-06-03)

### In One Weekend
  - Fix    -- Correct typo: "Intance Translation" -> "Instance Translation"
  - Fix    -- Corrected geometry type when computing distance between two points, final scene (#609)

### The Rest of Your Life
  - Fix    -- Missing closing parenthesis in listing 10 (#603)
  - Fix    -- Tiny improvements to the lambertian::scatter() development (#604)
  - Fix    -- Correct geometry type and unit vector method in `ray_color()`, listing 20 (#606)
  - Fix    -- Listing 26: alternate `random_double()` switched `distribution`, `generator` (#621)
  - Fix    -- Listing 28, 30: `light_shape` should have default material, not `0` (#607)
  - Fix    -- Listing 30: `mixture_pdf` needs `shared_ptr` arguments (#608)


----------------------------------------------------------------------------------------------------
# v3.1.1 (2020-05-16)

### Common
  - Change -- Camera code improvements to make it more robust when any particular value changes.
              Also, the code develops in a smoother series of iterations as the book progresses.
              (#536)
  - Fix    -- Refactoring the camera code in v3.1.0 missed updating the viewport to match, resulting
              in distorted renders (#536)

### In One Weekend
  - Change -- The C++ `<random>` version of `random_double()` no longer depends on `<functional>`
              header.
  - Change -- Refactored `random_scene()`. More named intermediate values, sync'ed with source.
              (#489)
  - Fix    -- Camera initialization with explicit up vector (#537)
  - Fix    -- Changed some text around the camera model and the camera defocus blur model (#536)

### The Next Week
  - Change -- Refactored `random_scene()`. Added more named intermediate values, sync'ed with
              version in _In One Weekend_ and with source. Added highlight for update from last
              version in book 1. (#489)
  - Change -- The C++ `<random>` version of `random_double()` no longer depends on `<functional>`
              header.
  - Fix    -- Added clarification about updating lambertian variables from `color` to `solid_color`.
  - Fix    -- Corrected for-loop indices (they differed from the version in book 1) in
              `random_scene()`.
  - Fix    -- Introduce "Texture Coordinates for Spheres" in Chapter 4 to support (u,v) coordinates
              in `hit_record` (#496)
  - Fix    -- Small correction: we now use `std::sort` instead of `qsort` (#490)


----------------------------------------------------------------------------------------------------
# v3.1.0 (2020-05-03)

This minor upgrade adds some fixes and changes that are a bit more than just patches. The text now
has subchapter headings to help readers browse content and get a bit more context. We're introducing
new type aliases `point3` and `color` for `vec3` to better indicate the underlying mathematical
types of parameters and variables. Overall, a bunch of small improvements that we'd recommend
adopting, but may warrant comparison with any current projects.

### Common
  - Change -- Minor change to use new `point3` and `color` type aliases for `vec3` (#422)
  - Change -- Renamed `constant_texture` to `solid_color`, add RGB constructor (#452)
  - Change -- Moved `vec3::write_color()` method to utility function in `color.h` header (#502)
  - Change -- Switch from `ffmin`/`ffmax` to standard `fmin`/`fmax` (#444, #491)
  - Change -- Math notation to bold uppercase points, bold lowercase no-barb vectors (#412)
  - Change -- Books use Markdeep's image class=pixel for rendered image fidelity (#498)
  - Fix    -- Include cmath in vec3.h (#501)
  - Fix    -- Scattered improvements to the text
  - New    -- Subchapters throughout all three books (#267)
  - New    -- Add explanation for padding `aarect` in the zero dimension (#488)

### In One Weekend
  - Change -- Define image aspect ratio up front, then image height from that and the image width
  - Change -- Default image sizes changed from 200x100 to 384x216
  - Change -- First image size changed to 256x256
  - Fix    -- Improve image size and aspect ratio calculation to make size changes easier
  - Fix    -- Added `t` parameter back into `hit_record` at correct place
  - Fix    -- Image basic vectors off by one
  - Fix    -- Update image and size for first PPM image
  - Fix    -- Update image and size for blue-to-white gradient image
  - Fix    -- Update image and size for simple red sphere render
  - Fix    -- Update image and size for sphere with normal-vector coloring
  - Fix    -- Correct typo in "What's next?" list to rejoin split paragraph on "Lights." Adjust
              numbering in rest of list.

### The Next Week
  - Change -- Large rewrite of the `image_texture` class. Now handles image loading too. (#434)


----------------------------------------------------------------------------------------------------
# v3.0.2 (2020-04-11)

### Common
  - Change -- Every book source now includes from a single common acknowledgments document
  - Fix    -- Code styling for source code both inline and in fenced blocks (#430)

### In One Weekend
  - Fix    -- Correct typo: "consine" to "cosine"

### The Next Week
  - Fix    -- `shared_ptr` dereference and simplify code in `hittable_list::bounding_box()` (#435)
  - Fix    -- Erroneous en-dash in code block. Replace `–>` with `->` (#439)
  - Fix    -- Introduce `u`,`v` surface coordinates to `hit_record` (#441)
  - Fix    -- Add highlight to new `hittable::bounding_box()` method (#442)

### The Rest of Your Life
  - Fix    -- Unitialized variable in first version of `integrate_x_sq.cc`
  - Fix    -- Remove unreferenced variables in several sample programs
  - Fix    -- Correct program computation of the integral of x^2 (#438)


----------------------------------------------------------------------------------------------------
# v3.0.1 (2020-03-31)

### Common
  - Delete -- Delete old README files specific to each book (#410)
  - Fix    -- Display rendered images as pixelated instead of smoothed (#179)

### In One Weekend
  - Fix    -- Remove duplicated text and reword on the camera up vector (#420)


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
  - Change -- Default floating-point type changed from `float` to `double` (#150)
  - Change -- Materials are now referenced with `std::shared_ptr` pointers
  - Change -- Complete elimination of bare pointers and `new`/`delete`
  - Change -- `hittable_list` uses `std::vector` plus `std::shared_ptr` pointers
  - Change -- Header cleanup across the source code (#218, #220)
  - Change -- Cleaned up standard C++ header use (#19)
  - Change -- Improved random number generator utilities
  - Change -- Replace MAXFLOAT with (portable) infinity (#195, #216)
  - Change -- A _lot_ of code cleanup, refactoring, renaming (#192)
  - Change -- Disable compile warnings for external `stb_image.h` on Windows
  - Change -- Replace pi with portable version (#207)
  - Change -- `ray_color()` function now has max depth passed in, rather than hard-coding it (#143)
  - Change -- Added `random_in_unit_sphere()`, `random_unit_vector()`, `random_in_hemisphere()` to
              vec3.h. Fixed places where we were using one but should have been using another.
              (#145)
  - Change -- General rework of the `vec3` header (#153, #156, #215)
  - Change -- Clarify sphere intersection code, plus slight perf improvement (#113)
  - Change -- `ray::point_at_parameter()` renamed to `ray::at()`
  - Change -- Moved `ffmin()`, `ffmax()` from `aabb.h` to `rtweekend.h`
  - Change -- Move low-level utility functions to more appropriate headers
  - Change -- `squared_length()` renamed to `length_squared()`
  - Change -- Update `sphere::hit()` function.
  - Change -- Refraction variables renamed to match reflection variable names
  - Change -- Simplify lambertian scatter direction calculation
  - Fix    -- Diffuse PDF computation uses random point _on_ sphere, rather than _inside_
  - Fix    -- Improve color [0,1] -> [0,255] mapping
  - New    -- CMake configuration & build
  - New    -- Added progress output for main programs (#139)
  - New    -- `src/common` directory for code shared across books
  - New    -- Common project-wide header: `src/common/rtweekend.h`
  - New    -- File constants.h with portable math constants (#151)
  - New    -- `vec3::write_color` - provides a robust output method for color data (#93)
  - New    -- `degrees_to_radians()` utility function (#217)
  - New    -- `random_int()`, `random_double()`, and `vec3::random()` utility functions
  - New    -- Added safety value when surface texture has null data
  - New    -- Main programs now define and handle parameterized background color

### Common to All Books
  - Change -- Code in source and in book reformatted to a consistent 96-column line length (#219)
  - Change -- Lots more highlighting of changed code in books to aid reading
  - Change -- Math typesetting fixes throughout the books (#13)
  - Change -- Books now use Markdeep's chapter indirection syntax
  - Change -- Updated several output images to match code updates
  - Change -- Books general styling improvements (#197)
  - Change -- Refactored acknowledgements. These are now moved to and duplicated in each book
  - Fix    -- Fixed various minor problems in the text
  - New    -- Added code listing captions, including source file name, for all books (#238)
  - New    -- Added captions to all figures (#238)
  - New    -- Local copy of `markdeep.min.js` for offline reading

### In One Weekend
  - Change -- Reworked Lambertian reflection text (#155)
  - Change -- Revised the figure for computing a random reflection vector (#142)
  - Fix    -- Update `ray_color()` code blocks to match current source (#391)
  - New    -- Clarified text around the ideal Lambertian distribution (#155)
  - New    -- Additional explanatory text to the dielectric chapter
  - New    -- Image for hemispherical rendering
  - New    -- Image for dealing with front and back faces (#326)

### The Next Week
  - Change -- Added proper handling of front vs back face intersection (#270)
  - Fix    -- Fixed bug in `noise_texture::value()` (#396)
  - Fix    -- Correct first Perlin noise() function in "The Next Week".
  - Fix    -- Fix OCR error in `texture::value()` function (#399)
  - Fix    -- Remove premature declaration of `moving_sphere::bounding_box()` (#405)
  - New    -- "The Next Week" main program added swtich statement for different scenes
  - New    -- "The Next Week" main program now defines all image/camera parameters for each scene

### The Rest of Your Life
  - Delete -- Several unused source files from `src/TheRestOfYourLife`
  - Change -- Improved naming of auxilliary programs in _The Rest of Your Life_ source
  - Fix    -- Delete unused variable `p` in main() (#317)


----------------------------------------------------------------------------------------------------
# v2.0.0 (2019-10-07)

This major release marks an overhaul of the entire series, moving from a primarily PDF format to a
web accessible format using Markdeep (https://casual-effects.com/markdeep/). This represents a huge
overhaul to the contents, particularly around source code blocks in the text, mathematical
typesetting and source-code cleanup.

### Common
  - Delete -- Deprecated existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ repos
  - Change -- Moved existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ content to io repo
  - Change -- Rewrote vec3.h `cross` function for clarity
  - Fix    -- All instances of `hitable` have become `hittable`
  - Fix    -- Replaced `drand48()` with portable `random_double` number generation
  - New    -- General release to web
  - New    -- Created single monolithic raytracing.github.io repo
  - New    -- License change to CC0 in COPYING.txt
  - New    -- CHANGELOG.md
  - New    -- CONTRIBUTING.md
  - New    -- COPYING.txt
  - New    -- README.md
  - New    -- Raytracing.github.io links to all the three books
  - New    -- CSS for all books
  - New    -- CSS for the print variant of the books

### In One Weekend
  - Delete -- Code, `vec3 p = r.point_at_parameter(2.0);` in main.cc
  - Change -- README files updated for top level, source, and books
  - Change -- Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
  - Change -- Text, Syntax highlighting of source modifications
  - Change -- Text, Chapter 3, Reorder include files in code blocks to match src conventions
  - Change -- Text, Chapter 3, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 3, Reordered `vec3` class functions to + - * /
  - Change -- Text, Chapter 4, Reorder include files in code blocks to match src conventions
  - Change -- Text, Chapter 6, Reorder include files in code blocks to match src conventions
  - Change -- Text, Chapter 6, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 7, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 9, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 9, Put function signatures and `{` on the same line
  - Change -- Text, Chapter 10, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 10, Put function signatures and `{` on the same line
  - Change -- Text, Chapter 11, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 13, Put function signatures and `{` on the same line
  - Fix    -- Text, Chapter 7, Add `#include "random.h"` in code blocks
  - Fix    -- Text, Chapter 10, Added metal fuzziness parameter for initial dielectric
  - Fix    -- Text, Chapter 13, Added metal fuzziness parameter
  - Fix    -- Code, Removed extraneous `;` from `vec3::&operator[]` signature
  - New    -- Markdeep page created for entire body of text
  - New    -- Markdeep MathJax for formulae and equations for body of text
  - New    -- Raytracing.github.io/books/RayTracingInOneWeekend.html

### The Next Week
  - Change -- Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
  - Change -- Text, Syntax highlighting of source modifications
  - Change -- Text, Chapter 2, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 3, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 4, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 5, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 5, added "texture" to "We can use that texture on some spheres"
  - Change -- Text, Chapter 7, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 7, "This is yz and xz" changed to "This is xz and yz"
  - Change -- Text, Chapter 8, Changed "And the changes to Cornell is" to "... Cornell are"
  - Change -- Text, Chapter 9, Changed short `if` statements to two lines for Consistency
  - Change -- Text, Chapter 10, Consistent use of spaces in code blocks
  - Change -- Code and Text, Chapter 9, cleaned up implementation of `constant_medium::hit`
  - Change -- Code and Text, Chapter 9, Rewrote debug functionality in `constant_medium::hit`
  - Fix    -- Text, Chapter 2, The `lambertian` class definition now uses `vec3` instead of `texture`
  - Fix    -- Text, Chapter 7, Changed `cornell_box` hittable array size to 5
  - Fix    -- Code and Text, Chapter 3, Changed `List[0]` to `List[i]` in
          `hittable_list::bounding_box()`.
  - Fix    -- Code and Text, Chapter 3, Replaced `fmax` and `fmin` with `ffmax` and `ffmin`
  - Fix    -- Code, Add missing headers to `constant_medium.h` to fix g++ compiler error
  - New    -- Raytracing.github.io/books/RayTracingTheNextWeek.html
  - New    -- README.md, source README.md
  - New    -- Markdeep page created for entire body of text
  - New    -- Markdeep MathJax created for formulae and equations for body of text
  - New    -- Earth map picture for use in rendering

### The Rest of Your Life
  - Change -- Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
  - Change -- Text, Syntax highlighting of source modifications
  - Change -- Text, Chapter 2, Reorder include files in code blocks to match src conventions
  - Change -- Text, Chapter 3, Reorder include files in code blocks to match src conventions
  - Change -- Text, Chapter 6, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 6, Consistent use of spaces in code blocks
  - Change -- Text, Chapter 8, Changed calculation of `a` axis to pseudocode
  - Change -- Text, Chapter 8, Consistent use of spaces in code blocks
  - Fix    -- Text, Chapter order starting from chapter 2
  - Fix    -- Text, Renamed figures and images to match new chapter numbering
  - Fix    -- Text, Chapter 4, Rewrote formula for "Color" to "Color = A * color(direction"
  - Fix    -- Code and Text, Chapter 6, `material::scattering_pdf` now returns type float
  - Fix    -- Code and Text, Chapter 6, removal of factor of 2 to `random_cosine_direction`
              calculation
  - New    -- Raytracing.github.io/books/RayTracingTheRestOfYourLife.html
  - New    -- README.md, source README.md
  - New    -- Markdeep page created for entire body of text
  - New    -- Markdeep MathJax created for formulae and equations for body of text


----------------------------------------------------------------------------------------------------
# v1.123.0  (2018-08-26)

  - New    -- First GitHub release of _Ray Tracing: The Rest of Your Life_.


----------------------------------------------------------------------------------------------------
# v1.54.0  (2018-08-26)

  - New    -- First GitHub release of _Ray Tracing in One Weekend_.


----------------------------------------------------------------------------------------------------
# v1.42.0  (2018-08-26)

  - New    -- First GitHub release of _Ray Tracing: The Next Week_.
