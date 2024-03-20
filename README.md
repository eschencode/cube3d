# cub3d

A graphical group project of 42 in which you learn to use raycasting to develop a 3D-game in the fashion of Wolfenstein.

## Background Knowledge

### Raycasting

Raycasting is a rendering technique which let’s 2D appear as 3D, more precisely: it gives you a 3D perspective on a 2D map. Therefore, it is impossible to move in the third dimension (moving up or down) or to display different heights.

In order to give this 3D illusion, rays are casted from the point of the spectator. Depending on the length of the rays, the objects that are hit by the rays are displayed as greater or smaller. Moreover, objects, like walls, can be coloured differently depending on which direction they are facing. This increases the 3D illusion effect. 

A very good guide is: https://lodev.org/cgtutor/raycasting.html

#### DDA Algorithm

DDA is the abbreviation for *Digital Differential Analyzer*. It is one of the simplest and fastest line generation algorithm. By incrementing from one point to the next point, it calculates a line.

Steps:
	1. You have two points, with each two coordinates:
		int x1, y1, x2, y2
	2. You calculate the difference between the two points:
		float dx = x2 - x1;
		float dy = y2 - y1;
	3. Calculate the slope:
		float m = dy / dx;
	4. If m > 1 -> you calculate the next point by:
		float xn = x1 + 1/m
		float yn = y1 + 1
		if m < 1 -> you calculate the next point by:
		float xn = x1 + 1
		float yn = y1 + m
	5. If m = 1 -> you found your point
		x1 = xn
		y1 = yn

This algorithm will be used to find the point where we hit a wall or another object (we can see until there is a object in our way).

#### 

1. Position of player: pos (x, y)
2. Direction they are looking: dir (x, y)
3. "Camera plane": the line on the map that the player sees and that will be displayed on the screen

So, we have 
			pos (x, y)
			dir (x, y)
			central focus point: pos + dir
			leftest point of vision: pos + dir - plane
			rightest point of vision: pos + dir + plane

The Field of Vision (FOV) is calculated through the lenght of dir and of the camera plane. For a first person game, an FOV of 66 degrees is good. This means that the direction vector is slightly longer than the camera plane. 
