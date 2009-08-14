#ifndef UTIL__H
#define UTIL__H __FILE__

#include "Memory.h"

#define LOOP_FROM_TO(type, iter_var, init_value, max_value) for ( type iter_var = init_value; iter_var < max_value ; ++ iter_var)

#define NEW(VAR, KLASS) \
   LOG_MEMORY("NEW (.variable \"%s\", .class \"%s\", .sizeof %d)\n", (#VAR), (#KLASS), sizeof(KLASS));KLASS *VAR = new KLASS

#endif
