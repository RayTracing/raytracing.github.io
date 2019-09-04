Ray Tracing: The Next Week - Source
====================================================================================================

Content
--------
This folder contains the finished code for _Ray Tracing: The Next Week_ ([local][] / [online][]).

Every chapter of the book acts as its own mini tutorial, and each chapter is largely independent of
other chapters. Every chapter ends with an example render, and in the source, [main.cc][] contains a
render function specific to each chapter. The source presented here represents the simplest superset
of the code from all chapters.


Intent
-------
This folder is not meant to act as its own tutorial. The source presented here is provided so you
can compare your work when progressing through the book. We strongly recommend reading and following
along with the book to understand the source.


Programming Language
---------------------
This book is written in C++, and uses some modern features of C++11. The language and features were
chosen to be broadly understood by the largest collection of programmers. It is not meant to
represent ideal C++ code.


Building
---------
As the source is intended for illustration & comparison only, it does not include any mechanism for
building a final program. As far as possible, the code is privately tested on multiple platforms to
ensure that it is generally usable on any OS (primarily Windows, OSX, and Linux), compiler, or build
environment.

It is therefore necessary for you to create your own build tooling. However, the source begins as a
single main file, and uses only a small collection of additional header files.

The _Ray Tracing in One Weekend_ series has a long history of implementations in other programming
languages (see [_Implementations in Other Languages_][implementations]), and across all three
primary operating systems. Feel free to add your own implementation to the list!


Corrections & Contributions
----------------------------
If you spot errors, have suggested corrections, or would like to help out with the project, please
review the [CONTRIBUTING][] guidelines for the most effective way to proceed.



[online]:          https://raytracing.github.com/books/RayTracingTheNextWeek.html
[local]:           ../../books/RayTracingTheNextWeek.html
[main.cc]:         ./main.cc
[implementations]: https://github.com/RayTracing/raytracing.github.io/wiki/Implementations-in-Other-Languages
[CONTRIBUTING]:    ../../CONTRIBUTING.md
