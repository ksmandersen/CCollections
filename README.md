# CCollections

CCollections is a general purpose collection library for the ANSI C programming language. It was insipired by the well known collection libraries for .NET runtime and Java runtime.
CCollections gives programmeres with an object-oriented background a convinient way to use collections in C.
The library provides a familiar and consistent interface to work with collections.

## Existing solutions

| Library | Consistent naming | Good documentation | Garbage collection |
| :------ | :---------------- | :----------------- | :----------------- |
| gdsl    | ✖                 | ✖                  | ✖                  |
| GLib    | ✔                 | ✔                  | ✖                  |



## Why?

* Memory management is cumbersome to deal with when you're used to the OO-world
* Collection libraries for C are rarely very well documented in the degree that most OO developers are used to.
* Most of the libraries available doesn't use consistent naming across ADT's (probably due to the lack of interfaces and classes)

## Requirements

* Consistent and familiar naming convention inspired by C# naming conventions
* Well documented collections with the kind of documentation used for .NET and Java collection libraries.
* Build-in support for garbage collection so developers need to worry about allocating memory.
* The library should be able to build with any common ANSI C compiler like gcc, clang, lcc, etc.
* Lots and lots of testing!

The collection library will include the following collection types:

* Array
* Dictionary
* HashSet
* LinkedList
* List
* Queue
* SortedDictionary
* SortedList
* SortedSet
* Stack


## Møde

Check netlib.org
Numerical recipes in c
overvejelser i fht. udvidelse af Glib med boehms relevant
tests imbefatter både performance og funktionalitet.
Brug af cache i den rigtige rækkefølge
OSX app Shark
Automatiserede tests
test cases fra c5 kap 11
arbejdsplan med rækkefølge, også i fht. ambitioner og impletering + test af data strukturer
boehms research paper - boehms hjemmeside

## Memory management

CCollections incorporates support for automatic garbage collection using Boehm's garbage collection library.
Programmers who are new to the C programming language will not need to micro-manage their memory allocations by themselves
while experienced C programmers can take full control and manage their memory manually.

## Installation

More on this later

## Usage

More on this later

## Acknowledgement

This library was started and developed as student project at [IT University of Copenhagen](http://itu.dk/).
The project was supervised by [Peter Sestoft](http://itu.dk/people/sestoft) and Hans Henrik Sørensen.

This project is greatly insipired by [The C5 Generic Collection Library for C# and CLI](http://www.itu.dk/research/c5/).

## License
CCollections is licensed under the [BSD-2-Clause License (FreeBSD)](http://opensource.org/licenses/BSD-2-Clause).

Copyright (c) 2012, [Ulrik Damm](http://github.com/ulrikdamm) and [Kristian Andersen](http://github.com/ksmandersen).
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

