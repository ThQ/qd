#ifndef MEMORY__H
#define MEMORY__H __FILE__

#include <cstdlib>

#define Memory_ALLOC(ptr, type, n) \
   LOG_MEMORY("MEMORY_ALLOCATE (.pointer \"%s\", .type \"%s\", .count %d)\n", (#ptr), (#type), (uint)(n)); \
   ((ptr) = (type*)malloc(sizeof(type) * n));

#define Memory_FREE(ptr) \
   LOG_MEMORY("MEMORY_FREE (.pointer \"%s\", .pointer_at 0x%x)\n", (#ptr), (uint)(ptr)); \
   free((ptr)); \
   (ptr) = NULL;

#define Memory_FREE_IF_NOT_NULL(ptr) if ((ptr) != NULL){Memory_FREE(ptr);}

#define Memory_REALLOC(ptr, type, n) \
   LOG_MEMORY("MEMORY_REALLOCATE (.pointer \"%s\", .pointer_at 0x%x, .type \"%s\", .count %d)\n", (#ptr), (uint)(ptr), (#type), (uint)(n)); \
   ((ptr) = (type*)realloc((ptr), sizeof(type) * n));

#define DELETE(p) \
   LOG_MEMORY(\
         "<%s:0x%x> DELETE (.type %u, .class_at 0x%x)\n", \
         t::get_type_name((p)->type), \
         (uint)(p), \
         ((Object*)(p))->type, \
         (uint)((Object*)(p))->klass\
   ); \
   delete p; \
   p = NULL; \
   ASSERT_DELETE(p);
#define DELETE_THIS() INTERNAL("<%s:0%x> DELETE\n", t::get_type_name(this->type), (uint)this);

/// @todo Delete these.
#define __MALLOC(size) malloc((size))
#define __REALLOC(pointer, new_size) realloc((pointer), (new_size))

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
