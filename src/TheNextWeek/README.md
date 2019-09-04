Ray Tracing: The Next Week - Source
====================================================================================================

Content
--------
This folder ([TheNextWeek][]) contains the finished code of the [_Ray Tracing: The Next Week_][] book.

Every chapter of [_Ray Tracing: The Next Week_][] acts as it's own mini tutorial, and each chapter is largely independent of other chapters. Every chapter ends with an example render, and in the source, the [main.cc][] contains a render function specific to each chapter. The source presented here represents the simplest superset of the code from all chapters.

Intent
-------
This folder is not meant to act as it's own tutorial. The source presented here is provided so that you can compare your work when going along with the book. We strongly recommend reading and following along with the book if you want to understand the source.

Programming Language
---------------------
This book is written in c++ with some modern features of c++11. The code as written is designed to be readable by the largest collection of potential programmers. The code is not meant to illustrate idealized c++ code.

Building
---------
No mechanism for building is included with this project.

The _Ray Tracing in One Weekend_ series has a long history of being written in other programming languages ([Implementations in Other Languages][]) and across all three primary operating systems.

It is necessary for you to create your own build tooling. However, the source begins as a single main file and builds to only a small collection of additional header files.

The c++ code as written should compile across all three platforms (Win, OSX, Linux).

Corrections & Contributions
----------------------------
If you spot errors, have suggested corrections, or would like to help out with the project, please
review the [CONTRIBUTING][] document for the most effective way to proceed.



[TheNextWeek]:                         https://github.com/RayTracing/raytracing.github.io/tree/master/src/TheNextWeek
[_Ray Tracing: The Next Week_]:         https://github.com/RayTracing/raytracing.github.io/tree/master/books/RayTracingTheNextWeek.html
[main.cc]:                              https://github.com/RayTracing/raytracing.github.io/tree/master/src/TheNextWeek/main.cc
[Implementations in Other Languages]:   https://github.com/RayTracing/InOneWeekend/wiki/Implementations-in-Other-Languages
[CONTRIBUTING]:                         ../../CONTRIBUTING.md