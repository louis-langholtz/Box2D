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
|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=iosfoo)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=dev)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=macosxfoo)](https://travis-ci.org/louis-langholtz/Box2D)|[![Build Status](https://travis-ci.org/louis-langholtz/Box2D.svg?branch=win32foo)](https://travis-ci.org/louis-langholtz/Box2D)|

## Overview

General influences on this fork are:
- [C++14](https://en.wikipedia.org/wiki/C%2B%2B14);
- [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md);
- [Unit testing](https://en.wikipedia.org/wiki/Unit_testing);

**NOTE**: These sources make heavy use of the standard C++ library [`assert`](http://en.cppreference.com/w/cpp/error/assert) macro to confirm code correctness.
As such, this library *must* be compiled with the `NDEBUG` preprocessor macro enabled
to see any kind of performance.

## Changes

Here's a run-down of some of the changes this fork introduces:
- Exported symbols are now within the library namespace of `box2d` and are no longer prefaced by `b2`.
- Mutable global variables in the library have been removed or replaced with runtime-time parameters.
- Preprocessor defines, except those used for include guards, have been replaced with C++ solutions or removed from the API.
- [Rounded and modified corner collisions](Box2D/Documentation/CollisionHandlng.md).
- *Capsule* shapes (using `EdgeShape` or 2-vertex `PolygonShape` instances).
- Support for up to 254-vertex polygons.
- More stable polygon stacking.
- Shared shape ownership, with friction, density, and restitution moved into them (from Fixture class) for reduced memory usage.
- Support for C++11's range-based loops and constant expressions.
- Unit tested via [Google Test](https://github.com/google/googletest/tree/aa148eb2b7f70ede0eb10de34b6254826bfb34f4) and [over 400 tests](https://github.com/louis-langholtz/Box2D/tree/dev/Box2D/UnitTests).
- Continuous integration (CI) building and unit testing of repository updates
  for the Linux platform.
- Compile-time support for zero-runtime strongly-typed physical units (using an interface to [`constexpr`-enhanced boost units](https://github.com/louis-langholtz/units)). For details on how to enable this, see [Documentation/PhysicalUnits.md](Box2D/Documentation/PhysicalUnits.md).
- Compile-time support for `double` and `long double` floating-point types, and 32-bit and 64-bit fixed-point types (in addition to `float`).
- Fully per-step run-time configurable (via [`StepConf`](https://github.com/louis-langholtz/Box2D/blob/dev/Box2D/Box2D/Dynamics/StepConf.hpp)).
- In-depth per-step return value statistics (via [`StepStats`](https://github.com/louis-langholtz/Box2D/blob/dev/Box2D/Box2D/Dynamics/StepStats.hpp)).
- Increased construction-time configurability of world instances (via [`World::Def`](https://github.com/louis-langholtz/Box2D/blob/dev/Box2D/Box2D/Dynamics/World.hpp#L107)).
- Various methods have been rewritten to be [non-member non-friend functions](http://www.drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197).
- Various functions and procedures have been rewritten to be ["pure functions"](https://en.wikipedia.org/wiki/Pure_function).
- Testbed enhancements: per-step configurability, per-step statistics, ability to manipulate bodies while paused, and more.
- Testbed test additions: Half Pipe, iforce2d's Topdown Car, Orbiter, Newton's Cradle, and Spinning Circles.

## The Application Programming Interface

For *doxygen* generated documentation for the Application Programming Interface, see: [API](API/index.html).
