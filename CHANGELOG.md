Change Log
================================================================================

v2.0.0 (In Progress)
-------------------
### Major Changes
  - Created single monolithic raytracing.github.io repo
    - Moved existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ content to io repo
    - Deprecated existing _InOneWeekend_, _TheNextWeek_, _TheRestOfYourLife_ repos
  - Fixed chapter order in _Ray Tracing: The Rest Of Your Life_
    - Typo in chapter numbering lead to two chapter 2s
    - All proceeding chapters were off by one
    - Corrected second instance of chapter 2 as chapter 3
    - Proceeding chapters were incremented as fix

### Minor Changes
  - Added CHANGELOG.md
  - Added CONTRIBUTING.md
  - Added COPYING.txt
    - Created COPYING.md
    - Changed license to CC0 in COPYING.md
    - Renamed COPYING.md to COPYING.txt

### Patches
  - Removed bug in Chapter 2 of _Ray Tracing: The Rest Of Your life_
    - The `lambertian` class definition in Chapter 2 previously used `texture`s
    - This has been changed to `vec3`


v1.123.0  (2018-08-26)
-----------------------
### Minor Changes
  - First GitHub release of _Ray Tracing: The Rest Of Your Life_, bundled with source code.


v1.54.0  (2018-08-26)
----------------------
### Minor Changes
  - First GitHub release of _Ray Tracing In One Weekend_, bundled with source code.


v1.42.0  (2018-08-26)
----------------------
### Minor Changes
  - First GitHub release of _Ray Tracing: The Next Week_, bundled with source code.

