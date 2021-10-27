#pragma once
typedef struct Entity {
  int done;
  void* object;
  int  (*update)(void*);
  void (*render)(void*);
  void (*unload)(void*);
  struct Entity* prev;
  struct Entity* next;
} Entity;

Entity* EntityAdd(void*, int(*)(void*), void(*)(void*), void(*)(void*), Entity*);
void EntityUpdateAll(Entity*);
void EntityRenderAll(Entity*);
void EntityUnloadAll(Entity*);
void EntityUnload(Entity*);
void EntityUnloadDone(Entity*);
