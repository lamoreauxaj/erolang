# Demo

Welcome to our demo! Hopefully you are excited to check out the language. The goal
is to also add a renderer to this demo, so you can visualize the constructions
which you write.

Below here is an editor which you can edit the given code and run it. The output
of the code and any errors will be shown below.

Give it a try! There is some sample code here for you to get started with.

**Disclaimer:** There is a high liklihood of bugs. In fact I can name quite a few.
Feel free to play around with it and see what works.
The error messages are in beta, sometimes they
are okay, while sometimes you'll get significantly less helpful messages.

<Demo :code="'a = point(0, 0, 1)\nb = point(1, 0, 0)\nc = point(0, 1, 2)\nd = plane(a, b, c)\ne = sphere(a, b)\nf = intersection(d, e)\nwrite(f)'"/>
