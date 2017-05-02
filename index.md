# Box2D

Hello and welcome to the online documentation for [my fork
of the Box2D physics engine](https://github.com/louis-langholtz/Box2D)
that was originally written by Erin Catto.

Years ago I worked on developing a video game that involved physical
interactions such as collisions between entities. Not wanting to write
a whole bunch of code for simulating physics if a library was already
out there and ready to use, I found the Box2D library by Erin Catto
and **WOW** was I psyched. It took me a little getting used to but in the
end I was able to get it to do everything I needed to do.

My warmest thanks to Erin for developing Box2D and making it available
for us to use.

Now, years later, I returned to Box2D for another game I started work on
and instead fell in love with changing the Box2D library. At first this was
just so I could use new features in C++14, but my work on the library grew
to include many other changes.

What you'll find here, is online documentation I've written to explain the
changes that I've made and hopefully excite people to try this fork out.

Sincerely,

[Louis Langholtz](https://github.com/louis-langholtz/)

## Current Continuous Integration Status

|iOS|Linux|Mac OS X|Windows|
|---|-----|--------|-------|
|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=iosfoo)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=dev)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=macosxfoo)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build status](https://ci.appveyor.com/api/projects/status/q4q1y1g6ckqqpiev/branch/dev?svg=true)](https://ci.appveyor.com/project/louis-langholtz/box2d/branch/dev)|

## Overview

General influences on this fork are:
- [C++14](https://en.wikipedia.org/wiki/C%2B%2B14);
- [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md);
- [Unit testing](https://en.wikipedia.org/wiki/Unit_testing);

**NOTE**: These sources make heavy use of the standard C++ library [`assert`](http://en.cppreference.com/w/cpp/error/assert) macro to confirm code correctness.
As such, this library *must* be compiled with the `NDEBUG` preprocessor macro enabled
to see any kind of performance.

## Additional Resources

- [Changes Document](https://github.com/louis-langholtz/Box2D/blob/dev/Changes.md):
  provides a run-down of changes that have been introduced.
- [Building Document](https://github.com/louis-langholtz/Box2D/blob/dev/Box2D/Building.txt):
  information on how to build this project and run the testbed.
- [API Pages](http://louis-langholtz.github.io/Box2D/API/index.html): documentation on the Application Programming Interface (API).
- [Issues Web Interface](https://github.com/louis-langholtz/Box2D/issues):
  for questions, bugs reports, or suggestions associated with this project.
