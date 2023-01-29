#include "text.h"
#include "game.h"
#include <stdio.h>


#define MAX_NAME_LENGHT 100


int main() {
	printPrewritten("logo");
	waitForInput();
	clearScreen();

	char playerName[MAX_NAME_LENGHT];
	printPrewritten("intro text 1");

	fgets(playerName, MAX_NAME_LENGHT - 1, stdin);
	for (int i = 0; i < MAX_NAME_LENGHT; i++)
		if (playerName[i] == '\n')
			playerName[i] = '\0';
	
	printPrewritten("intro text 2");
	waitForInput();

	startGame(playerName);

	clearScreen();
	printf("Closing game...\n");

	return 0;
}