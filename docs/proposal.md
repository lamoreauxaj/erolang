# [PA Proposal] Geometers -- writing a compiler for a geometric language called Ero to create Euclidean constructions

**Team Members:**
- Aaron Lamoreaux
- Anand Iyer

## The Idea

We want to build a compiler in C++ for a language called Ero (this is a self-designed language). We are really excited for this project and anticipate it being ~~fun~~ (sorry, we're not working on Fun - Ero?). *Actually the language was originally called Euclid, but we decided to change that name.*

This language is unique for a few reasons. The core data types are geometric figures as the language is meant to allow you to specify Euclidean constructions. The language has a core set of postulates which allow one to construct any Euclidean construction using just those postulates. The language is heavily inspired by classical geometry and Euclid's Elements.

You could call the language **Euclidean complete** (not a real term, but we'll call it that) since any geometric construction that you could make using the postulates described by Euclid in his Elements, you could describe in this language.

In fact, this language does not even need real numbers in order to be able to specify these constructions. Furthermore the langauge is technically **Turing complete** even without real numbers since the type system along with the ability to type check (which was originally the only conditional in the language) and recursion does technically allow the language to simulate any Turing machine albeit awkwardly.

***Important Note:*** this idea was already in existence before the final project in this class. Since we want to write a compiler for the language and there is no code for this effort already, the work in this project will be new work but built upon a previous idea.

### Background on the Language

The idea for this language originated from a previous project that Aaron and a friend from high school (James) built at a hackathon. It was inspired as a creative way to specify geometric diagrams for a VR project in Unity called Experimental Geometer which would allow the player to render the diagrams and actually play with them in 3D space.

[Here](./experimental-geometer-demo.mp4) is a video of our demo if you want an idea of the project. The quality is bad since this is a screen recording of a Youtube video recorded with a phone which recorded a projector which was playing a screen recording of someone demoing the application. I don't have the original video, sorry!

This was actually part of the code that ran that demo. Do not that this code does not match the syntax which we are implementing (for example, the choice to have lack of commas in parameter lists).
```
a = point(0.0 1.0 0.0)
b = point(0.0 1.1 0.0)
c = point(0.1 1.0 0.0)
d = point(0.2 1.2 0.1)
x = point(0.35 1.1 0.2)
y = point(0.30 0.9 0.1)
ba = point(0.30 0.8 0.1)
bb = point(0.35 0.7 0.0)
bc = point(0.30 0.6 0.2) 
bd = point(0.0 0.5 0.1)
bin = binormal(line(ba bb) line(bc bd))

m = intersection(line(x y) midnormal(x y))

s = circumsphere(a b c d)
cen = center(s)

...
```

The project was demoed with a crappy interpreter written in 24 hours for the language which was written in C# and was a single 600+ line file. This interpreter has bugs (for example negative numbers didn't work).

I (Aaron) have wanted to return to this project for a while and write a complete implementation of the language.

## Ero Features

**Features:**
- Figure types which are Point, Line, Segment, Ray, Plane, Circle, Arc, Sphere, Empty, and Space.
- Postulates (core functions) which are `plane(alpha, beta, gamma)`, `sphere(center, p)`, `line(alpha, beta)`, `segment(alpha, beta)`, `point(x, y, z)`, `ray(endpoint, p)`, `arc(start, p, end)`, `intersection(alpha, beta)`, `point_on(alpha)`, `endpoints(alpha)`, and `center(alpha)`.
    - These postulates are actually sufficient to create any construction which could be done on paper. In fact the point function requires real numbers which aren't even needed. Furthermore, one could omit ray / arc as well. An interesting feature of the language is that the figure type of the intersection of any two figures is also in the given set of figures (closed under intersection).
    - Some of these functions have multiple return values. We are still deciding on how to handle this, either when you do assignment you can specify a list of things to assign like `a, b = intersection(x, y)` and later items in the list are empty. Or we could go further and support data types which are tuples.
    - We know exactly what each of these functions are intended to do, however the names should hopefully give you good explanation of their purpose.
- Global constants including space and empty.
- Conditional if statements and a boolean conditional for type checking.
- Construction statements (functions) which take parameters, return values, and can be recursive.
- The ability to write to stdout a figure type. This will write the figure to stdout in a specific format that would allow someone reading stdout to be able to render the figure.

The above list is a mostly complete selection of the features which we want to have in the language. The key ones are functions which are recursive and return values with local scope as well along with conditionals and multiple data types. We think this is sufficiently complex for two weeks, but maybe we will be able to implement more.

### Features outside the language

Considering this is a geometric language, our goal is also to be able to render the diagrams. Thus we would like to take the output of an executable and run it and render the output in some way. We were thinking of creating a simple WebGL application which would take the output and render it to a canvas. Neither of us have messed with these APIs before, but we don't anticipate this being a large portion of the work in the project over the compiler, but it still a key part of our idea.

## The Plan

We hope to implement the ability for the compiler to tokenize the language construct some sort of syntax tree and compile basic programs as quickly as possible hopefully within a few days. We will both we working on this together at the start.

Afterward, we will implement all the geometric constructs and a basic renderer in a couple days (we don't anticipate this being complex). One of us will likely implement all the computational geometry logic and the other will work on the renderer.

We will then return to flush out the compiler making sure features like local variables and function calls are working as intended which may be skipped in the first compiler implementation. Again since this is the hardest part of the project, we will work on this part together.

This is a rough plan, but hopefully should give you an idea of the order in which we will work on this project.

## Some Sample Programs

The following program creates a diagram that was from an old AMC problem.
```
c = point(0, 0, 0)
b = point(4, 0, 0)
a = point(0, 3, 0)
d = point(4, 0, 4)

l1 = segment(b, c)
l2 = segment(a, b)
l3 = segment(a, c)
l4 = segment(a, d)
l5 = segment(b, d)
l6 = segment(c, d)

write(l1)
write(l2)
write(l3)
write(l4)
write(l5)
write(l6)
```

The following constructions take two points and return the midnormal and the midpoint respectively.
```
midnormal = (a b) -> (p) {
    cir = intersection(sphere(a, b), sphere(b, a))
    p = plane(point_on(cir), point_on(cir), point_on(cir))
}

midpoint = (a b) -> (p) {
    p = intersection(line(a, b), midnormal(a, b))
}
```

#### References

- [Euclid's Elements](https://www.gutenberg.org/files/21076/21076-pdf.pdf). This inspired a lot of the language ideas.
- [Experimental-Geometer](https://github.com/JamsRamen/Experimental-Geometer). This is the GitHub for the previous project. This is mostly here so you can be aware of what work has already been done to ensure that this project is new work. In here you can find an interpreter (which is over 600 lines and has 27 classes in a single file - please don't ask why there are 27 classes in one file) which implemented a set of features not too far from what we plan to implement.
