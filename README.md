# froglib
A code-only game engine using C++ and raylib that's still in development.

## features
### core
A game class with run, load, update and draw functions which can be overriden.

### physics
So far I have a small rigidbody physics system that runs on a seperate thread at a fixed framerate. you can apply forces and impulses.

### rendering
Only a few helper functions to minimize boilerplate.

### math
A Vec2 class for Vector2's with operator overloading for most common operators.

### entities
An entity class for things that need to be drawn and updated to inherit from.
