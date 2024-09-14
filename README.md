# miniRT
My first RayTracer using the [minilibx](https://github.com/42Paris/minilibx-linux) graphics library.

> The main goal of miniRT is to prove to yourself that you can implement any mathematics or physics formulas without being a mathematician

## **About:**
**Mandatory part:**
- Your program has to display the image in a window.
- The management of your window must remain fluid (changing to another window, minimizing, and so forth).
- You need at least these 3 simple geometric objects: plane, sphere, cylinder.
- If applicable, all possible intersections and the inside of the object must be handled correctly.
- The use of the images of the MiniLibX is mandatory
- Your program must be able to resize the object’s unique properties: diameter for a sphere and the width and height for a cylinder.
- Your program must be able to apply translation and rotation transformation to objects, lights and cameras (except for spheres and lights that cannot be rotated).
- Light management: spot brightness, hard shadows, ambiance lighting (objects are never completely in the dark).
- You must implement Ambient and diffuse lighting.
- Your program must take as a first argument a scene description file with the .rt extension

**Example output (temple.rt):**
![Screenshot_20240912_144439](https://github.com/user-attachments/assets/43da2912-b22a-49de-a68a-68bac75dfbe7)

## **Usage:**
*This program is designed to work on MacOS and Linux.*

```shell
# Clone the repository:
$> git clone --recursive https://github.com/fv99/miniRT.git

# Compile:
$> make

# Run with valid map as parameter:
$> ./miniRT map.rt
```

### **Example input:**
Elements which are defined by a capital letter can only be declared once in the scene.
```
$>cat testmap.rt
A 0.5 0,0,0
C 0,0,0 0,0,1 90
L 0,0,0 0.9 255,130,0
sp 0,3,8 3 100,0,100
pl 0,30,10 0,1,-1 255,100,0
cy 2.0,0.0,20.6 1,-1,0 5.2 10.42 10,0,255
$>
```
