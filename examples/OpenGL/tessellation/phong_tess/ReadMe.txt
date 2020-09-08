Cg 3.1 Phong Tessellation example.

This example is an implementation of the Phong tessellation algorithm found in

Phong Tessellation reference : 
  Phong tessellation,
  Tamy Boubekeur and Marc Alexa
  ACM ToG, Vol. 27, No. 5, 2008.

The program itself uses 4 custom programmable pipeline stages:
1. Vertex Shader
2. Tessellation Control Shader
3. Tessellation Evaluation Shader
4. Fragment Shader

The program is designed around using 3-control point patch primitives 
and the associated normals at the vertices to produce patches representing the
geometric equivilent of the Phong shading model.

USE

Mouse
- Left button - Click, hold, and drag to rotate the model.
- Middle button - Click, hold, and drag to zoom in and out.
- Right button - Brings up a menu of actions.

Keyboard/menu

The menu contains all the options, including the associated key to press for all actions.

n - Cycle to next model.
w - Toggles wireframe mode.  Use with adaptive LOD mode to see the changing LOD    on the fly.
0 - Increase phong shape factor (0 is the same as linear interpolation)
9 - Decrease the phong shape factor(1 is max).
s - Toggle specular component of lighting model. (Helpful for seeing outline)
x - Toggles between dynamic adaptive LOD mode and fixed LOD mode.
  Levels of detail for both adaptive and explicit can be modified.
o - Outline triangle patches.
] - Increase outer tessellation levels.
  While 3 parameter are used, they are all increased uniformly in this implementation.
[ - Decrease outer tessellation levels.
  While 3 parameter are used, they are all decreased uniformly in this implementation.
+ - Increase inner tessellation levels.
  All increased uniformily.
- - Decrease inner tessellation levels.
  All decreased uniformily.
d - Draw the control cage wires.  This will show the outlines of the original input patches (3 cntrl points)
h - Draw hidden control cage wires.  This will draw control cage wires which are hidden from view by the model.
' - Increases the scaling factor for adaptive LOD.  This has the effect of changing the relative size of the
    output tessellated triangles.  Experiment to see different effects.
; - Decreases the scaling factor for adaptive LOD.
esc - Exits the application.
