#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "moves.h"


#define START_HP 10
#define START_ACTIONS 2


#ifndef Entity_s
#define Entity_s
typedef struct Entity {
    char* name;

    int currHp;
    int maxHp;

    int currActions;
    int maxActions;

    setNode* moveset;
} Entity;
#endif


/* Create a Player and fill it's components */
Entity* createPlayer(const char* name, setNode* moveset) {
    Entity* pl = malloc(sizeof(Entity));
    if (pl == NULL) {
        #ifdef DEBUG
        printf("ERROR: Allocating Entity struct!\n");
        #endif
        return pl;
    }

    // Setting up basic atributes
    pl->currHp = START_HP;
    pl->maxHp = START_HP;
    pl->currActions = START_ACTIONS;
    pl->maxActions = START_ACTIONS;
    pl->moveset = moveset;

    // Storing name on the heap
    char* plName = malloc(strlen(name) + 1); /* +1 for '\0' */
    if (plName == NULL) {
        #ifdef DEBUG
        printf("ERROR: Allocating Entity name!\n");
        #endif
        return pl;
    }

    strcpy(plName, name);
    pl->name = plName;

    return pl;
}


Entity* createEntity(const char* name, setNode* moveset, const int maxHp, const int maxActions) {
    Entity* e = createPlayer(name, moveset);

    e->currHp = maxHp;
    e->maxHp = maxHp;
    e->currActions = maxActions;
    e->maxActions = maxActions;

    return e;
}


/* Remove an Entity from the heap */
void removeEntity(Entity** e) {
    free((*e)->name);
    free(*e);
    *e = NULL;
}


/* Print all the Entity's attributes in a neat way */
void printEntity(Entity* e, bool showMoves) {
    printf("------======= ");
    printf("%s | HP = %d/%d | Actions = %d/%d", e->name, e->currHp, e->maxHp, e->currActions, e->maxActions);
    printf(" =======------\n\n");

    if (showMoves) {
        printMoveset(e->moveset);
    }
}