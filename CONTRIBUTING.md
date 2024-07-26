Contributing To The Ray Tracing in One Weekend Series
====================================================================================================

The _Ray Tracing in One Weekend_ series is intended to be lightweight and accessible for all who
want to learn about ray tracing and related graphics topics. To that end, we welcome feedback,
proposals, and improvements.

In particular, we are now a dedicated GitHub organization. The books are now available in HTML from
https://raytracing.github.io/, so we can keep the content up-to-date with the latest corrections and
improvements.


Development Branches
---------------------
We use `release` as our release branch. _Generally, changes should never go directly to the release
branch_. All ongoing development work (and all of the latest changes) will be in the `dev-patch`,
`dev-minor`, `dev-major`, or feature branches. The appropriate target branch for any pull requests
you want to make will be determined in the associated issue first (all pull requests should have an
associated issue).


Issues
-------
The easiest way to help out is to log any issues you find in the books. Unclear passages, errors of
all kinds, even better ways to present something -- just go to the [issues page][].

1. First ensure that the issue is still outstanding (check `dev-patch`, `dev-minor` or `dev-major`
   as appropriate). Often the issue has already been addressed or no longer applies to the latest
   in-development version. Admittedly, that's a bit of a hassle, but at least step two should help
   you avoid duplicate issues.

2. **Before creating a new issue**, please review existing issues to see if someone has already
   submitted the same one. Chances are you're not the first to encounter something, so a little
   quick research can save everyone some hassle. If you have new information, please continue the
   thread in the existing issue.

3. When entering a new issue, please include all relevant information. For content issues, include
   the book or books this applies to, and specific locations that should be reviewed. Similarly for
   code: please include the file, function/class, and line number(s) if that applies.

4. Finally, _please keep issues focused on a single problem or suggestion_. If discussion prompts
   you to think of a related issue, create a separate issue for that topic and add a link back to
   the original discussion or issue (just use the "#NNN" syntax for issue/discussion/pull-request
   NNN -- GitHub will automatically make this a link).


Pull Requests
--------------
To contribute a change to the project, *please follow these steps*:

  1. [Create a new GitHub issue](https://github.com/RayTracing/raytracing.github.io/issues).

  2. Let us know if you're willing to make the fix yourself.

  3. Participate in the discussion as needed. We'll ensure that the work doesn't conflict with or
     duplicate other work planned or in progress, and decide which development branch is correct
     for the release type and release schedule.

  4. Once you've received instructions to proceed with your change, create a new feature branch (or
     fork) from the assigned development branch (usually `dev-patch`, `dev-minor`, or `dev-major`).

  5. Follow the existing code style.

  6. Ensure that the change is complete:

     - Update all relevant source code for all three books (`src/*`). Since the code is developed as
       the books proceed, you may need to update many historical code listings as well, _and this
       may require corresponding updates to the book text_.

     - Update all relevant code listings and text in all three books (`books/RayTracing*.html`).
       Follow existing style for the Markdeep source (for example, text should be wrapped to 100
       characters).

     - Provide clear and full commit descriptions: title line (50 characters max), followed by a
       blank line, and then a descriptive body with lines not exceeding 72 characters. If a commit
       is expected to completely resolve an outstanding issue, add a line "Resolves #NNN" to the
       bottom of your commit message, where NNN is the existing GitHub issue number. You may provide
       multiple such lines if applicable.

     - Include a one-line summary change at the bottom of the current development section in the
       changelog (`CHANGELOG.md`). Include a reference to the associated GitHub issue.

     - For an example of the above, see
       [issue #1262](https://github.com/RayTracing/raytracing.github.io/issues/1262) and
       [PR #1263](https://github.com/RayTracing/raytracing.github.io/pull/1263).

  7. When ready, create your pull request (PR) and request a review from "RayTracing/reviewers".

  8. Congratulate yourself for having been part of the 1% of contributors who actually read and
     followed these guidelines.

Note the code philosophy outlined in the first section of the first book. In short, the code is
intended to be clear for everyone, using simple C/C++ idioms as much as possible. We have chosen to
adopt _some_ modern conventions where we feel it makes the code more accessible to non-C++
programmers. Please follow the existing coding style and simplicity when offering your suggested
changes.

If anything above sounds daunting, note that you'll get _**massive**_ credit for actually reading
the CONTRIBUTING.md and following the process above -- so we'd be delighted to answer any questions
and guide you through the process.


Questions
----------
If you have any questions, feel free to ping me at steve@hollasch.net.



[issues page]: https://github.com/RayTracing/raytracing.github.io/issues/
