#include "text.h"
#include "entity.h"
#include "moves.h"
#include "moveFx.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


#define MAX_MOVES 3
const enum moveId { Scratch, Heal, WeetIkVeel, EetIkVeel, Swap } moveId;


/* Declare all moves in the game */
void declareMoves(Move* moves[]) {
    moves[Scratch] = createMove("Scratch", 1, scratchFx);
    moves[Heal] = createMove("Heal", 2, healFx);
    moves[WeetIkVeel] = createMove("Weet Ik Veel", 2, weetIkVeelFx);
    moves[EetIkVeel] = createMove("Eet Ik Veel", 2, eetIkVeelFx);
    moves[Swap] = createMove("Swap", 2, swapFx);
}


/* Remove all declared moves */
void removeAllMoves(Move* moves[]) {
    for (int i = 0; i < MAX_MOVES; i++) {
        removeMove(moves[i]);
    }
}


/* Clear the screen and display current gamestate */
void updateGameState(Entity* pl, Entity* enemy, const bool enemyTurn) {
    clearScreen();

    printPrewritten("battle");

    printEntity(enemy, false);
    printPrewritten("enemy");

    printEntity(pl, !enemyTurn);
}


/* End the game and show win/loss screen */
void endGame(bool playerWon) {
    clearScreen();

    if (playerWon)
        printPrewritten("victory");
    else
        printPrewritten("defeat");

    waitForInput();
}


/* End the game if it should, otherwise return false */
bool shouldGameEnd(Entity* pl, Entity* enemy) {
    // Decide if the game needs to end
    if (pl->currHp <= 0) {
        endGame(false);
        return true;
    }
    else if (enemy->currHp <= 0) {
        endGame(true);
        return true;
    }

    return false;
}


/* 
    Everything that happens during the player's turn
    returns true if game needs to end after
*/
bool execPlayerTurn(Entity* pl, Entity* enemy, Move* moves[]) {
    pl->currActions = pl->maxActions;
    enemy->currActions = enemy->maxActions;

    updateGameState(pl, enemy, false);
    
    while (pl->currActions > 0) {
        // Get the move
        printf("Choose a move...\n");
        char action = getch();
        int moveCount = action - '0';

        Move* move = getNodeByCount(pl->moveset, moveCount)->currMove;
        if (move == NULL) { /* Invalid move given */
            printf("That isn't a valid move, try again!\n");
            waitForInput();
            updateGameState(pl, enemy, false);
            continue;
        }

        if (execMove(move, pl, enemy, true)) {
            if (shouldGameEnd(pl, enemy))
                return true;

            if (pl->currActions > 0)
                updateGameState(pl, enemy, false);
        }
        else { /* If the move didn't execute */
        }
    }

    return false;
}


/* 
    Everything that happens during the enemy's turn
    returns true if game needs to end after
*/
bool execEnemyTurn(Entity* pl, Entity* enemy, Move* moves[]) {
    updateGameState(pl, enemy, true);

    while (enemy->currActions > 0) {
        // generate random attack from moveset
        srand(time(NULL));
        const int MIN = 1;
        const int MAX = getMovesetSize(enemy->moveset);
        int moveCount = MIN + rand() % MAX;

        Move* move = getNodeByCount(enemy->moveset, moveCount)->currMove;
        if (move == NULL) /* Invalid move given */
            continue;

        if (execMove(move, enemy, pl, false)) {
            if (shouldGameEnd(pl, enemy))
                return true;
            
            if (enemy->currActions > 0)
                updateGameState(pl, enemy, true);
        }
        else { /* If the move didn't execute */
        }
    }

    return false;
}


/* The main game loop */
void gameLoop(Entity* pl, Entity* enemy, Move* moves[], bool enemyTurn) {
    if (enemyTurn == false)
        if (execPlayerTurn(pl, enemy, moves))
            return;
    else
        if (execEnemyTurn(pl, enemy, moves))
            return;

    if (shouldGameEnd(pl, enemy))
        return;

    // Otherwise, continue the loop
    enemyTurn = !enemyTurn;
    gameLoop(pl, enemy, moves, enemyTurn);
}


/* Start the main game loop */
void startGame(char* playerName) {
    // declaring variables
    Move* moves[MAX_MOVES];
    declareMoves(moves);

	setNode* Moveset = NULL;
	addMoveToSet(&Moveset, moves[Scratch]);
	addMoveToSet(&Moveset, moves[Heal]);
	addMoveToSet(&Moveset, moves[WeetIkVeel]);
	addMoveToSet(&Moveset, moves[EetIkVeel]);
	addMoveToSet(&Moveset, moves[Swap]);

	Entity* enemy = createEntity("Not Bulbasaur", Moveset, 20, 3);
	Entity* pl = createPlayer(playerName, Moveset);

    // starting game
    gameLoop(pl, enemy, moves, false);

    // clearing the heap
	removeMoveset(&Moveset);
    removeAllMoves(moves);
	removeEntity(&enemy);
	removeEntity(&pl);
}