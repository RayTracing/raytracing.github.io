Change Log
================================================================================

v2.0.0 (2019-10-07)
---------------------
Common
- New: General release to web
- New: Created single monolithic raytracing.github.io repo
- New: License change to CC0 in COPYING.txt
- Delete: Deprecated existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ repos
- Change: Moved existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ content to io repo
- Add: CHANGELOG.md
- Add: CONTRIBUTING.md
- Add: COPYING.txt
- Add: README.md
- Add: raytracing.github.io links to all the three books
- Add: CSS for all books
- Add: CSS for the print variant of the books
- Fix: All instances of `hitable` have become `hittable`
- Fix: Replaced `drand48()` with portable `random_double` number generation
- Change: Rewrote vec3.h `cross` function for clarity


_Ray Tracing in One Weekend_
- Fix: Text, Chapter 7, Add `#include "random.h"` in code blocks
- Fix: Text, Chapter 10, Added metal fuzziness parameter for initial dielectric
- Fix: Text, Chapter 13, Added metal fuzziness parameter
- Fix: Code, Removed extraneous `;` from `vec3::&operator[]` signature
- New: Markdeep page created for entire body of text
- New: Markdeep MathJax for formulae and equations for body of text
- New: raytracing.github.io/books/RayTracingInOneWeekend.html
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
- Delete: Code, `vec3 p = r.point_at_parameter(2.0);` in main.cc


_Ray Tracing: The Next Week_
- Fix: Text, Chapter 2, The `lambertian` class definition now uses `vec3` instead of `texture`
- Fix: Text, Chapter 7, Changed `cornell_box` hittable array size to 5
- Fix: Code and Text, Chapter 3, Changed `List[0]` to `List[i]` in `hittable_list::bounding_box()`
- Fix: Code and Text, Chapter 3, Replaced `fmax` and `fmin` with `ffmax` and `ffmin`
- Fix: Code, Add missing headers to constant_medium.h to fix g++ compiler error
- New: raytracing.github.io/books/RayTracingTheNextWeek.html
- Add: README.md, source README.md
- Add: Markdeep page created for entire body of text
- Add: Markdeep MathJax created for formulae and equations for body of text
- Add: Earth map picture for use in rendering
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


_Ray Tracing: The Rest of Your Life_
- Fix: Text, Chapter order starting from chapter 2
- Fix: Text, Renamed figures and images to match new chapter numbering
- Fix: Text, Chapter 4, Rewrote formula for "Color" to "Color = A * color(direction"
- Fix: Code and Text, Chapter 6, `material::scattering_pdf` now returns type float
- Fix: Code and Text, Chapter 6, removal of factor of 2 to `random_cosine_direction` calculation
- New: raytracing.github.io/books/RayTracingTheRestOfYourLife.html
- Add: README.md, source README.md
- Add: Markdeep page created for entire body of text
- Add: Markdeep MathJax created for formulae and equations for body of text
- Change: Text, Chapter 0 Overview has become Chapter 1, all subsequent chapters incremented
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 3, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 8, Changed calculation of `a` axis to pseudocode
- Change: Text, Chapter 8, Consistent use of spaces in code blocks


v1.123.0  (2018-08-26)
-----------------------
_Ray Tracing: The Rest of Your Life_
- New: First GitHub release.


v1.54.0  (2018-08-26)
----------------------
_Ray Tracing in One Weekend_
- New: First GitHub release.


v1.42.0  (2018-08-26)
----------------------
_Ray Tracing: The Next Week_
- New: First GitHub release.
