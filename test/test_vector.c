#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>

#include "vector.h"

void it_creates_a_vector() {
  Vector* vec = newVector(10);
  assert_not_null(vec);
  freeVector(vec);
}

void it_inserts_two_elements() {
  Vector* vec = newVector(10);
  int     foo = 1;
  int     bar = 2;
  insert(vec, &foo);
  insert(vec, &bar);
  assert_int(foo, ==, *(int*) vec->array[0]);
  assert_int(bar, ==, *(int*) vec->array[1]);
  freeVector(vec);
}

void it_retrieves_element_at_index() {
  Vector* vec = newVector(10);
  for(int i = 0; i < 10; i++)
    insert(vec, (void*) (size_t) i);

  assert_int(5, ==, (size_t) get(vec, 5));
  assert_int(9, ==, (size_t) get(vec, -1));

  freeVector(vec);
}

void it_removes_an_element() {
  Vector* vec = newVector(10);

  int foo = 13;
  int bar = 17;

  insert(vec, &foo);
  insert(vec, &bar);

  assert_int(foo, ==, *(int*) pop(vec, 0));
  assert_int(bar, ==, *(int*) get(vec, 0));

  freeVector(vec);
}

void it_resizes_as_needed() {
  Vector* vec = newVector(2);

  int foo = 13;
  int bar = 17;

  insert(vec, &foo);
  insert(vec, &bar);

  assert_int(vec->length, ==, 2);

  insert(vec, &foo);
  insert(vec, &bar);

  assert_int(vec->length, ==, 4);

  freeVector(vec);
}

create_test(it_creates_a_vector);
create_test(it_inserts_two_elements);
create_test(it_retrieves_element_at_index);
create_test(it_removes_an_element);
create_test(it_resizes_as_needed);

MunitTest tests[] = {
    add_test(it_creates_a_vector),
    add_test(it_inserts_two_elements),
    add_test(it_retrieves_element_at_index),
    add_test(it_removes_an_element),
    add_test(it_resizes_as_needed),
};

create_suite("vector", tests);
