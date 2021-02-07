Quick start: Press 'R', then 'Q', then start clicking.

Demo:

https://malkiewiczm.github.io/3d/index.html

## Editor Keybinds

All editing except selections only work in orthographic views

- Q: toggle between "insert mode" and "select mode"
     once in insert mode, click to insert nodes
- S: switch to selection mode
- H: toggle show control mesh
- M: move selection
- Delete: delete selected nodes

## Cameras Keybinds

- 1: reset camera

Orthographic Views

- F: front view
- B: back view
- R: right view
- L: left view
- T: top view
- Y: bottom view

Perspective Views

- 3: 3d view... right click to look around, WASD to move around
- 4: look at the car
- 5: point-of-view mode

## Compiling

1. Requires emscripten and mingw32
2. gen_make.sh or gen_make.bat generates the makefile
3. Run emsdk_env.bat from emscripten installation
4. Run mingw32-make
