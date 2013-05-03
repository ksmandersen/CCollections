# CCollections

CCollections is a general purpose collection library for the ANSI C programming language. It was insipired by the well known collection libraries for .NET runtime and Java runtime.
CCollections gives programmeres with an object-oriented background a convinient way to use various data structures in C.
The library provides a familiar and consistent interface to work with collections.

Here is an example of how easy it use to the library:

    int countchar (char list[]) {
      int i, count = 0;
      for (i = 0; list[i] != '\0'; i++)
      count++;
      return (count);
    }

    cc_linked_list *keys = cc_linked_list_new_with_values(cc_type_string, "Apples", "Bananas", "Oranges", "Pineapples", CC_END);
    cc_array_list *values = cc_array_list_new();

    cc_enumerator *e = cc_linked_list_get_enumerator(keys);
    while(cc_enumerator_move_next(e)) {
      cc_object *fruit = cc_enumerator_current(e);
      int count = countchar(cc_object_string_value(fruit));
      cc_array_list_add_last(values, cc_object_with_int(count));
    }

    cc_dictionary *fruits = cc_dictionary_new_with_enumerators(cc_linked_list_get_enumerator(keys), cc_array_list_get_enumerator(values));

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

## Hashing

Til at starte med implementerer vi blot en simpel hashing metode til at test vores collections med. Senere kan vi
kigge på at bruge eksisterende biblioteker med Perfect Hashing. Der er to meget udbredte:

* [CMPH - C Minimal Perfect Hashing Library](http://cmph.sourceforge.net/)
* [gperf - GNU Perfect hashing](http://www.gnu.org/software/gperf/#TOCintroduction)

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

