#pragma once
#include <iostream>
#include <windows.h>
#include "PacmanLocation.h"
#include "PacmanConstantsFunctions.h"
using namespace std;

// Base Class (Abstract class)
class Character {
public:
	Position location; // character 'has a' location

	Character(int x, int y) :location(x, y) {}
	void updateLocation(int x, int y);
	bool isLocation(int x, int y);
	virtual void setCharacter(int x, int y, int color) = 0; // pure virtual function
};

// Derived Classes

// protagonist of the game
class Pacman : public Character {
	char pacman;
public:
	Pacman(int x, int y) :Character(x, y) {
		pacman = 'P'; // set character to represent pacman
	}

	void setCharacter(int x, int y, int color) override {
		updateLocation(x, y); // puts cursor on given (x,y) 
		SetConsoleTextAttribute(hConsole, color);
		cout << pacman;
	}

	int getXPacman() const;
	int getYPacman() const;
};

// antagonist of the game
class Ghost : public Character {
	char ghost;
public:
	Ghost(int x, int y) : Character(x, y) {
		ghost = 'G';	// set character to represent a ghost
	}

	void setCharacter(int x, int y, int color) override {
		updateLocation(x, y); // puts cursor on given (x,y)
		SetConsoleTextAttribute(hConsole, color);
		cout << ghost;
	}

	void moveRandom(Map& obj, int frame_count); // inky's movement 
	void directPursuit(Map& obj, Pacman& pm, int frame_count); // blinky's movement
	bool caughtByGhost(Pacman& pm);
	bool caughtByPacman(Pacman& pm, Map& obj);
	void leaveBox(Map& obj, int frames, int color); // to make ghosts leave their "house"
};

// FUNCTION DEFINITIONS

void Character::updateLocation(int x, int y)
{
	location.updatePos(x, y);
	setCord(x, y);
}

bool Character::isLocation(int x, int y)
{
	if (location.getXpos() == x && location.getYpos() == y)
		return true;
	else false;
}

int Pacman::getYPacman() const 
{
	return location.getYpos();
}

int Pacman::getXPacman() const 
{
	return location.getXpos();
}

void Ghost::moveRandom(Map& obj, int frame_count)
{
	int ghost_x = location.getXpos();
	int ghost_y = location.getYpos();
	bool wall = true;
	srand(time(NULL)); // set seed so that random numbers are different everytime it runs

	 // inky is cyan
	if (frame_count % ghost_speed == 0) // to slow down the ghosts (moves every 10 frames)
	{
		do {
			int random_direction = rand() % 4; // generate a random number between 0 and 3
			switch (random_direction) {
			case 0: // right
				if (!obj.isWall(ghost_y, ghost_x + 1)) {
					ghost_x++;
					setCharacter(ghost_x, ghost_y, 11);
					wall = false;

				}
				break;
			case 1:	// down
				if (!obj.isWall(ghost_y + 1, ghost_x)) {
					ghost_y++;
					setCharacter(ghost_x, ghost_y, 11);
					wall = false;

				}
				break;
			case 2:	// left
				if (!obj.isWall(ghost_y, ghost_x - 1)) {
					ghost_x--;
					setCharacter(ghost_x, ghost_y, 11);
					wall = false;

				}
				break;
			case 3:	// up
				if (!obj.isWall(ghost_y - 1, ghost_x)) {
					ghost_y--;
					setCharacter(ghost_x, ghost_y, 11);
					wall = false;

				}
			}
		} while (wall);	// regenerate movement as long as there is a wall
	}
	else
		setCharacter(ghost_x, ghost_y, 11);
}

void Ghost::directPursuit(Map& obj, Pacman& pm, int frame_count)
{
	int ghost_x = location.getXpos();
	int ghost_y = location.getYpos();
	int pacmanx = pm.getXPacman();
	int pacmany = pm.getYPacman();
	bool wall = true;

	if (frame_count % ghost_speed == 0) { // to slow down the ghosts (moves every 10 frames)
		if (pacmanx < ghost_x) // pacman behind ghost in x-direction
		{
			if (!obj.isWall(ghost_y, ghost_x - 1))
			{
				ghost_x--; // move left
			}
		}
		else if (pacmanx > ghost_x) // pacman ahead of ghost in x-direction
		{
			if (!obj.isWall(ghost_y, ghost_x + 1))
			{
				ghost_x++; // move right
			}
		}

		if (pacmany < ghost_y) // pacman is above the ghost
		{
			if (!obj.isWall(ghost_y - 1, ghost_x))
			{
				ghost_y--; // move up
			}
		}
		else if (pacmany > ghost_y) // pacman is below the ghost
		{
			if (!obj.isWall(ghost_y + 1, ghost_x))
			{
				ghost_y++; // move down
			}
		}
		setCharacter(ghost_x, ghost_y, 12);
	}
	else
		setCharacter(ghost_x, ghost_y, 12);
}

bool Ghost::caughtByGhost(Pacman& pm)
{
	int ghost_x = location.getXpos();
	int ghost_y = location.getYpos();
	int pacmanx = pm.getXPacman();
	int pacmany = pm.getYPacman();

	if (ghost_x == pacmanx && ghost_y == pacmany) // if (x,y) of ghost and pacman match
		return true;
	else
		return false;
}

bool Ghost::caughtByPacman(Pacman& pm, Map& obj)
{
	int ghost_x = location.getXpos();
	int ghost_y = location.getYpos();
	int pacmanx = pm.getXPacman();
	int pacmany = pm.getYPacman();

	if (ghost_x == pacmanx && ghost_y == pacmany) { // in energizer mode, if their (x,y) match
		obj.setPoints(10, pacmany, pacmanx); // increase points by 10
		return true;
	}
	else
		return false;
}

void Ghost::leaveBox(Map& obj, int frames, int color)
{
	int ghost_x = location.getXpos();
	int ghost_y = location.getYpos();
	if (frames % 20 == 0)
	{
		ghost_y--;
	}
	setCharacter(ghost_x, ghost_y, color);
}