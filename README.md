# AC-Utils

AC-Utils is a public-domain library designed to reduce duplicate code
spread out across projects.

## Building

You'll need a C compiler such as GCC (included in MinGW/Mingw-w64/Cygwin).
If you're using a different compiler such as Clang you may need to modify
the `Makefile` located in the root directory.

To build, simply run:  
`make`

## Instructions

In order to use AC-Utils within your own project, you'll need to include
all of the header files located within `inc`. You'll also need to link
with `libacutils.a`, which is usually inside of a `lib` folder. You can
then link by using a command akin to the example provided:  
`gcc src/main.c -o example -Llib -lacutils`

## LICENSE

This project is released under the conditions of the Unlicense, making it
a public-domain library. For more information, visit the following link:
https://unlicense.org/.