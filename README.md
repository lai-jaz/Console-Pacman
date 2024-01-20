# Console-Pacman
A console application for pacman with two of the original game's ghosts'.

# Controls:
Arrow keys move pacman across the maze, allowing it to eat the pellets scattered around. To win the game, the user should eat all the pellets and the user loses if they lose all 3 lives (which are lost by getting caught by the ghost).

# Project files: 
PacmanMain.cpp => Main function, the main game loop and some of the logic of placement of the characters of the game and their behaviour according to the game mode (Normal / Energizer). It also contains the module that controls the movement of Pacman.

PacmanMap.h => Contains the Map class that makes and prints the maze and also tracks the pellets being eaten, the scores and makes sure that the characters do not bypass the walls.

PacmanLocation.h => The position class is defined that contains the x and y locations of characters.

PacmanCharacters.h => This header file contains the base class, where the Character class is defined, and all the functionalities regarding the characters (Pacman and Ghosts) have been defined. The Pacman class addresses the functions, movements, positioning and abilities of pacman's character. The Ghost class defines functionality for the movement and behaviours of the ghosts. One movement type is direct pursuit, where the ghost tries to catch Pacman by pursuing it through comparing their positions and the other is random movement through which the ghost decides its next step randomly.

PacmanConstantsFunctions.h => This header file contains the constants defined for the initial locations of the characters and the dimensions of the map. It also contains the speed of ghosts and the bool value that determines the energizer mode of the game. There are also some user-defined functions for the starting screen, game over screen, etc.
