#include "entity.h"
#include <time.h>
#include <stdlib.h>


/* effect for the scratch move */
void scratchFx(const void* src_, const void* tar_) {
    const int SCRATCH_DMG = 4;

    Entity* src = (Entity*)src_;
    Entity* tar = (Entity*)tar_;

    tar->currHp -= SCRATCH_DMG;
    printf("%s got scratched and took %d damage!\n", tar->name, SCRATCH_DMG);
}


/* effect for the heal move */
void healFx(const void* src_, const void* tar_) {
    const int HEAL_AMOUNT = 6;

    Entity* src = (Entity*)src_;
    Entity* tar = (Entity*)tar_;
    
    src->currHp += HEAL_AMOUNT;
    if (src->currHp > src->maxHp)
        src->currHp = src->maxHp;

    printf("%s said some magic words and healed for %d hp!\n", src->name, HEAL_AMOUNT);
}


/* effect for the weetIkVeel move */
void weetIkVeelFx(const void* src_, const void* tar_) {
    const int MIN = 1;
    const int MAX = 5;

    Entity* src = (Entity*)src_;
    Entity* tar = (Entity*)tar_;
    
    srand(time(NULL));
    int dmg = MIN + rand() % MAX;
    int heal = MIN + rand() % MAX;

    tar->currHp -= dmg;
    src->currHp += heal;
    
    if (src->currHp > src->maxHp)
        src->currHp = src->maxHp;

    printf("%s randomly took %d damage, because %s didn't know much!\n", tar->name, dmg, src->name);
    printf("%s randomly healed for %d hp aswell!\n", src->name, heal);
}


/* effect for the weetIkVeel move */
void eetIkVeelFx(const void* src_, const void* tar_) {
    const int MIN = 5;
    const int MAX = 10;

    Entity* src = (Entity*)src_;
    Entity* tar = (Entity*)tar_;

    srand(time(NULL));
    int heal = MIN + rand() % MAX;

    int healthDiff = src->maxHp - src->currHp;

    if (heal > healthDiff) {
        src->currHp -= heal - healthDiff;
        printf("%s ate to much and took %d damage!\n", src->name, heal - healthDiff);
    }
    else {
        src->currHp += heal;
        printf("%s had a good meal and healed for %d hp!\n", src->name, heal);
    }
}


/* effect for the weetIkVeel move */
void swapFx(const void* src_, const void* tar_) {
    Entity* src = (Entity*)src_;
    Entity* tar = (Entity*)tar_;

    setNode* swap = src->moveset;
    src->moveset = tar->moveset;
    tar->moveset = swap;

    printf("%s and %s magicly swapped movesets!\n", src->name, tar->name);
}