#include <iostream>
#include <windows.h>
#include <conio.h>

#include "PacmanMap.h" // making and printing and maintaining the map
#include "PacmanLocation.h" // stores x,y of a character
#include "PacmanCharacters.h" // base & derived classes of pacman and the ghosts
#include "PacmanConstantsFunctions.h"
using namespace std;

/*  TO DO:
	print map, position of pacman [DONE] and ghosts [DONE]
	movement of pacman [DONE] and ghosts [DONE] 
	hardcoded position of energizer [DONE]

	rules:
		-pacman and ghost collide -> lives-- [DONE]
		-screen pause, show lives getting subtracted and pacman returned to initial pos [DONE]
		-eat pellets -> points++ [DONE]
		-eat ghosts -> ponts+=10 [DONE]

	pacman:
		-eating pellets (dots) (turns to space) [DONE] (total no = 0 then game_over) [DONE]
		-eating energizer (turns to space) (ability to eat ghosts) [DONE]
		-not being able to overwrite walls (X) [DONE]
*/

int main() {

	int m = pacman_x, n = pacman_y;	// position on screen
	int i_prev = pacman_y, j_prev = pacman_x; // position in array
	int frame_count = 0, frame_count_energizer = 0;
	double energizer_timer = 300;
	int lives = 3;\

	Map map; // objects of the game
	Pacman pacman(m , n);	
	Ghost inky(ghost1_x, ghost1_y), blinky(ghost2_x, ghost2_y); // "Inky" and "Blinky" the Ghosts

	// DISPLAY START MENU
	startMenu();

	while (1) { // MAIN GAME LOOP

		map.printMap();

		// TEXT AT BOTTOM OF THE SCREEN
		SetConsoleTextAttribute(hConsole, 7);
		setCord(0, 35);
		cout << "Score: " << map.getPoints() << "\tLives: " << lives;
		if (energizer_mode)
			cout << endl << "~~~ENERGIZER MODE~~~";

		// SETTING PACMAN
			pacman.setCharacter(m, n, 14);

		// SETTING GHOSTS
	
			if (frame_count <= 40) {
				inky.leaveBox(map, frame_count, 11);
				blinky.leaveBox(map, frame_count, 12);
			}
			else {
				inky.moveRandom(map, frame_count);
				blinky.directPursuit(map, pacman, frame_count);
			}

		// ENERGIZER MODE
			if (frame_count_energizer == energizer_timer) {	// check if time is up for energizer mode
				if (inky.isLocation(ghost1_x, ghost1_y))
					inky.leaveBox(map, frame_count, 11);
				if (blinky.isLocation(ghost2_x, ghost2_y))
					blinky.leaveBox(map, frame_count, 12);
				energizer_mode = false; // end energizer mode
				frame_count_energizer = 0; // reset frame count for energizer mode
			}
			else if (energizer_mode == true && frame_count_energizer > 0 && frame_count_energizer < energizer_timer) {	// if not, then the ghosts continue to move randomly(if they are not already caught
				if (!(inky.isLocation(ghost1_x, ghost1_y)))
					inky.moveRandom(map, frame_count);
				if (!(blinky.isLocation(ghost2_x, ghost2_y)))
					blinky.moveRandom(map, frame_count);
			}
		
		// CONTROLS
		if (GetAsyncKeyState(VK_UP))  // move upward
		{
			if (!map.isWall(n - 1, m)) {
				if (map.isEnergizer(i_prev, j_prev)){
					map.removeEnergizer(i_prev, j_prev);
				}
				map.setPoints(1, i_prev, j_prev);
				map.removePellet(i_prev, j_prev); // remove pellet at pacman's pos
				n--;
				i_prev--;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT))  // move left
		{
			if (!map.isWall(n, m - 1)) {
				if (map.isEnergizer(i_prev, j_prev)){
					map.removeEnergizer(i_prev, j_prev);
				}
				map.setPoints(1, i_prev, j_prev);
				map.removePellet(i_prev, j_prev); // remove pellet at pacman's pos
				m--;
				j_prev--;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))    // move right
		{
			if (!map.isWall(n, m + 1)) {
				if (map.isEnergizer(i_prev, j_prev)){
					map.removeEnergizer(i_prev, j_prev);
				}
				map.setPoints(1, i_prev, j_prev);
				map.removePellet(i_prev, j_prev); // remove pellet at pacman's pos
				m++;
				j_prev++;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))   //move downward
		{
			if (!map.isWall(n + 1, m)) {
				if (map.isEnergizer(i_prev, j_prev)){
					map.removeEnergizer(i_prev, j_prev);
				}
				map.setPoints(1, i_prev, j_prev);
				map.removePellet(i_prev, j_prev); // remove pellet at pacman's pos
				n++;
				i_prev++;
			}
		}
		frame_count++;

		// NORMAL MODE
		if (!energizer_mode) {
			if (inky.caughtByGhost(pacman) || blinky.caughtByGhost(pacman))
			{
				lifeLost(lives);
				m = j_prev = pacman_x;
				n = i_prev = pacman_y;
				if (lives != 0) {
					pacman.setCharacter(m, n, 14);
					inky.setCharacter(ghost1_x, ghost1_y, 11);
					blinky.setCharacter(ghost2_x, ghost2_y, 12);
				}
			}
		}

		// ENERGIZER MODE
		if (energizer_mode) {
			if (inky.caughtByPacman(pacman, map)){
				inky.setCharacter(ghost1_x, ghost1_y, 11);
			}
			if (blinky.caughtByPacman(pacman, map)) {
				blinky.setCharacter(ghost2_x, ghost2_y, 12);
			}
			frame_count_energizer++; // keep timing of energizer mode
		}

		// CHECKING END OF THE GAME
		if (lives == 0)
		{
			gameOver();
			cout << "You Lost!\n\n";
			SetConsoleTextAttribute(hConsole, 7);
			exit(0);
		}
		else if(map.getPelletCount()==0)
		{
			gameOver();
			SetConsoleTextAttribute(hConsole, 10);
			cout << "You Won!\n\n";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "Total Score: " << map.getPoints() << endl << endl;
			SetConsoleTextAttribute(hConsole, 7);
			exit(0);
		}

		system("cls");
	}
}
