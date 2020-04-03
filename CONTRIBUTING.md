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

The latest official release can be found in the `master` branch. All ongoing development work (and
all of the latest changes) will be in the `dev-patch`, `dev-minor`, and `dev-major` branches. The
appropriate target branch for any pull requests you want to make will be determined in the
associated issue first (all PRs should have an associated issue).


Issues
-------
The easiest way to help out is to log any issues you find in the books. Unclear passages, errors of
all kinds, even better ways to present something -- just go to the [issues page][].

**Before creating a new issue**, please review existing issues to see if someone has already
submitted the same one. Odds are you're not the first to encounter something, so a little quick
research can save everyone some hassle. It's also a good idea to verify that problems still exist in
the `development` branch when creating new issues.

When entering a new issue, please include all relevant information. For content issues, include the
book or books this applies to, and specific locations that should be reviewed. Similarly for code:
please include the file, function/class, and line number(s) if that applies.


Pull Requests
--------------
To contribute a change to the project, please follow these steps:

  1. [Create a GitHub issue](https://github.com/RayTracing/raytracing.github.io/issues).

  2. Participate in the discussion as needed. We'll ensure that the work doesn't conflict with or
     duplicate other work planned or in progress, and decide which development branch is correct
     for the release type and release schedule.

  3. Create your changes in a feature branch (or fork) from the assigned development branch
     (probably `dev-patch`, `dev-minor`, `dev-major`, or `future`).

  4. Follow existing code style.

  5. When ready, create a pull request and request a review from "rt-contributors".

New to GitHub? We'll walk you through the process above. Just mention that you'd like a little
guidance in the proposal issue.


Questions
----------
If you have any questions, feel free to ping me at steve@hollasch.net.



[issues page]: https://github.com/RayTracing/raytracing.github.io/issues/
