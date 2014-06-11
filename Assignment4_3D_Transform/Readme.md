3D Transformations
============

An c++ to implement 3D transfor-
mations. 

Implement a matrix stack, and translate, rotate, scale, and view
an object via both orthographic and perspective projections.

Users stories
--------------
- Users could translate, rotate, scale 3D models.

![Image Alt](/Assignment4_3D_Transform/demo/faces_c.png)
- Rotate Test

![Image Alt](/Assignment4_3D_Transform/demo/junk_c.png)
- Rotate and Perspective test.

![Image Alt](/Assignment4_3D_Transform/demo/ortho_test_c.png)
- Ortho projection test.

![Image Alt](/Assignment4_3D_Transform/demo/persp_c.png)
- Perspective test.

![Image Alt](/Assignment4_3D_Transform/demo/orient2_c.png)
- Orient object.

![Image Alt](/Assignment4_3D_Transform/demo/orient3_c.png)
- Non-affine transformation.


I have write a script called test.cli.
When you open the main window, the command "read test.cli" will generate all the test cases and save the as tif with suffix "_c".

For orient command, the orient matrix is actually a general form of affine transformations(except the translation). 
[a,b,c,0,
d,e,f,0,
h,i,g,0
0,0,0,1]
When the letter are non zero, it is a shear transformation matrix.
When b,c,d,f,h,i are zeros, it is a  scale transformation matrix.
All we can change to Rotation matrix as well.
