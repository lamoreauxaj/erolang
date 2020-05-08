---
sidebar: auto
---

# Presentation

Check out the project [here](https://github.com/Lamoreauxaj/pa). Give us stars please <3.

## What did we make?

We wrote a compiler for a self-made language called Ero. Ero is a functional
scripting language intended to describe and process Euclidean constructions in
two or three dimensions. Ero is inspired by *Elements*, an ancient geometry
textbook by Euclid of Alexandria. As a result, Ero does not focus on algebra or
arithmetic. Rather, it relies on geometry as its main method of computation, even
though real arithmetic is still supported. Ero is **Turing complete** (able to compute
anything which is computable) and **Euclidean complete** (able to construct any
Euclidean construction). Ero can also be used to create non-Euclidean constructions
(such as angle trisection and squaring the circle).

### Data Types

The language's main built-in data types are the following:
- Point
- Line
- Ray (unimplemented)
- Segment (unimplemented)
- Sphere
- Circle
- Arc (unimplemented)
- Empty
- Space
- Real (numeric data type)
- Bool
- Undefined
- Tuple (partially implemented)
- Construction (functions)

### Postulates

The language has a set of postulates which can be used to implement all other core
functions within the language. These consist of
- `plane(Point alpha, Point beta, Point gamma)`

    Returns the unique plane constructed
    from the three points `alpha`, `beta`, and `gamma`.

- `sphere(Point center, Point point)`

    Returns the unique sphere with `center` as its center such that
    `point` is a point on the sphere.

- `point(Real x, Real y, Real z)`

    Returns the point with the Cartesian coordinates (`x`, `y`, `z`).

- `ray(Point endpoint, Point point)`

    Returns the unique ray with endpoint `endpoint` such that
    `point` is a point on the ray.

- `arc(Point start, Point point, Point end)`

    Returns the unique arc with endpoints `start` and `end` such that `point`
    is a point on the arc.

- `intersections(Figure *omega)` (this represents variable number of arguments)

    Returns a tuple of figures whose union is the intersection of all figures in `omega`.

- `point_on(Figure alpha)`

    Returns a "random" point on `alpha`.

- `endpoints(Point alpha)`

    Returns a tuple of all the endpoints of `alpha`.

- `distance(Point alpha, Point beta)`

    Returns the Euclidean distance between `alpha` and `beta`.

These set of postulates are enough to create any Euclidean construction and although
they may seem limited they are sufficient as primitives to allow the creation of
more complex constructions.

Furthermore the language contains standard operators and constructs you would expect
including most arithmetic operators, while loops, if statements, etc.

## Features

Here we will focus on features that we actually implemented along with sample code since
we did not get to implement every thing that was described above. And yes you may
run the sample code and in fact you can even edit the code.

No guarantees that if you modify the code, you won't find bugs ;).

### Variables + Assignment

The following code demonstrates that our language has basic constructs
for printing, assigning to variables, and doing addition.
<Demo :code="'a = b = 1.0 + 2.0 + 1.2\nb = b + 0.5\nwrite(a + b)\nwrite(a + 1.0)'"/>

### If Statements

We implemented if statements in our language. There is also the `is` operator
which compares two real values to be within epsilon. Currently this is the only
operator that returns a boolean, but implementing the other comparison
operators is relatively straightforward. Furthermore there are also global constants
`true` and `false` which can be used.
<Demo :code="'a = 1.0\nb = true\nif (a is 1.0) {\n    write(1.0)\n}\nif (b) {\n    if (false) {\n        write(2.0)\n    }\n    write(3.0)\n}'"/>

### Local Variables

We implemented local variables. We did this through first preprocessing all identifiers
in the language and mapping them to a position in memory. We differentiated between
global variables and local variables. Global variables live in the data segment of our
compiled programs, while local variables live on the stack (except for
captured variables). It's not easy to really show that `b` is a local variable in this
case, but you'll have to trust us.
<Demo :code="'a = 1.0\nif (a is 1.0) {\n    b = 2.0\n    write(a)\n    write(b)\n}'"/>

### While Loops

Of course our language needed while loops. Pretty self-explanatory.
<Demo :code="'a = 1.0\nwhile (a is 1.0) {\n    b = b + 0.5\n    write(b)\n    if (b is 3.0) {\n        a = 0.0\n        write(4.2)\n    }\n}'"/>

### Constructions

Constructions are the main abstraction in Ero allowing one to compose primitive
postulates to create more interesting diagrams. Our constructions are limited currently
since we only allow a small number of arguments and can only return a single value. The
main reason for the single return value is that we have not implemented tuples yet
and this is intended to return a tuple of return values.
<Demo :code="'add = construction (a, b) -> (z) {\n    z = a + b\n}\n\na = 1.0\nz = 3.0\nwrite(add(a + z))'"/>

### Geometric Postulates

We have bindings to all the core geometric functions that we implemented. This is the
same way that we implemented write as well. These functions are actually written in C++
compiled to an object file and linked with our compiled assembly since due to the
complexity of the operations, these were unreasonable for us to implement in assembly
alone.
<Demo :code="'a = point(0, 0, 0)\nb = point(1, 0, 0)\nc = point(0, 1, 0)\nd = plane(a, b, c)\ne = sphere(a, b)\nf = intersection(d, e)\nwrite(a)\nwrite(b)\nwrite(c)\nwrite(d)\nwrite(e)\nwrite(f)'" :render="false"/>

### Rendering

Now who would want to put effort into designing beautiful diagrams if you couldn't
then render them. Well we did exactly that. We implemented a basic rendering system
using a library called THREE.js which takes the stdout of the program and renders it.
<Demo :code="'a = point(0, 0, 0)\nb = point(1, 0, 0)\nc = point(0, 1, 0)\nd = plane(a, b, c)\ne = sphere(a, b)\nf = intersection(d, e)\nwrite(f)'"/>

### Rendering is 3D?

The rendering is actually 3D. For example if we tilt the circle, you'll notice that
the perspective will change accordingly.
<Demo :code="'a = point(0, 0, 1)\nb = point(1, 0, 0)\nc = point(0, 1, 2)\nd = plane(a, b, c)\ne = sphere(a, b)\nf = intersection(d, e)\nwrite(f)'"/>

### Closures

This was another technical aspect that we were proud to implement. When you declare
a function in a local scope, any local variables will be captured by reference to
create a closure. These local variables then get a dedicated place in the data segment
even though they are local variables.
<Demo :code="'adder = 0\nif (true) {\n    d = 1.0\n    adder = construction (a, b) -> (z) {\n        z = a + b + d\n        d = d + 1.0\n    }\n}\nwrite(adder(0, 1))\nwrite(adder(0, 1))\nwrite(adder(0, 2))\nwrite(adder(2.0, 4.2))'"/>

## Technical Challenges

### How to Store Data Types

Given that data types actually need to not only know their type since there is type
checking postulates along with the possibility for the language to be optionally typed.
Additionaly not all data types are equally size. Thus we store each variable as 16 bytes,
8 bytes which notate the type of the variable, and 8 bytes for the value. If the type
is a figure which all need more than 8 bytes for the value, then a pointer to
some area of memory is used which is malloc'd.

### Closures

When we were designing the closures we had to think about where captured variables would
live in memory. We decided to do all captures by reference since we feel this actually
turns out to be simpler to implement. However a capture by value would take the value
of the local value, but not modify the orignal local value.

### Memory Management

When we create new figures and such, memory is malloc'd to store these figures. In
order to prevent excessive memory leaks, these values are cleaned up when the data
in a variable is reassigned. Since there are no references in this language,
this does not cause any issues. This feature is only partially implemented, but was
an important note.

### Linking with Standard Library

We wrote all the standard postulates in C++ along with utilities such as the ability
to throw a runtime exception. Thus we first compile the program to an assembly
file and then extern all these functions while creating variables which bind
to them. Then when we compile, we link with all the C++ object files in order to
generate the final binary.

### This Site

We actually spent quite a while working on this site just for the demo. When you click
run, the code is sent to a AWS EC2 server which is running a Node.js server behind a
Nginx proxy. It is a very basic server since it only has to take your input, run one
command and return the output.

The frontend of the site was written using Vue and is hosted on an AWS S3 Bucket.

#### Auto Deployments

Furthermore, we took the time to invest into setting up CI/CD such that when you commit
to master, the server pulls a new copy and restarts while also updating the S3 bucket.

### Unit Tests

We decided to use Google's googletest C++ testing framework in order to write unit tests
for this project. We have a good number of unit tests for just a couple features while
most of our code is severly lacking in unit tests. But that is life I guess, when you
rush through all these features.

### Computational Geometry

Computational geometry is hard and this project actually consisted of quite a bit of
it. For example, we implemented line intersection in 3D through projections with cross
products. These implementations did take up a significant amount of time since we
had to implement ever possible pair of intersection of figures and write code to
generate the intersected objects.

## Future Work

This project is still very much in a buggy stage. Some parts were rushed as well. Some
unimplemented parts are proper error reporting, better testing, parsing newlines between
statements well, additional operators, tuples, arbitrary number of arguments, multiple
return values, type checking, and possibly many more.

A lot of features still remain unfinished as well, for example not every figure
has a print defined on it, and not every geometry postulate is callable right now.
These aren't exactly a bug, but not every bit of code has been put to use. For example,
since we didn't not finish writing the wrapper function around intersection,
you can only intersect certain pairs of objects even though we have the code for
intersection.

The project has actually grown a lot and there is a significant portion of refactoring
that needs to be done along with more documentation and unit testing. The project has
actually become pretty large without over 3000 lines of C++ (in 14 different files)
plus a few hundred lines of markdown (which this page is written in)
and a couple hundred lines of JavaScript as of writing this. Although most of this code
will remain, maintaining our technical debt is important.

We will open source the GitHub repository for this project after it is done and continue
development. Although we'll take it slower on implementing features to make sure
that we are more thorough which we skipped often when working on this project.

## Thanks

Thanks for listening or reading our presentation! We really enjoyed working on this
project and probably invested just over 100 hours of work combined between us on this
project.
