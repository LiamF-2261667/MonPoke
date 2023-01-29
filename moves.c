#include "stdbool.h"
#include "text.h"
#include "moves.h"


typedef struct Move {
    char* name;
    int actionCost;
    void (*effect)(const void*, const void*);
} Move;


typedef struct setNode {
    Move* currMove;
    struct setNode* prevNode;
    struct setNode* nextNode;
} setNode;


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


/* Create a new move with its attributes */
Move* createMove(char* name, int actionCost, void (*effect)(const void*, const void*)) {
    Move* newMove = malloc(sizeof(Move));
    if (newMove == NULL) {
        #ifdef DEBUG
        printf("ERROR: Allocating Move!\n");
        #endif
        return newMove;
    }
    newMove->name = name;
    newMove->actionCost = actionCost;
    newMove->effect = effect;

    return newMove;
}


/* Remove a move from the heap */
void removeMove(Move* move) {
    free(move);
}


/* 
    Execute a move 
    Returns bool: if move succesfully executed
*/
bool execMove(const Move* move, Entity* src, Entity* tar, const bool showInfo) {
    if (src->currActions < move->actionCost) {
        if (showInfo) {
            printf("Not enough action points!\n");
            waitForInput();
        }
        return false;
    }

    src->currActions -= move->actionCost;

    printf("%s used %s!\n", src->name, move->name);
    move->effect(src, tar);
    
    waitForInput();

    return true;
}


/* return the aphabetical order of 2 movies */
int cmpMoveNodes(const setNode* node1, const setNode* node2) {
    return strcmp(node1->currMove->name, node2->currMove->name);
}


/* Add a move sorted inside a moveset*/
void addMoveToSet(setNode** MoveSet, Move* move) {
    setNode* newNode = malloc(sizeof(setNode));
    if (newNode == NULL) {
        #ifdef DEBUG
        printf("ERROR: Allocating newNode");
        #endif
        return;
    }

    // Initializing variables
    newNode->currMove = move;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;

    // Adding the move to the set
    if (*MoveSet == NULL) { /* Create a new moveset */
        newNode->currMove = move;
        *MoveSet = newNode;

        return;
    }

    // Add node sorted in linked list
    setNode* prev = NULL;
    setNode* next = *MoveSet;

    // Go over all nodes untill the right position is found
    while (next != NULL && cmpMoveNodes(newNode, next) > 0) {
        prev = next;
        next = next->nextNode;
    }

    if (prev == NULL) { /* Add in front */
        newNode->nextNode = next;
        next->prevNode = newNode;
        *MoveSet = newNode;
    }

    else if (next == NULL) { /* Add behind */
        prev->nextNode = newNode;
        newNode->prevNode = prev;
    }

    else { /* Add inbetween */
        prev->nextNode = newNode;
        newNode->prevNode = prev;
        newNode->nextNode = next;
        next->prevNode = newNode;
    }
}


/* Get a setNode by it's count */
setNode* getNodeByCount(setNode* MoveSet, const int count) {
    for (int i = 1; i < count; i++) {
        if (MoveSet == NULL) {
            #ifdef DEBUG
            printf("ERROR: Trying to get move that doesn't exist!\n");
            #endif
            return NULL;
        }
        MoveSet = MoveSet->nextNode;
    }

    return MoveSet;
}


/* remove a node from a moveset */
void removeNodeFromMoveset(setNode** MoveSet, setNode* node) {
    setNode* prev = node->prevNode;
    setNode* next = node->nextNode;

    free(node);

    if (prev == NULL) { /* removed first node */
        next->prevNode = NULL;
        *MoveSet = next;
    }
    else if (next == NULL) { /* removed last node */
        prev->nextNode = NULL;
    }
    else { /* Removed node inbetween */
        prev->nextNode = next;
        next->prevNode = prev;
    }
}


/* Removes a moveset from the heap */
void removeMoveset(setNode** MoveSet) {
    setNode* curr = *MoveSet;
    while (curr != NULL) {
        setNode* next = curr->nextNode;
        free(curr);
        curr = next;
    }
    *MoveSet = NULL;
}


/* Return the amount of nodes inside a moveset */
int getMovesetSize(setNode* MoveSet) {
    int count = 0;
    while(MoveSet != NULL) {
        count++;
        MoveSet = MoveSet->nextNode;
    }

    return count;
}


/* Print a moveset in a neat way */
void printMoveset(const setNode* MoveSet) {
    int moveCount = 1;
    printf("+---------------------\n");

    while (MoveSet != NULL) {
        printf("| %d: %s [%d]\n", moveCount, MoveSet->currMove->name, MoveSet->currMove->actionCost);
        MoveSet = MoveSet->nextNode;
        moveCount++;
    }
    
    printf("+---------------------\n");
}