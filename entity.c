#include "entity.h"
#include <stdlib.h>

Entity* EntityAdd(void* object, int (*update)(void*), void (*render)(void*), void (*unload)(void*), Entity* head) {
  Entity* e = malloc(sizeof(Entity));
  e->done = 0;
  e->update = update;
  e->render = render;
  e->unload = unload;
  if (head) {
    head->prev = e;
    e->next = head;
  }
  return e;
}
void EntityUpdateAll(Entity* head) {
  while (head) {
    head->done = head->update(head);
    head = head->next;
  }
}

void EntityRenderAll(Entity* head) {
  while (head) {
    head->render(head);
    head = head->next;
  }
}

void EntityUnloadAll(Entity* head) {
  while (head) {
    Entity* n = head->next;
    EntityUnload(head);
    head = n;
  }
}

void EntityUnload(Entity* e) {
  if (e->prev) {
    e->prev->next = e->next;
  }
  if (e->next) {
    e->next->prev = e->prev;
  }
  e->unload(e);
  free(e);
}

void EntityUnloadDone(Entity* head) {
  while (head) {
    if (head->done) {
      Entity* n = head->next;
      EntityUnload(head);
      head = n;
    } else {
      head = head->next;
    }
  }
}
