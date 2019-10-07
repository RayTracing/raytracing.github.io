Ray Tracing in One Weekend
====================================================================================================

![Ray Tracing in One Weekend](../images/RTOneWeekend.jpg)


Getting the Book
-----------------
The _Ray Tracing in One Weekend_ series of books are now available to the public for free in PDF
form, along with the accompanying source code.

You can view the book at https://raytracing.github.io/books/RayTracingInOneWeekend.html. If you
would like a printed or PDF version, print it directly from your browser (it has been styled to
support a printed layout).


Overview
---------
I’ve taught many graphics classes over the years. Often I do them in ray tracing, because you
are forced to write all the code but you can still get cool images with no API. I decided to adapt
my course notes into a how-to, to get you to a cool program as quickly as possible. It will not be
a full-featured ray tracer, but it does have the indirect lighting which has made ray tracing a
staple in movies. Follow these steps, and the architecture of the ray tracer you produce will be
good for extending to a more extensive ray tracer if you get excited and want to pursue that.

When somebody says “ray tracing” it could mean many things. What I am going to describe is
technically a path tracer, and a fairly general one. While the code will be pretty simple (let the
computer do the work!) I think you’ll be very happy with the images you can make.

I’ll take you through writing a ray tracer in the order I do it, along with some debugging tips. By
the end, you will have a ray tracer that produces some great images. You should be able to do
this in a weekend. If you take longer, don’t worry about it. I use C++ as the driving language,
but you don’t need to. However, I suggest you do, because it’s fast, portable, and most
production movie and video game renderers are written in C++. Note that I avoid most “modern
features” of C++, but inheritance and operator overloading are too useful for ray tracers to pass
on. I do not provide the code online, but the code is real and I show all of it except for a few
straightforward operators in the vec3 class. I am a big believer in typing in code to learn it, but
when code is available I use it, so I only practice what I preach when the code is not available.
So don’t ask!

I have left that last part in because it is funny what a 180 I have done. Several readers ended
up with subtle errors that were helped when we compared code. So please do type in the
code, but if you want to look at mine, here it is.


Corrections & Contributions
----------------------------
If you spot errors, have suggested corrections, or would like to help out with the project, please
review the [CONTRIBUTING][] document for the most effective way to proceed.



[CONTRIBUTING]:             ../CONTRIBUTING.md
[releases]:                 https://github.com/raytracing/raytracing.github.io/releases/
[Hack the Hood]:            https://hackthehood.org/
[Real-Time Rendering]:      https://realtimerendering.com/#books-small-table
[submit issues via GitHub]: https://github.com/raytracing/raytracing.github.io/issues/
