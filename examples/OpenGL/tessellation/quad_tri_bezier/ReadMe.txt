Cg 3.1 Bezier patch example.

This example shows how to evaluate mixed quad/tri bezier patches on the GPU.

The program itself uses 4 custom programmable pipeline stages:
1. Vertex Shader
2. Tessellation Control Shader
3. Tessellation Evaluation Shader
4. Fragment Shader

The program has two control shaders and two evaluation shaders, one for quad patches and one for triangular patches.
The triangle patches consist of 10 control points, and the quad patches will have 16 control points.

USE

Mouse
- Left button - Click, hold, and drag to rotate the model.
- Middle button - Click, hold, and drag to zoom in and out.
- Right button - Brings up a menu of actions.

Keyboard/menu

The menu contains all the options, including the associated key to press for all actions.

n - Cycle to next model.
t - Toggle between patches and coarse mesh.
<SPACE> - Toggle rotation.
r - Resets rotation.
9 - Decrease rotation ( can go negative ).
0 - Increases rotation.
w - Toggles wireframe mode on the TESSELLATED triangles, not the original control triangles.
  Use with adaptive LOD mode to see the changing LOD on the fly.
x - Toggles between dynamic adaptive LOD mode and fixed LOD mode.
  Levels of detail for both adaptive and explicit can be modified.
o - Outline patches. Triangle patches are blue.
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
; - Decreases the scaling factor for adaptive LOD.  This has the effect of changing the relative size of the
  output tessellated triangles.  Experiment to see different effects.
' - Increases the scaling factor for adaptive LOD.
esc - Exits the application.
