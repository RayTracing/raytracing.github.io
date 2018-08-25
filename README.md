Ray Tracing: The Next Week
====================================================================================================

![Ray Tracing: The Next Week](./RTNextWeek.jpg)

Getting the Book
-----------------
You can download the PDF version of the book from Eric Haine's [Real-Time Rendering] site.
Alternatively, you can purchase a Kindle version of this series from [Amazon.com]. Half of the
proceeds of these sales go to [Hack the Hood], a really neat organization.

Overview
---------
In [Ray Tracing In One Weekend], you built a simple brute force path tracer. In this installment
we’ll add textures, volumes (like fog), rectangles, instances, lights, and support for lots of
objects using a BVH. When done, you’ll have a “real” ray tracer.

A heuristic in ray tracing that many people—including me—believe, is that most optimizations
complicate the code without delivering much speedup. What I will do in this mini-book is go with the
simplest approach in each design decision I make. Check www.in1weekend.com for readings and
references to a more sophisticated approach. However, I strongly encourage you to do no premature
optimization; if it doesn’t show up high in the execution time profile, it doesn’t need optimization
until all the features are supported!

The two hardest parts of this book are the BVH and the Perlin textures. This is why the title
suggests you take a week rather than a weekend for this endeavor. But you can save those for last if
you want a weekend project. Order is not very important for the concepts presented in this book, and
without BVH and Perlin texture you will still get a Cornell Box!

Acknowledgments
----------------
Thanks to Becker for his many helpful comments on the draft and to Matthew Heimlich for spotting a
critical motion blur error. Thanks to Andrew Kensler, Thiago Ize, and Ingo Wald for advice on
ray-AABB tests. Thanks to David Hart and Grue Debry for help with a bunch of the details. Thanks to
Jean Buckley for editing.



[Amazon.com]:                 https://amazon.com/dp/B01CO7PQ8C
[Hack the Hood]:              http://www.hackthehood.org
[Ray Tracing In One Weekend]: https://github.com/petershirley/raytracinginoneweekend/
[Real-Time Rendering]:        http://www.realtimerendering.com/#books-small-table
