This program implements all the commands including orient and tiffwrite as extra credits.

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
