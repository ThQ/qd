#include "vm/Stack.h"

namespace NS_VM
{
   Stack::Stack()
   {
      this->blocks = NULL;
      this->block_count = 0;
   }

   Stack::~Stack()
   {
      for (ULong i = 0 ; i < this->block_count ; ++ i)
      {
         T_OBJECT::drop(this->blocks[i]);
      }
      delete[] this->blocks;
   }

   void
   Stack::append(t::Block* block)
   {
      T_OBJECT::pick(block);
      ++ this->block_count;
      this->blocks = (t::Block**)realloc(this->blocks, sizeof(t::Block*) * this->block_count);
      ASSERT_REALLOC(this->blocks);
      this->blocks[this->block_count - 1] = block;
   }

   unsigned long
   Stack::count()
   {
      return this->block_count;
   }

   t::Block*
   Stack::get(ULong at)
   {
      ASSERT(
            at < this->block_count,
            "Index [%lu] out of range [0:%lu].\n",
            at,
            this->block_count - 1
      );
      T_OBJECT::pick(this->blocks[at]);
      return this->blocks[at];
   }

   t::Block*
   Stack::pop()
   {
      t::Block* result;
      if (this->block_count > 0)
      {
         result = this->blocks[this->block_count - 1];
         -- this->block_count;
         ULong new_size = sizeof(t::Block*) * this->block_count;
         // @TODO: Fix the instensive REALLOC'ing
         this->blocks = (t::Block**)REALLOC(this->blocks, new_size);
      }
      else
      {
         result  = NULL;
      }
      return result;
   }

   void
   Stack::print()
   {
      printf("StackTrace:\n");
      for (ULong i = this->block_count - 1 ; i >= 0 ; -- i)
      {
         printf(
            "  #%lu [%s]\n",
            i + 1,
            this->blocks[i]->name.c_str()
         );
      }
   }
}
