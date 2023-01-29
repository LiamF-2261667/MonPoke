#ifndef entity_H
#define entity_H

#include "entity.c"

Entity* createPlayer(const char* name, setNode* moveset);
Entity* createEntity(const char* name, setNode* moveset, const int maxHp, const int maxActions);
void removeEntity(Entity** e);
void printEntity(Entity* e, bool showMoves);

#endif
