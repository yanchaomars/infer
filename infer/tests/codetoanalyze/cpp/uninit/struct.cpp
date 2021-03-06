/*
 * Copyright (c) 2017 - present Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include <string>

struct SimpleRuleKey {
  std::string value;
  int i;
};

struct s {
  int n;
  int b;
  std::string s;
};

struct s t4; // global struc are init by default

std::string struct_init_ok() {
  SimpleRuleKey srk{};
  std::string s1;
  s1 = srk.value; // srk has been initialized

  return s1;
}

std::string struct_uninit_ok() {
  SimpleRuleKey srk;
  std::string s1;
  s1 = srk.value; // srk has not been initialized, but value has type string and
                  // therefore it is initialized by default

  return s1;
}

int FN_struct_uninit() {
  int k;
  SimpleRuleKey srk;
  k = srk.i; // Should reports here: srk was not initialized and i has type int
             // so it's not initialized by default
  return k;
}

int struct_partially_init_ok() {

  struct s t1 = {0}; // partially initialized
  int j;
  j = t1.b; // when partially initialized, automatically other fields get
            // initilized

  return j;
}

int global_struct_ok() {

  int j;
  j = t4.n; // global struct are initilized by default

  return j;
}

void init_struct(struct s*);

int call_init_struct_ok() {
  struct s t;
  init_struct(&t);

  return t.n;
}

struct s init_all_fields(void);

int init_field_via_function_ok() {

  struct s t;

  t = init_all_fields();
  return t.n;
}

int init_field_via_function_ptr_ok() {

  struct s* t;

  *t = init_all_fields();
  return t->n;
}

enum class FieldType : uint8_t {
  Stop = 0x0,
  True = 0x1,
  False = 0x2,
  Int8 = 0x3,
  Int16 = 0x4,
  Int32 = 0x5,
  Int64 = 0x6,
  Double = 0x7,
  Binary = 0x8,
  List = 0x9,
  Set = 0xa,
  Map = 0xb,
  Struct = 0xc,
  Float = 0xd
};

class C {
  int a, b;

 public:
  std::pair<FieldType, int> read_values();
};

int use_C(C& c) {
  const auto pr = c.read_values();

  return pr.second;
}

struct s not_a_constructor_but_returning_T(void);

int foo() {
  struct s t = not_a_constructor_but_returning_T();
  return t.n;
}
