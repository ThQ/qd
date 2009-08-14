#include "vm/CallStack.h"

namespace vm
{
   CallStack::CallStack()
   {
      this->blocks = NULL;
      this->block_count = 0;
   }

   CallStack::~CallStack()
   {
      if (this->blocks != NULL)
      {
         LOOP_FROM_TO(ulong, i, 0, this->block_count)
         {
            ASSERT_NOT_NULL(this->blocks[i]);
            ASSERT_NOT_NULL(this->blocks[i]->klass);
            this->blocks[i]->drop();
         }
         Memory_FREE(this->blocks);
      }
   }

   void
   CallStack::append(t::Block* block)
   {
      ASSERT_NOT_NULL(block);
      ASSERT_NOT_NULL(block->klass);

      ++ this->block_count;
      Memory_REALLOC(this->blocks, t::Block*, this->block_count);
      block->pick();
      this->blocks[this->block_count - 1] = block;
   }

   ulong
   CallStack::count()
   {
      return this->block_count;
   }

   t::Block*
   CallStack::get(ulong at)
   {
      ASSERT(
            at < this->block_count,
            "Index [%lu] out of range [0:%lu].\n",
            at,
            this->block_count - 1
      );
      return this->blocks[at];
   }

   t::Block*
   CallStack::pop()
   {
      t::Block* result;
      if (this->block_count > 0)
      {
         result = this->blocks[this->block_count - 1];
         ASSERT_NOT_NULL(result);
         result->drop();
         -- this->block_count;
         if (this->block_count != 0)
         {
            Memory_REALLOC(this->blocks, t::Block*, this->block_count);
         }
         else
         {
            Memory_FREE(this->blocks);
         }
      }
      else
      {
         result  = NULL;
      }
      return result;
   }

   void
   CallStack::print()
   {
      printf("StackTrace:\n");
      for (ulong i = this->block_count - 1 ; i >= 0 ; -- i)
      {
         printf(
            "  #%lu [%s]\n",
            i + 1,
            "" //this->blocks[i]->name.c_str()
         );
      }
   }
}
