Terrain tessellation

This program implements two techniques to do terrain tessellation.  The first technique
uses the common displacement map.  With this technique, patches are produces across a flat
surface and then uniformly interpolated in the tessellation evaluation shader.  These points
then sample a heightmap and displacement themselves along a common normal (0,0,1).  In the fragment
shader, the tangent components are sampled from the displacement texture and used for smooth shadeing.

The other technique uses B-spline evaluation.  Overlapping patches are used in the example.  The data
points are the sampled points from the heightmap, and cubic b-spline segments are evaluated for each patch.
This creates a smooth surface which is continuous both in position and tangent.  This is useful for smoother terrain,
such as a desert, or for using additional displacement mapping on

Controls:

Left mouse - Rotate
Right mouse - Menu
Middle mouse - Zoom in/out.

b Toggle between b-spline and regular displacement
c Toggle draw checker pattern exposing patches.
p Pause the rotation
0 Speed up rotation.
9 Slow down rotation
w Toggle wireframe mode.
x Toggle explicit and adaptive LOD
8 Increase number of patches along the x direction.
i Decrease number of patches along the x direction.
7 Increase number of patches along the y direction.
u Decrease number of patches along the y direction.
] Increase explicit outer tessellation level.
[ Decrease explicit outer tessellation level.
+ Increase explicit inner tessellation level.
- Decrease explicit inner tessellation level.
' Increase adaptive LOD scaling factor.
; Decrease adaptive LOD scaling factor.
esc Exit application.