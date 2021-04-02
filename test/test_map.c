#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

#include <stdio.h>

#include "map.h"

MunitResult get_non_existing_key() {
  Map* map   = newMap();
  int  value = 42;

  mapAdd(map, "foo", &value);

  int* retrieved_value = mapGet(map, "bar");

  assert_null(retrieved_value);

  free(map);
  return MUNIT_OK;
}

MunitResult get_existing_key() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);

  int* retrieved_value = mapGet(map, "foo");

  assert_int(value, ==, *retrieved_value);

  mapFree(map);
  return MUNIT_OK;
}

MunitResult remove_entry() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);

  int* removed_value = mapRemove(map, "foo");

  assert_int(value, ==, *removed_value);

  mapFree(map);
  return MUNIT_OK;
}

MunitResult remove_null() {
  Map* map   = newMap();
  int  value = 42;

  mapAdd(map, "foo", &value);
  mapRemove(map, "foo");

  assert_null(mapRemove(map, "foo"));

  mapFree(map);
  return MUNIT_OK;
}

MunitResult set_new_value() {
  Map* map   = newMap();
  int  value = 42;

  void* old_value = mapSet(map, "foo", &value);

  assert_null(old_value);
  assert_int(42, ==, *(int*) mapGet(map, "foo"));

  mapFree(map);
  return MUNIT_OK;
}

MunitResult resize() {
  Map* map = _newMap(3);

  int foo = 1;
  int bar = 2;
  int baz = 3;
  int seg = 4;

  mapAdd(map, "foo", &foo);
  mapAdd(map, "bar", &bar);
  mapAdd(map, "baz", &baz);
  mapAdd(map, "seg", &seg);

  assert_short(3, !=, map->table_size);

  assert_int(foo, ==, *(int*) mapGet(map, "foo"));
  assert_int(bar, ==, *(int*) mapGet(map, "bar"));
  assert_int(baz, ==, *(int*) mapGet(map, "baz"));
  assert_int(seg, ==, *(int*) mapGet(map, "seg"));

  mapFree(map);
  return MUNIT_OK;
}

MunitTest tests[] = {{"/get_null", get_non_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/get_existing", get_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/remove_entry", remove_entry, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/remove_null", remove_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/set_new", set_new_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/resize", resize, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/map",                 /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char* argv[]) { return munit_suite_main(&suite, NULL, argc, argv); }
