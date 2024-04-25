# cub3d

A graphical group project of 42 in which you learn to use raycasting to develop a 3D-game in the fashion of Wolfenstein.

## Background Knowledge

### Raycasting

Raycasting is a rendering technique which let’s 2D appear as 3D, more precisely: it gives you a 3D perspective on a 2D map. Therefore, it is impossible to move in the third dimension (moving up or down) or to display different heights.

In order to give this 3D illusion, rays are casted from the point of the spectator. Depending on the length of the rays, the objects that are hit by the rays are displayed as greater or smaller. Moreover, objects, like walls, can be coloured differently depending on which direction they are facing. This increases the 3D illusion effect. 

A very good guide is: https://lodev.org/cgtutor/raycasting.html

## Usage

### Clone Repository

The graphical window is created with the help of the mlx library. A basic graphic library created by 42. It is not included in this repository and has to be downloaded first:

	https://github.com/42Paris/minilibx-linux

Follow the guidelines on the github repository.

Then git clone this repo and cd into the folder:

	git clone git@github.com:tstahlhut/cub3d.git
	cd cub3d

Run make to build the executable:

	make

If you get the following error, you have to change the path to the minilibx you downloaded at the beginnning. You can do so in the file ./inc/cub.h in line 16.

	In file included from src/main.c:13:
	src/../inc/cub.h:16:11: fatal error: '../../../minilibx-linux/mlx.h' file not found
	# include "../../../minilibx-linux/mlx.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	1 error generated.
	make: *** [<builtin>: src/main.o] Error 1

## Run Program

Cub3D takes one argument which is a map. The map is a textfile with the extension **.cub**. This repository has four maps which represent level 0 to level 3. Start with the first level:

	./cub3D maps/level0.cub

The game stops when you hit the exit door (a blue door with the word "exit" on it). In the terminal you will see a timer which monitors how long it takes you to find the exit. Your score is not saved anywhere.

### Maps

You can also create your own maps. In the textfile (don't forget the .cub extension) you have to specify (1) the ceiling color (C) and the floor color (F) in RGB. 

	F  19,109,21
	C 153,204,255

(2) You have to provide a path to the textures which the walls should have: One for North (NO), South (SO), East (EA) and West(WE). You can find the textures we used in the ./textures file. The textures have to be xpm files. If you have a png, you can convert it for example with this free converter: https://convertio.co/kr/. 

	SO textures/wood.xpm
	NO textures/greystone.xpm
	WE textures/colorstone.xpm
	EA textures/stone.xpm

(3) The map is made by zeros (walkable space) and ones (walls). You can play around and modify the map. However, the map has always to be closed by walls, otherwise you get an error. If you want to add an exit, you add a "2". You may also add several exit doors. 

	11111111111111111111
	10010000000000001111
	10000011011010011111
	20010000011011011111
	10000000011011001111
	10010000W11000001111
	10011111111111001111
	10010011111111001111
	10111000000000001111
	11111111111111111111
	11111111111111111111

The player is represented by N, S, E or W which specifies the starting direction, i.e. the direction the player looks to at the start of the game. You can also modify that. 

Now, there is only one thing to say: Have fun!



If you find any bugs, please report them to us.