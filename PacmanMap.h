#pragma once
#include <iostream>
#include <windows.h>
#include "PacmanConstantsFunctions.h"
using namespace std;

class Map {
	char map[map_rows][map_columns]; // array of map
	int count_pellets; // count of pellets maintained to check if user won the game
	int points; // maintain scores

public:
	Map();
	void makeMaze();
	int countPelletsInitial(); 	// count pellets at the start
	void printMap();
	void removePellet(int prev_x, int prev_y); // pellet at previous coor of pacman gets removed
	int getPelletCount() const;	
	void removeEnergizer(int prev_x, int prev_y); // energizer at previous (x,y) of pacman gets removed
	void setPoints(int pt, int prev_x, int prev_y);// add points every time pacman eats a pellet/energizer/ghost
	int getPoints() const;
	bool isEnergizer(int i, int j); // check if pacman obtained an energizer at given index
	bool isWall(int next_i, int next_j); // check if the next index is a wall 
};

Map::Map() 
{
	// outer walls (boundary) and pellets
	for (int i = 0; i < map_rows; i++) {
		for (int j = 0; j < map_columns; j++) {
			if (i == 0 || i == map_rows - 1) {
				map[i][j] = 'X';
			}
			else if (j == 0 || j == map_columns - 1) {
				map[i][j] = 'X';
			}
			else
			{
				map[i][j] = '.';
			}
		}
	}
	// inner walls (maze)
	makeMaze();
	map[6][6] = 'O'; // placing the energizers
	map[28][6] = 'O';
	map[6][33] = 'O';
	map[28][33] = 'O';
	count_pellets = countPelletsInitial();
	points = 0;

}

void Map::makeMaze()
{
	for (int i = 0; i < map_rows; i++) {
		for (int j = 0; j < map_columns; j++) {

			// first row of walls
			if (i >= 2 && i <= 5) {
				if ((j >= 4 && j <= 9) || (j >= 13 && j <= 16)) {
					map[i][j] = 'X';
				}
				else if ((j >= 23 && j <= 26) || (j >= 30 && j <= 35)) {
					map[i][j] = 'X';
				}
			}

			// middle top line of wall
			if (i >= 1 && i <= 7) {
				if (j == 19 || j == 20) {
					map[i][j] = 'X';
				}
			}
			if (i >= 8 && i <= 12) {
				if ((j >= 4 && j <= 9) || (j >= 30 && j <= 35))
					map[i][j] = 'X';
			}

			// left upper 'T'
			if (i >= 9 && i <= 16) {
				map[i][13] = 'X';
				if (i == 12) {
					if (j >= 13 && j <= 16)
						map[i][j] = 'X';
				}
			}

			// middle 'T'
			if (j >= 16 && j <= 23) {
				if (i == 9)
					map[i][j] = 'X';
			}
			if (j == 19 || j == 20) {
				if (i >= 10 && i <= 15)
					map[i][j] = 'X';
			}

			// right upper 'T'
			if (i >= 9 && i <= 16) {
				map[i][26] = 'X';
				if (i == 12) {
					if (j >= 23 && j <= 26)
						map[i][j] = 'X';
				}
			}

			// ghost box  i: 20->21 j: 12->25
			if (i == 19) {	// door = i: 19 j: 18,19,20,21
				if ((j >= 13 && j <= 17) || (j >= 22 && j <= 26))
					map[i][j] = 'X';
				if ((j > 17 && j < 22))
					map[i][j] = ' ';
			}
			if (i >= 20 && i <= 22) {
				if (j == 13 || j == 26)
					map[i][j] = 'X';
				else if (j > 13 && j < 26)
					map[i][j] = ' ';
				if (i == 22) {
					if (j >= 13 && j <= 26)
						map[i][j] = 'X';
				}
			}

			// second last line of wall
			if (i >= 14 && i <= 20)
			{
				if ((j >= 4 && j <= 9) || (j >= 30 && j <= 35))
					map[i][j] = 'X';
			}

			// last line of wall
			if (i >= 23 && i <= 26)
			{
				if ((j >= 4 && j <= 9) || (j >= 30 && j <= 35))
					map[i][j] = 'X';
			}

			// lower 'T'
			if (j >= 16 && j <= 23) {
				if (i == 26 || i == 25)
					map[i][j] = 'X';
			}
			if (j == 19 || j == 20) {
				if (i >= 27 && i <= 30)
					map[i][j] = 'X';
			}
		}
	}
}

int Map::countPelletsInitial() 
{
	int count = 0;
	for (int i = 0; i < map_rows; i++) {
		for (int j = 0; j < map_columns; j++) {
			if (map[i][j] == '.' || map[i][j] == 'O')
				count++;
		}
	}
	return count;
}

void Map::printMap()
{
	for (int i = 0; i < map_rows; i++) {
		for (int j = 0; j < map_columns; j++) {
			if (map[i][j] == 'X')
				SetConsoleTextAttribute(hConsole, 9);	// walls are blue
			else if (map[i][j] == '.' || map[i][j] == 'O')
				SetConsoleTextAttribute(hConsole, 7);	// pellets and energizers are  white
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Map::removePellet(int prev_x, int prev_y)
{
	if (map[prev_x][prev_y] != ' ') {
		count_pellets--; // subtracting number
	}
	map[prev_x][prev_y] = ' ';
}

int Map::getPelletCount() const
{
	return count_pellets;
}

void Map::removeEnergizer(int prev_x, int prev_y)
{
	if (map[prev_x][prev_y] == 'O') {
		count_pellets--;
	}
	map[prev_x][prev_y] = ' ';
	energizer_mode = true;
}

void Map::setPoints(int pt, int prev_x, int prev_y) 
{
	if (map[prev_x][prev_y] != ' ') {
		points += pt;
	}
}

int Map::getPoints() const 
{
	return points;
}

bool Map::isEnergizer(int i, int j) 
{
	if (map[i][j] == 'O') {
		return true;
	}
	else
		return false;
}

bool Map::isWall(int next_i, int next_j) {
	if (map[next_i][next_j] == 'X') {
		return true;
	}
	else
		return false;
}