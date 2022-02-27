
// A and B are not macro expanded in CAT but they will be in the call to CAT_1
// see macro_test.c for an example
#define CAT_1(A ,B) A ## B
#define CAT(A, B) CAT_1(A, B)

#define NS_1(A ,B) A ## __ ## B
#define NS(name, ID) NS_1(name, ID)

// causes A to be macro expanded
#define ECHO(A) A

