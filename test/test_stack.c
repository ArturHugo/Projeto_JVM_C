#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>

#include "stack.h"

void test() {
  int testSuccesfull = 1;

  typedef struct {
    u1    bytecode;
    char* mnemonic;
    u1    pc;
    u1    n_args;
  } test;

  test  i, i2;
  test* teste;

  char* mn   = "teste";
  i.bytecode = 42;
  i.mnemonic = mn;
  i.pc       = 42;
  i.n_args   = 4;

  char* mn2   = "teste2";
  i2.bytecode = 43;
  i2.mnemonic = mn2;
  i2.pc       = 43;
  i2.n_args   = 5;

  Node* list = NULL;

  pushNode(&list, &i);
  pushNode(&list, &i2);

  teste = peekNode(list);

  if(teste->bytecode != i2.bytecode || teste->n_args != i2.n_args || teste->pc != i2.pc) {
    testSuccesfull = 0;
  }

  teste = popNode(&list);
  if(teste->bytecode != i2.bytecode || teste->n_args != i2.n_args || teste->pc != i2.pc) {
    testSuccesfull = 0;
  }

  teste = popNode(&list);
  if(teste->bytecode != i.bytecode || teste->n_args != i.n_args || teste->pc != i.pc) {
    testSuccesfull = 0;
  }

  assert_not_null(testSuccesfull);
}

create_test(test);

MunitTest tests[] = {add_test(test)};

create_suite("stack", tests);
