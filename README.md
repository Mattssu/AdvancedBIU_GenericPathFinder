# Advanced Programing project - 2nd Mile Stone

###### We're creating a thread based Generic Problem Solver.

It consists of 2 main parts:

### First Part:

We have a generic **server** that recieves a specfic problem and it handles it with the correct problem handler
that either solves the appropriate problem that he recived from the **client** or gets the solution from the cache file.
Following those classes we made a Parallel Server that can many clients simultaniously.

###### We can see the scheme below:

![server scheme](https://i.imgur.com/eZPTeml.png)

### Second Part :

We have a generic Solver class and a generic Problem class that contains a state (those classes utilise the Bridge design pattarn).
In that way every specific problem has its own Solver and that way it assures the SOLID principles.
