#define create_test(test_fn)                                                                       \
  MunitResult test_##test_fn() {                                                                   \
    test_fn();                                                                                     \
    return MUNIT_OK;                                                                               \
  }

#define create_test_with_fixture(test_fn)                                                          \
  MunitResult test_##test_fn(const MunitParameter params[], void* fixture) {                       \
    if(params)                                                                                     \
      ((void) 0);                                                                                  \
    test_fn(fixture);                                                                              \
    return MUNIT_OK;                                                                               \
  }

#define create_skip(test_fn)                                                                       \
  MunitResult test_##test_fn() {                                                                   \
    test_fn();                                                                                     \
    return MUNIT_SKIP;                                                                             \
  }

#define add_test(test_name)                                                                        \
  { "/" #test_name, test_##test_name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define add_test_with_fixtures(test_name)                                                          \
  { "/" #test_name, test_##test_name, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL }

#define create_suite(suite_name, tests)                                                            \
  static const MunitSuite suite = {"/" suite_name, tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};       \
  int main(int argc, char* argv[]) { return munit_suite_main(&suite, NULL, argc, argv); }
