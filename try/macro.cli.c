
// cpp macro definitions have constant names. Hence, we can not synthesize a name for definition.

// -> macro1 is defined to equal an identifier "macro2_t0"
// -> a second macro is defined using the name "macro2_t0",
//
// which of these happens?
//   1) macro2 be expanded and its result placed into the definition of macro1
//   2) macro1 expands where it is invoked, and if that exanded content contains a call to macro2, then macro2 is expanded.  Etc.
//
// This test shows that macro2 is never expanded as part of the definition of macro1, no matter what order the definitions
// occur in, even when there are cascading macro calls (against conventional wisdom).  Hence, it is always the second
// case.

// in the macro CAT_1 C and D are not expanded before the concatenation
// in the macro CAT A and B as arguments aare expanded before being passed to CAT_1
#define CAT_1(C ,D) C ## D
#define CAT(A, B) CAT_1(A, B)

#define ECHO_1(A) A
#define ECHO(A) ECHO_1(A)

#include "stdio.h"

int main(){

  #define macro2_t0 12
  #define macro1_t0 macro2_t0
  printf("macro2 first, macro1_t0 expands to:%d\n" ,macro1_t0);
  #undef macro2_t0
  #define macro2_t0 24
  printf("macro2 first, then redefined after, macro1_t0 expands to:%d\n" ,macro1_t0);

  #define macro1_t1 macro2_t1
  #define macro2_t1 112
  printf("macro2 second, macro1_t1 expands to:%d\n" ,macro1_t1);
  #undef macro2_t1
  #define macro2_t1 224
  printf("macro2 second, then redefined after, macro1_t1 expands to:%d\n" ,macro1_t1);

  #define macro2_t2 1112
  #define macro1_t2 ECHO(macro2_t2)
  printf("macro2 first, macro1_t2 with ECHO expands to:%d\n" ,macro1_t2);
  #undef macro2_t2
  #define macro2_t2 2224
  printf("macro2 first, then redefined after, macro1_t2 with ECHO expands to:%d\n" ,macro1_t2);

  #define macro1_t3 CAT(macro2_t3,5)
  #define macro2_t3 5
  printf("macro2 second, macro1_t3 with CAT expands to:%d\n" ,macro1_t3);
  #undef macro2_t3
  #define macro2_t3 15
  printf("macro2 first, then redefined after, macro1_t3 with ECHO expands to:%d\n" ,macro1_t3);

}

/*
2022-02-07T21:04:03Z
Morpheus@Turbine§/home/Morpheus/projects/plato/projects/tunnel§
> ./macro
macro2 first, macro1_t0 expands to:12
macro2 first, then redefined after, macro1_t0 expands to:24
macro2 second, macro1_t1 expands to:112
macro2 second, then redefined after, macro1_t1 expands to:224
macro2 first, macro1_t2 with ECHO expands to:1112
macro2 first, then redefined after, macro1_t2 with ECHO expands to:2224
macro2 second, macro1_t3 with CAT expands to:55
macro2 first, then redefined after, macro1_t3 with ECHO expands to:155
*/ 
