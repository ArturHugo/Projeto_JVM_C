#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

#include <stdio.h>

#include "map.h"

MunitResult test_create_new_map() {
  Map* map = newMap();
  munit_assert_not_null(map);
  munit_assert_null(map->head);
  munit_assert_null(map->tail);
  free(map);
  return MUNIT_OK;
}

MunitResult test_add_to_empty_map() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);

  assert_string_equal("foo", map->head->key);
  assert_int(42, ==, *(int*) map->head->value);

  free(map);
  return MUNIT_OK;
}

MunitResult test_add_to_map() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);
  mapAdd(map, "bar", &value);

  assert_not_null(map->head->next);
  assert_string_equal("bar", map->tail->key);
  assert_int(42, ==, *(int*) map->tail->value);

  free((map)->head->next);
  free(map->head);
  free(map);
  return MUNIT_OK;
}

MunitResult get_non_existing_key() {
  Map* map = newMap();

  int* retrieved_value = mapGet(map, "foo");

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

  free(map);
  return MUNIT_OK;
}

MunitResult remove_key() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);

  int* removed_value = mapRemove(map, "foo");

  assert_int(value, ==, *removed_value);
  assert_null(map->head);

  free(map);
  return MUNIT_OK;
}

MunitResult remove_key_in_the_middle() {
  Map* map = newMap();

  int foo = 0;
  int bar = 1;
  int baz = 2;

  mapAdd(map, "foo", &foo);
  mapAdd(map, "bar", &bar);
  mapAdd(map, "baz", &baz);

  int* removed_value = mapRemove(map, "bar");

  assert_int(bar, ==, *removed_value);

  free(map);
  return MUNIT_OK;
}

MunitResult remove_non_existent_key() {
  Map* map = newMap();

  int value = 42;

  mapAdd(map, "foo", &value);

  int* retrieved_value = mapRemove(map, "bar");

  assert_null(retrieved_value);

  free(map);
  return MUNIT_OK;
}

MunitTest tests[] = {
    {"/new", test_create_new_map, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/empty_add", test_add_to_empty_map, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/add", test_add_to_map, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/get_null", get_non_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/get_existing", get_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/remove", remove_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/remove_middle", remove_key_in_the_middle, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/remove_nll", remove_non_existent_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/map",                 /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char* argv[]) { return munit_suite_main(&suite, NULL, argc, argv); }
