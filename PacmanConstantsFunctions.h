#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "PacmanMap.h"
using namespace std;

const int map_rows = 30; // length of maze
const int map_columns = 40; // width of maze
const int pacman_x = 20; // initial (x,y) location of pacman
const int pacman_y = 24;
const int ghost1_x = 19; // initial (x,y) location of inky (ghost1)
const int ghost1_y = 21;
const int ghost2_x = 20; // initial (x,y) location of blinky (ghost2)
const int ghost2_y = 19;
const int ghost_speed = 10; // to slow down the ghosts
bool energizer_mode = false; // to set the energizer mode of the game
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void lifeLost(int& lives) {
	system("cls");
	Sleep(1500);
	cout << "\n\nLives left: " << --lives;
	Sleep(1500);
	system("cls");
}

void instructions() {
	system("cls");
	cout << "How to play:" << endl;
	cout << "\nArrow keys control Pacman";
	cout << "\nAvoid Ghosts";
	cout << "\nEating pellets = +1 score";
	cout << "\nEating ghosts (in energizer mode) = +10 score";
	cout << "\n\nYou win if you eat all the pellets";
	cout << "\n\nYou lose if you run out of 3 lives";
	_getch();
	system("cls");
}

void startMenu() {
	int choice;
	do {
		Sleep(1000);
		cout << "\n\n\n\nWelcome to\n";
		Sleep(1500);
		SetConsoleTextAttribute(hConsole, 14);
		cout << "                   PACMAN!\n\n";
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(1000);
		cout << "[1] Start  [2] Instructions  [3] Exit\n\n";
		do {
			cout << "Enter number: ";
			cin >> choice;
		} while (choice < 1 || choice > 3);	// validation
		if (choice == 2) {
			instructions();
		}
		else if (choice == 3) {
			exit(0);
		}
	} while (choice != 1);
	system("cls");
}

void gameOver() {
	system("cls");
	cout << "\n\nGAME OVER\n\n";
	Sleep(1500);
}

void setCord(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}