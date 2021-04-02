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

  free(map);
  return MUNIT_OK;
}

MunitTest tests[] = {{"/get_null", get_non_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/get_existing", get_existing_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/map",                 /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char* argv[]) { return munit_suite_main(&suite, NULL, argc, argv); }
