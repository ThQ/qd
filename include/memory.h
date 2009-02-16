#ifndef MEMORY_H

#include <cstdlib>

#define MALLOC(size) malloc((size))
#define REALLOC(pointer, new_size) realloc((pointer), (new_size))

#endif
