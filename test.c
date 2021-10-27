#include <stdio.h>
#include "minunit.h"
#include "entity.h"

int tests_run = 0;
int entityUpdateCallCount;
int entityRenderCallCount;
int entityUnloadCallCount;
int done = 0;

int TestEntityUpdate (void* object) {
  entityUpdateCallCount++;
  return done;
}

void TestEntityRender (void* object) {
  entityRenderCallCount++;
}

void TestEntityUnload (void* object) {
  entityUnloadCallCount++;
}

Entity* TestAddEntity(Entity* e) {
  return EntityAdd(NULL, TestEntityUpdate, TestEntityRender, TestEntityUnload, e);
}

void TestCleanup(Entity* e) {
  EntityUnloadAll(e);
}

static char* test_EntityAdd() {
  Entity *e1 = TestAddEntity(NULL);
  mu_assert("EntityAdd returns an entity", e1 != NULL);
  mu_assert("Head prev is null", e1->prev == NULL);
  mu_assert("Head next is null", e1->next == NULL);
  Entity *e2 = TestAddEntity(e1);
  mu_assert("EntityAdd returns new head", e2 != NULL);
  mu_assert("Head prev is null", e2->prev == NULL);
  mu_assert("Head next is tail", e2->next == e1);
  mu_assert("Tail prev is head", e1->prev == e2);
  mu_assert("Tail next is null", e1->next == NULL);
  Entity *e3 = TestAddEntity(e2);
  mu_assert("EntityAdd returns new head", e3 != NULL);
  mu_assert("Head prev is null", e3->prev == NULL);
  mu_assert("Head next is body", e3->next == e2);
  mu_assert("Body prev is head", e2->prev == e3);
  mu_assert("Body next is tail", e2->next == e1);
  mu_assert("Tail prev is body", e1->prev == e2);
  mu_assert("Tail next is null", e1->next == NULL);
  TestCleanup(e3);
  return 0;
}

static char* test_EntityUpdateAll() {
  entityUpdateCallCount = 0;
  Entity *e1 = TestAddEntity(NULL);
  Entity *e2 = TestAddEntity(e1);
  Entity *e3 = TestAddEntity(e2);
  EntityUpdateAll(e3);
  mu_assert("EntityUpdate calls TestEntityUpdate", entityUpdateCallCount == 3);
  TestCleanup(e3);
  return 0;
}

static char* test_EntityUpdateAllDone() {
  done = 1;
  entityUpdateCallCount = 0;
  Entity *e1 = TestAddEntity(NULL);
  Entity *e2 = TestAddEntity(e1);
  Entity *e3 = TestAddEntity(e2);
  EntityUpdateAll(e3);
  mu_assert("EntityUpdate calls TestEntityUpdate", entityUpdateCallCount == 3);
  mu_assert("EnittyUpdateAll marks entity 1 done", e1->done == 1);
  mu_assert("EnittyUpdateAll marks entity 2 done", e2->done == 1);
  mu_assert("EnittyUpdateAll marks entity 3 done", e3->done == 1);
  TestCleanup(e3);
  return 0;
}

static char* test_EntityRenderAll() {
  entityRenderCallCount = 0;
  Entity *e1 = TestAddEntity(NULL);
  Entity *e2 = TestAddEntity(e1);
  Entity *e3 = TestAddEntity(e2);
  EntityRenderAll(e3);
  mu_assert("EntityRender calls TestEntityRender", entityRenderCallCount == 3);
  TestCleanup(e3);
  return 0;
}

static char* test_EntityUnloadAll() {
  entityUnloadCallCount = 0;
  Entity *e1 = TestAddEntity(NULL);
  Entity *e2 = TestAddEntity(e1);
  Entity *e3 = TestAddEntity(e2);
  EntityUnloadAll(e3);
  mu_assert("EntityUnload calls TestEntityUnload", entityUnloadCallCount == 3);
  return 0;
}

static char* test_EntityUnloadDone() {
  entityUnloadCallCount = 0;
  Entity *e1 = TestAddEntity(NULL);
  Entity *e2 = TestAddEntity(e1);
  Entity *e3 = TestAddEntity(e2);
  e2->done = 1;
  EntityUnloadDone(e3);
  mu_assert("EntityUnloadDone calls TestEntityUnload once", entityUnloadCallCount == 1);
  mu_assert("Head prev is null", e3->prev == NULL);
  mu_assert("Head next is tail", e3->next == e1);
  mu_assert("Tail prev is head", e1->prev == e3);
  mu_assert("Tail next is null", e1->next == NULL);
  TestCleanup(e3);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_EntityAdd);
  mu_run_test(test_EntityUpdateAll);
  mu_run_test(test_EntityUpdateAllDone);
  mu_run_test(test_EntityRenderAll);
  mu_run_test(test_EntityUnloadAll);
  mu_run_test(test_EntityUnloadDone);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
      printf("%s\n", result);
  } else {
      printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
