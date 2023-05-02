## Add any additional notes here

- Run the tilemap editor with `python3 tilemapEditor.py` after building
- Run the sprite editor with `python3 spriteEditor.py` after building
- Run the example game with 'python3 game.py` after building

## Game/Engine Publicity

**Project Website**: https://sites.google.com/view/cs4850-stuart-little-engine/home?authuser=0
## Compilation Instructions
*Potential Dependencies* <br>
Tkinter should be come installed with python, but if not, it can be installed with `pip install tk` or other similar installation methods. <br>
*For Mac (python3.9):* `python3 build.py` <br>
*For MinGW (python3.6):* `sh mingw64Python3_6build.sh`<br>
*For MinGW (python3.9):* `sh mingw64Python3_9build.sh`<br>

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have 

### ./Engine Directory Organization

- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
- lib
    - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
    - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.
