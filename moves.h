#ifndef moves_H
#define moves_H

#include "moves.c"
#include "entity.h"

Move* createMove(char* name, int actionCost, void (*effect)(const void*, const void*));
bool execMove(const Move* move, Entity* src, Entity* tar, const bool showInfo);
void addMoveToSet(setNode** MoveSet, Move* move);
setNode* getNodeByCount(setNode* MoveSet, const int count);
void removeNodeFromMoveset(setNode** MoveSet, setNode* node);
void removeMoveset(setNode** MoveSet);
int getMovesetSize(setNode* MoveSet);
void printMoveset(const setNode* MoveSet);

#endif
