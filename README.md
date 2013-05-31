scim
====

Toy game and engine in C++

Still a work in progress; not yet ready for real use.

----

building
========

This app uses various libraries to run, so in order to compile it, you must have these libraries installed on your system. A OpenGL implementation of at least version 2.1 and GLSL version 1.2 is required.

Libs needed:
- GL, for graphics rendering
- GLEW, for OpenGL extension handling; (git)
- glfw, for window creation and OpenGL context creation; (git)
- glm, for math classes
- UnitTest++, for unit testing
- Assimp, for mesh loading; (git)
- DevIL, for image loading

All external libraries are open source and are included in the 'dep' directory. If not a quick Google search will find you what you need. The headers of all the libraries are already included in the build as system header, so the only thing the compiler should complain about is linking. Those marked with (git) are added as repo submodules and are pulled in from the official repository.

The library currently only builds on Linux, but could be easily modified to work on windoze.

Confirmed build with gcc 4.7.2, gcc 4.8.0

You can import "scim.sublime_project" into Sublime Text 2. The project file specifies a build directory, "build", and Ninja as the build program.

usage
=====

To test out scim, you can simply use the included demo and edit it to test out other features.

The demo is set up to work with a server http://github.com/stnma7e/scim_serv
