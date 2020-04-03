Ray Tracing in One Weekend Book Series
====================================================================================================

| ![RT in One Weekend][cover1] | ![RT The Next Week][cover2] | ![RT The Rest of Your Life][cover3] |
|:----------------------------:|:---------------------------:|:-----------------------------------:|
|   [In One Weekend][book1]    |   [The Next Week][book2]    |   [The Rest of Your Life][book3]    |


Getting the Books
------------------
The _Ray Tracing in One Weekend_ series of books are now available to the public for free directly
from the web:

  - [Ray Tracing in One Weekend][web1]
  - [Ray Tracing: The Next Week][web2]
  - [Ray Tracing: The Rest of Your Life][web3]

These books have been formatted for both screen and print. For printed copies, or to create PDF
versions, use the print function in your browser.


News
-----
2020-March-23 — v3.0.0 is out! Following the major v2.0.0 release, we finally had the chance to dig
into some of the larger changes we'd been wanting to make for a long time. This is a large change
across the books and entire source code. The new source code now builds using CMake, for most
platforms and build systems. We've refactored a good deal of the project source, cleaning things up,
refactoring, adding new functionality where it made sense, and generally trying to simplify the code
with the goal of making it easier to understand and modify. Finally, this release includes a number
of changes to areas of the book that have given readers difficulties. Enjoy!


Branches
---------
The `master` branch contains the code at latest release. All ongoing development, with all of the
latest changes, can be found in the `dev-patch`, `dev-minor`, and `dev-major` branches.


Downloading The Source Code
----------------------------
The [GitHub home][] for this project contains all source and documentation associated with the _Ray
Tracing in One Weekend_ series of books. To clone or download the source code, see the green "Clone
or download" button in the upper right of the project home page.


Building and Running
---------------------
Copies of source are provided for you to check your work and compare against. If you wish to build
the provided source, the project uses CMake. At the root of the project directory, run the following
commands to build the debug version of every executable:

    $ cmake -B build
    $ cmake --build build

You can specify the target with the `--target <program>` option, where the program may be
`inOneWeekend`, `theNextWeek`, `theRestOfYourLife`, or any of the demonstration programs. By default
(with no `--target` option), CMake will build all targets.

On Windows, you can build either `debug` (the default) or `release` (the optimized version). To
specify this, use the `--config <debug|release>` option.

### CMake GUI on Windows
You may choose to use the CMake GUI when building on windows.

1. Open CMake GUI on Windows
2. For "Where is the source code:", set to location of the copied directory. For example,
   `C:\Users\Peter\raytracing.github.io`.
3. Add the folder "build" within the location of the copied directory. For example,
   `C:\Users\Peter\raytracing.github.io\build`.
4. For "Where to build the binaries", set this to the newly-created build directory.
5. Click "Configure".
6. For "Specify the generator for this project", set this to your version of Visual Studio.
7. Click "Done".
8. Click "Configure" again.
9. Click "Generate".
10. In File Explorer, navigate to build directory and double click the newly-created `.sln` project.
11. Build in Visual Studio.

If the project is succesfully cloned and built, you can then use the native terminal of your
operating system to simply print the image to file.

### Running The Programs

On Linux or OSX, from the terminal, run like this:

    $ build/inOneWeekend > image.ppm

On Windows, run like this:

    build\debug\inOneWeekend > image.ppm

or, run the optimized version (if you've built with `--config release`):

    build\release\inOneWeekend > image.ppm

The generated PPM file can be viewed directly as a regular computer image, if your operating system
supports this image type. If your system doesn't handle PPM files, then you should be able to find
PPM file viewers online. We like [ImageMagick][].


Corrections & Contributions
----------------------------
If you spot errors, have suggested corrections, or would like to help out with the project, please
review the [CONTRIBUTING][] document for the most effective way to proceed.



[book1]:                    books/RayTracingInOneWeekend.html
[book2]:                    books/RayTracingTheNextWeek.html
[book3]:                    books/RayTracingTheRestOfYourLife.html
[CONTRIBUTING]:             ./CONTRIBUTING.md
[cover1]:                   images/RTOneWeekend-small.jpg
[cover2]:                   images/RTNextWeek-small.jpg
[cover3]:                   images/RTRestOfYourLife-small.jpg
[GitHub home]:              https://github.com/RayTracing/raytracing.github.io/
[ImageMagick]:              https://imagemagick.org/
[web1]:                     https://raytracing.github.io/books/RayTracingInOneWeekend.html
[web2]:                     https://raytracing.github.io/books/RayTracingTheNextWeek.html
[web3]:                     https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html
