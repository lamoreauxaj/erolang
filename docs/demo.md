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

<!-- <Demo :code="'a = 1.0\nb = 0.0\nwhile (a is 1.0) {\n    b = b + 0.5\n    if (b is 1.0) {\n        write(b)\n    }\n    if (b is 3.0) {\n        c = 4.2\n        a = b + c\n        write(a)\n   }\n}\nadd = construction (c, d) -> (z) {\n    z = c + d\n}\nc = 1.0\nd = 3.0\n\nwrite(add(c, d))'"/> -->

<Renderer :objects="[{'figure': 'circle', 'center': [0, 0, 0], 'point': [1, 0, 0], 'norm': [0, 1, 0]}]"/>
