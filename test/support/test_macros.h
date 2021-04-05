#define create_test(test_fn)                                                                       \
  MunitResult test_##test_fn() {                                                                   \
    test_fn();                                                                                     \
    return MUNIT_OK;                                                                               \
  }

#define add_test(test_name)                                                                        \
  { "/" #test_name, test_##test_name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define create_suite(suite_name, tests)                                                            \
  static const MunitSuite suite = {"/" suite_name, tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};       \
  int main(int argc, char* argv[]) { return munit_suite_main(&suite, NULL, argc, argv); }
