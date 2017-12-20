# TankSoccer
A simple OpenGL game and the final project of Computer Graphics course.

Please note that this project is still under development and may have tons of bugs. Although it is far from complete and satisfactory, I consider the framework on which this project is built is workable and should be shared as soon as possible, so that our team can collaborate on it.

Here I will briefly describe the structure of this program.

The abstract base class, "Geometry"  deals with everything related to the apperance of an object, so common functions that control how an object looks like goes here. "Sphere", "Cuboid" and "Cylinder" are all its derived classes. They're the building blocks of the scene.

Another abstract base class, "Entity" deals with the physical models, or the interactions and relations of objects. an "Entity" object is a rigid model, a combination of "Geometry" objects, their relative position and physical parameters that decides its behaviors (velocity, acceleration, deceleration factors, etc.) Currently "Entity" has two derived classes, "Tank" and "Ball".

"Game" class is the "topmost" class in this project. It controls the progress of game, draws the frames and updates the state of entities.

"Vector"(not the C++ "vector") class is defined in "Basic.h", containing several 3-d vector operations which I consider useful. I did overload some of its operators, and I hope this effort will be helpful for further debugging.

Lastly, "main.cpp" here contains the main function, and controls OpenGL.

Dec. 20th
Yiqun Liu
