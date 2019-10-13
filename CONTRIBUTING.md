Contributing To The Ray Tracing in One Weekend Series
====================================================================================================

The _Ray Tracing in One Weekend_ series is intended to be lightweight and accessible for all who
want to learn about ray tracing and related graphics topics. To that end, we welcome feedback,
proposals, and improvements.

In particular, we are now a dedicated GitHub organization. The books are now available in HTML from
https://raytracing.github.io/, so we can keep the content up-to-date with the latest corrections and
improvements.


Repository Organization
------------------------
This repository has the following organization

```bash
raytracing.github.io/      # Repository root
    books/                 # Book content
    images/                # All figures, renderings and other images used throughout the project
    src/                   # Source code
        common/            # Source code that is common to two or more books
        InOneWeekend/      # The final form of source code for Ray Tracing in One Weekend
        TheNextWeek/       # The final form of source code for Ray Tracing: The Next Week
        TheRestOfYourLife/ # The final form of source code for Ray Tracing: The Rest of Your Life
    style/                 # CSS for books and web site
```


Issues
-------
The easiest way to help out is to log any issues you find in the books. Unclear passages, errors of
all kinds, even better ways to present something -- just go to the [issues page][].

**Before creating a new issue**, please review existing issues to see if someone has already
submitted the same one. Odds are you're not the first to encounter something, so a little quick
research can save everyone some hassle.

When entering a new issue, please include all relevant information. For content issues, include the
book or books this applies to, and specific locations that should be reviewed. Similarly for code:
please include the file, function/class, and line number(s) if that applies.


Pull Requests
--------------
If you have a change that you think would be worthwhile, start with creating an issue, and indicate
whether you're willing to submit the change yourself. We'll let you know if it sounds like a good
idea, whether it duplicates another issue or work already planned. If you get the green light,
create your own fork of the project, make the changes, and then create a standard GitHub pull
request for us to review.

New to GitHub? We'll walk you through the process above. Just mention that you'd like a little
guidance in the proposal issue.


Questions
----------
If you have any questions, feel free to ping me at steve@hollasch.net.



[issues page]: https://github.com/RayTracing/raytracing.github.io/issues/
