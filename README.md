# cub3D
21-School (Ecole42) 'cub3D' project. Score 108/115.

## Description
The goal of this project is to make a dynamic view inside a maze using ray-casting principles.

## Usage
Project tested on macOS Catalina 10.15.5, Linux Manjaro 20.1 with KDE Plasma 5 and Linux Ubuntu 20.04 with KDE Plasma 5 (aka Kubuntu).

On macOS, the project uses the `minilibx_mms_20200219_beta.tgz` version of library sources from the 42 intra subject page. On Linux - [`minilibx-linux`](https://github.com/42Paris/minilibx-linux "lib for easy work with Xlib, made for 42 students") (from public repository [Ecole 42](https://github.com/42Paris)). Also in this project used my own Libft library with functions from my previous projects [`Libft`](https://github.com/awerebea/libft) and [`get_next_line`](https://github.com/awerebea/get_next_line).

The Makefile automatically detects the current OS and selects compilation options based on that.
So, to build libraries and program no matter what your current system is (macOS or Linux), just run:

`make` or `make bonus` (to build **cub3D** with mandatory part conditions only or with with some bonuses, accordingly).

*\* if you have some troubles while building your project on Linux, look up the [troubleshooting](https://github.com/awerebea/cub3D/blob/master/README.md#troubleshooting-on-linux) section.*

to run program use: `./cub3D maps/default.cub` or `./cub3D maps/default_bonus.cub` (where `*/*.cub` - is path to the [scene description file](https://github.com/awerebea/cub3D#scene-description-file)). 

or simple `make run` or `make run_bonus` to build and automatically run the program with predefined scene description files.

You can use the second (`--save`) argument to save the first rendered image in bmp format instead of running the program in a window.

`./cub3D maps/default.cub --save` or `./cub3D maps/default_bonus.cub --save`

or simple `make screenshot` or `make screenshot_bonus` to build and automatically run the program with predefined scene description files and second `--save` argument.

Saved "screenshot" will appear in the root directory of the project with name `screenshot.bmp` (or `screenshot_2.bmp`, `screenshot_3.bmp` etc if file with such names already exist).

## Troubleshooting on Linux
If you have fail, while building the **libmlx.a**, first of all make sure that all the necessary dependencies are installed in the system. If you get linker errors like `cannot find -lXext` or `cannot find -lbsd`, install required packages. For example, on Ubuntu, you can run:
```
sudo apt update
sudo apt install libxext-dev
sudo apt install libbsd-dev
```
Also, in Linux Manjaro and Linux Ubuntu on my PC, I have to use different compilers to build **libmlx.a**: the **clang** on Manjaro, and **gcc** on Ubuntu. So if you continue to receive a fail while building **libmlx.a**, try changing the compiler in the `minilibx/linux/Makefile.mk`, line #18 `CC = gcc` or `CC = clang` accordingly, or just run `make mlx_gcc` or `make mlx_clang` to do this automatically, and then try to build project again.

## Controls
`W` `A` `S` `D` `LEFT ARROW` `RIGHT ARROW` - to control player moves and rotates.

`ESC` or "red cross" of window - to quit program.

*additional, in **bonus** part only:*

`MINUS (-/_)` `PLUS (+/=)` - to change scale of radar minimap.

`SHIFT (left)` `SPACE` - to crouch and jump.

`M` - to toggle mouse hook (to be able to move the mouse pointer outside the window and, for example, press the red cross). 

## Scene description file

The **\*.cub** file, which passed to the program as the **first mandatory** argument.
In general file must contain:

* Window size (width height) in pixels. If given resolution is bigger than your current screen is, it will fit to your current screen resolution.

* Path's to textrure files for notrh, south, west, east walls and sprite in .xpm format.

* Floor and eiling color in R,G,B format.

* "Map" strings, where `1` - wall `0` - empty "walkable" space `N` `S` `W` or `E` - spawn point (with initial direction of player view) `2` - sprite.

Example of simple valid scene description file for **mandatory** part:
```
R   1920 1080
NO  ./path_to_textures/north_texture.xpm
SO  ./path_to_textures/south_texture.xpm
WE  ./path_to_textures/west_texture.xpm
EA  ./path_to_textures/east_texture.xpm
S   ./path_to_textures/sprite_texture.xpm
F   220,100,0
C   225,30,0

    111111111111111111111
    100000000000000000001
1111100010002000000000001
1000000010000001111111111
10000N001000000020001
1000111111110000000011111
1000000000010010000000001
1110000000000010200000001
  11111111111111111111111
```

In the bonus part, the floor and ceiling have textures instead of solid colors, so `F   220,100,0` and `C   225,30,0` strings from the example file above, in file for **bonus** part must be represent in following format:
```
F   ./path_to_textures/floor_texture.xpm
C   ./path_to_textures/ceiling_texture.xpm
```
*(Also in bonus part added a distance related shadow effect, the ability to rotate the viewpoint with the mouse and a radar minimap showing the player's current position, the direction of view, and sprite position markers.)*

## Screenshots
![mandatory part (cub3D)](https://user-images.githubusercontent.com/63558838/92263365-327a0380-eee5-11ea-9a75-e3ebb2703833.png)
![bonus part (cub3D_bonus](https://user-images.githubusercontent.com/63558838/92263416-49205a80-eee5-11ea-9c16-d95f3b93e7bc.png)
