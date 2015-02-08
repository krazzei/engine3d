# Engine3d
Hi there!
This is my project I am using to learn 3D rendering with OpenGL. Use this project to learn or as a starting point for your own rendering engine. This engine will hopefully be able to run on Linux and Mac, but for now its only tested on Windows (you can try to build on another platform but my buiding tutorial does not cover that).

# Building
Ok, so you've gotten the files now its time to build this sucker! Go grab Visual Studio Community edition!

1. Build the PNG and ZLIB Libraries:
Lets build the png library (and the zlib library), navigate to {repositoryLocation}\3rd_party\lpng1616\projects\vstudio and open the solution in visual studios. After it loads right click on the "libpng" project and build it (Debug or Release).

2. Build the GLFW Library:
Next is GLFW, navigate to {repositoryLocation}\3rd_party\glfw-2.7.6\support\msvc100 and open GLFW.sln in visual studios, upgrade any projects. After it loads build "GLFW" project by right clicking on it and selecting build.

3. Build the GLEW Library:
Finally is the GLEW library, navigate to {repositoryLocation}\3rd_party\glew-1.9.0\build\vc10 and open the glew.sln with visual studios, upgrade the projects. After it loads right click on "glew_shared" and build it.

4. Build the Engine:
Now its time to build the engine! navigate to {repositoryLocation}\Engine3D_express and open the Engine3D_express.sln with visual studios. Now hit F5 to build and run, once thats done a window should open up and you should see a wood box in front of you, move the camera around with WASD, you can look with the mouse. You can also move the light around with IJKL (like WASD only on the other side of the keyboard) and move it up and down with U and O, respectivly.
