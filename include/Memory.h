#ifndef MEMORY_H

#include <cstdlib>

#define MALLOC(size) malloc((size))
#define REALLOC(pointer, new_size) realloc((pointer), (new_size))

/**
 * A way of abstracting memory management.
 */
class Memory
{
   public: inline static void* free(void* ptr)
   {
      return free(ptr);
   }

   public: inline static void* malloc(size_t size)
   {
      return malloc(size);
   }

   public: inline static void* realloc(void* ptr, size_t new_size)
   {
      return realloc(ptr, new_size);
   }
};

#endif
