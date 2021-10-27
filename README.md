entity.h
--------
A minimalist entity management library, using a doubly linked list.

test.c
------
Run the test suite:

    make test

Check for memory leaks (requires valgrind):

    make mem

example.c
---------
You can use `entity.h` to manage all the entities in a game. Imagine we have a simple fighter class:

```c
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
```

We can call `EntityAdd` to add an object to an entity list. An entity can be any pointer, as long as it has update, render and unload methods.

```c
#include "entity.h"

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
```

Every frame the game updates all entities by calling `EntityUpdateAll`. This calls every entity's `update` method, passing the object as the argument. Any entity whose update returns zero is marked as "done". Then `EntityUnloadDone` unloads all complete entities. Separating update and unload allows entities all entities to behave as if they're updating at the same time. `EntityRenderAll` renders the entities. Finally once the game ends, any remaining entities are removed with `EntityUnloadAll`.

License
-------
Copyright 2021 David Farrell

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
