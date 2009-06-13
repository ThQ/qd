#ifndef MEMORY_H

#include <cstdlib>

#define MALLOC(size) malloc((size))
#define REALLOC(pointer, new_size) realloc((pointer), (new_size))

/**
 * A way of abstracting memory management.
 */
class Memory
{
   /**
    * Frees a memory allcated with malloc.
    *
    * @param ptr A pointer to the memory to free.
    */
   public: inline static void* free(void* ptr)
   {
      return free(ptr);
   }

   /**
    * Allocates memory.
    *
    * @param size Size of the memory to allocate.
    */
   public: inline static void* malloc(size_t size)
   {
      return malloc(size);
   }

   /**
    * Reallocates memory.
    *
    * @param ptr A pointer to the memory to reallocate.
    * @param new_size The memory size to reallocate.
    */
   public: inline static void* realloc(void* ptr, size_t new_size)
   {
      return realloc(ptr, new_size);
   }
};

#endif
