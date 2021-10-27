#include "entity.h"
#include <stdlib.h>

typedef struct Fighter {
  int hp;
} Fighter;

Fighter* FighterNew() {
  Fighter* f = malloc(sizeof(Fighter));
  f->hp = 3;
  return f;
}

int FighterUpdate (void* object) {
  Fighter* f = object;
  return f->hp--;
}

void FighterRender (void* object) {
  // no graphics for now :-(
}

void FighterUnload (void* object) {
  free(object);
}

int main(void) {
  Fighter* f = FighterNew();
  Entity* entities =
    EntityAdd(f, FighterUpdate, FighterRender, FighterUnload, NULL);

  while (1) {
    EntityUpdateAll(entities);
    EntityUnloadDone(entities);
    EntityRenderAll(entities);
  }
  // unload any remaining entities
  EntityUnloadAll(entities);

  return 0;
}
