#include "svm/Stack.h"

namespace svm
{
   Stack::Stack()
   {
      this->blocks = NULL;
      this->block_count = 0;
   }

   Stack::~Stack()
   {
      for (unsigned long i = 0 ; i < this->block_count ; ++ i)
      {
         SVM_DROP(this->blocks[i]);
      }
      //this->blocks = (Block**)realloc(this->blocks, 0);
      delete[] this->blocks;
   }

   void
   Stack::append(Block* block)
   {
      SVM_PICK(block);
      ++ this->block_count;
      this->blocks = (Block**)realloc(this->blocks, sizeof(Block*) * this->block_count);
      ASSERT_REALLOC(this->blocks);
      this->blocks[this->block_count - 1] = block;
   }

   unsigned long
   Stack::count()
   {
      return this->block_count;
   }

   Block*
   Stack::get(unsigned long at)
   {
      ASSERT(at < this->block_count, "Index [%lu] out of range [0:%lu].\n", at, this->block_count-1);
      SVM_PICK(this->blocks[at]);
      return this->blocks[at];
   }

   Block*
   Stack::pop()
   {
      Block* result;
      if (this->block_count > 0)
      {
         result = this->blocks[this->block_count - 1];
         -- this->block_count;
         this->blocks = (Block**)realloc(this->blocks, sizeof(Block*) * this->block_count);
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
