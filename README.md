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

For printed copies, or to create PDF versions, use the print function in your browser. These books
have been properly formatted for print versions as well.


Getting and Building the Source
--------------------
The [github page][git repo] for this project contains all source and documentation associated
with the _Ray Tracing in One Weekend_ series of books.

A local copy of the project can be created on your machine through git bash:
```
$ git clone https://github.com/RayTracing/raytracing.github.io
```
A local copy can also be obtained by pointing a git gui client to the link:
```
https://github.com/RayTracing/raytracing.github.io
``` 

Copies of source are provided for you to check your work and compare against.
If you wish to build the provided source, the process uses CMake.


If on Linux or OSX, from the terminal:
```
$ git clone https://github.com/RayTracing/raytracing.github.io
$ cd raytracing.github.io
$ mkdir build
$ cd build
$ cmake ..
$ make
```

If on Windows, building is recommended on CMake Gui with Visual Studio:
```
1. Open CMake Gui on Windows
2. Under "Where is the source code:" set to location of the copied directory
     e.g. C:\Users\Peter\raytracing.github.io
3. Add Folder "build" within the location of the copied directory
     e.g. C:\Users\Peter\raytracing.github.io\build
4. Under "Where to build the binaries" set to newly created build directory
5. Click "Configure"
6. Under "Specify the generator for this project" set to your version of Visual Studio
7. Click "Done"
8. Click "Configure" again
9. Click "Generate"
10. In File Explorer, navigate to build directory and double-click the newly created .sln project
11. Build in Visual Studio
```

If the project is succesfully cloned and built, you can then use the native terminal of your
operating system to simply print the image to file.

If on Linux or OSX, from the terminal:
```
$ ./inOneWeekend > weekendOutput.ppm
```

If on Windows, open the command line, cmd.exe:
```
C:\Users\Peter\raytracing.github.io\build\inOneWeekend.exe > weekendOutput.ppm
```

This PPM file can then be viewed as a regular computer image. Most operating systems come natively
with a PPM viewer included. If your operating system has difficulty knowing what to do with the
output, then PPM file viewers can be easily found online.


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
[git repo]:                 https://github.com/RayTracing/raytracing.github.io/
[releases]:                 https://github.com/RayTracing/raytracing.github.io/releases/
[submit issues via GitHub]: https://github.com/raytracing/raytracing.github.io/issues/
[web1]:                     https://raytracing.github.io/books/RayTracingInOneWeekend.html
[web2]:                     https://raytracing.github.io/books/RayTracingTheNextWeek.html
[web3]:                     https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html
