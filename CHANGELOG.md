Change Log
================================================================================

v2.0.0 (In Progress)
---------------------
Common
- Add: Created single monolithic raytracing.github.io repo
- Change: Deprecated existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ repos
- Change: Moved existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ content to io repo
- Add: CHANGELOG.md
- Add: CONTRIBUTING.md
- Add: COPYING.txt
- Add: README.md
- Change: License change to CC0 in COPYING.txt
- Add: Markdeep documents created for all three 
- Change: Replaced drand48() with portable random number generation
- Add: raytracing.github.io links to all the three books
- Change: Web links have been changed to new locations
- Add: Links to Kindle version of the books
- Add: Syntax coloring for highlighting of text in source blocks
- Add: CSS for images
- Add: CSS for body of the text
- Add: CSS for code blocks
- Add: CSS for the Print variant of the books

_Ray Tracing In One Weekend_
- Add: README.md
- Add: Source README.md
- Add: Markdeep page created for entire body of text
- Add: Markdeep MathJax created for formulae and equations for body of text
- Add: raytracing.github.io/books/RayTracingInOneWeekend.html
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 2, Consistent use of spaces in code blocks
- Change: Text, Chapter 2, Reordered `vec3` class functions to + - * /
- Change: Text, Chapter 2, unbolded unit_vector
- Change: Text, Chapter 3, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 3, Remove `*world` and `depth` parameters from `color` function signature
- Change: Text, Chapter 5, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 5, Consistent use of spaces in code blocks
- Change: Text, Chapter 5, Put `hit_record` and `{` on the same line
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 6, Add `#include "random.h"` in code blocks
- Change: Text, Chapter 7, Remove `depth` parameter from `color` function signature
- Change: Text, Chapter 8, Consistent use of spaces in code blocks
- Change: Text, Chapter 8, Put function signatures and `{` on the same line
- Change: Text, Chapter 9, Consistent use of spaces in code blocks
- Change: Text, Chapter 9, Put function signatures and `{` on the same line
- Change: Text, Chapter 9, Changed contents of `List[0]` to match original text
- Change: Text, Chapter 10, Consistent use of spaces in code blocks
- Change: Text, Chapter 10, Add curly braces for `if (refract)` statement
- Change: Text, Chapter 10, Remove `0.0` from metal instantiation
- Change: Text, Chapter 11, Change `lookatfrom` to `lookfrom`
- Change: Text, Chapter 12, Put function signatures and `{` on the same line


_Ray Tracing: The Next Week_
- Add: README.md
- Add: Source README.md
- Add: Markdeep page created for entire body of text
- Add: Markdeep MathJax created for formulae and equations for body of text
- Add: raytracing.github.io/books/RayTracingTheNextWeek.html
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Consistent use of spaces in code blocks
- Change: Text, Chapter 2, Rewrote `Camera` constructors parameters to match _In One Weekend_
- Change: Text, Chapter 3, Consistent use of spaces in code blocks
- Change: Text, Chapter 4, Consistent use of spaces in code blocks
- Change: Text, Chapter 4, Changed open brace to curly in `constant_texture` constructor
- Change: Text, Chapter 4, Changed open brace to curly at `const (`
- Change: Text, Chapter 4, Added `;` to `List[0]` and `List[1]`
- Change: Text, Chapter 5, Consistent use of spaces in code blocks
- Change: Text, Chapter 5, added "texture" to "We can use that texture on some spheres"
- Change: Text, Chapter 5, Changed open brace to curly in `two_perlin_sphere` signature
- Change: Text, Chapter 5, Changed `Z` to `2` in `trilinear_interp` signature
- Change: Text, Chapter 5, Removed `;` from `pexm_z` index
- Change: Text, Chapter 7, Consistent use of spaces in code blocks
- Change: Text, Chapter 7, "This is yz and xz" changed to "This is xz and yz"
- Change: Text, Chapter 7, Changed `cornell_box` hittable array size to 5
- Change: Text, Chapter 8, Changed "And the changes to Cornell is" to "... Cornell are"
- Change: Text, Chapter 9, Changed short if statements to two lines for Consistency
- Change: Text, Chapter 10, Consistent use of spaces in code blocks
- Change: Code and Text, Chapter 8, cleaned up implementation of `constant_medium::hit`
- Change: Code and Text, Chapter 8, Rewrote debug functionality in `constant_medium::hit`


_Ray Tracing: The Rest Of Your Life_
- Add: README.md
- Add: Source README.md
- Add: Markdeep page created for entire body of text
- Add: Markdeep MathJax created for formulae and equations for body of text
- Add: raytracing.github.io/books/RayTracingTheRestOfYourLife.html
- Fix: Text, Chapter order starting from chapter 2
- Fix: Text, Renamed figures and images to match new chapter numbering
- Fix: Text, Chapter 2, The `lambertian` class definition now uses `vec3` instead of `texture`s.
- Change: Text, Syntax highlighting of source modifications
- Change: Text, Chapter 2, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 2, Changed `i < NX` to `i < N`
- Change: Text, Chapter 3, Reorder include files in code blocks to match src conventions
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 6, Remove `flip_normals` from code block
- Change: Text, Chapter 6, Consistent use of spaces in code blocks
- Change: Text, Chapter 6, Change `hrec` to `rec`
- Change: Text, Chapter 8, Changed calculation of `a` axis to pseudocode
- Change: Text, Chapter 8, Consistent use of spaces in code blocks
- Fix: Code and Text, Chapter 6, removal of factor of 2 to `random_cosine_direction` calculation
- Fix: Text, Chapter 4, Rewrote formula for "Color" to "Color = A * color(direction"




v1.123.0  (2018-08-26)
-----------------------
_Ray Tracing: The Rest Of Your Life_
- Add: First GitHub release.


v1.54.0  (2018-08-26)
----------------------
_Ray Tracing In One Weekend_
- Add: First GitHub release.


v1.42.0  (2018-08-26)
----------------------
_Ray Tracing: The Next Week_
- Add: First GitHub release.


# TODO:
- [ ] Go through closed (and open) issues
- [ ] Go through repo contents
- [ ] Check for bug that I found, and changed for clarity
- [ ] Check changes against original text
- [ ] Formatting changes
- [ ] Fix line width
- [ ] git push

# Comments:
- feel free to condense/elaborate/combine some of the change notes
- Lots of the codeblock changes can probably be combined at the text level
- Formatting comments are _encouraged_
- It's hard to tell which sanity changes were from transcription mistakes vs original errors
- from code_block sanity check _InOneWeekend_ has chapters 8,9,10,11 incorrectly labelled

# Issues
- None of the _Sanity pass for Code Blocks_ changes ported to the src
- if (refract) in chapter 10 of _InOneWeekend_ needs curly braces
- In chapter 7 of _RestOfYourLife_ z calculation is different 