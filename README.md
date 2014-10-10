COMP2240 Assignment 2
=====================

Author: Simon Hartcher
======================

Requirements
------------

On Windows, you need to have pthreads installed and visible to gcc. As far as I know it should work
in Cygwin without any changes.

If all else fails, it will compile and run out of the box on jumpgate or compseng. The only thing was
that I noticed some discrepancies with question 4 on linux that I was unable to rectify.

Building And Running
--------------------

You can build with make. It will generate 4 (four) binaries (q1, q2, q3 and q4). You run each with arguments
for north and south farmers. Eg to run q3 with [N=3, S=4] you would run ./q3 3 4

[![Build Status](https://travis-ci.org/deevus/comp2240-assign2.svg?branch=master)](https://travis-ci.org/deevus/comp2240-assign2)