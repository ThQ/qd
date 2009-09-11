#include "vm/Frame.h"

namespace vm
{
   Frame::Frame ()
   {
      this->block = NULL;
      this->arguments = NULL;
      this->argument_count = 0;
      this->exception = NULL;
      this->exception_handler = NULL;
      this->parent_frame = NULL;
   }

   Frame::Frame (t::Block* pBlock)
   {
      this->arguments = NULL;
      this->argument_count = 0;
      this->block = pBlock;
      this->block->pick();
      this->exception = NULL;
      this->exception_handler = NULL;
      this->parent_frame = NULL;

      if (pBlock->argument_count)
      {
         Memory_ALLOC (this->arguments, t::Value, pBlock->argument_count);

         for (u1 i = 0 ; i < pBlock->argument_count ; ++i)
         {
            this->arguments[i] = pBlock->get_argument(i);
         }
         this->argument_count = pBlock->count_arguments();
      }
   }

   Frame::~Frame ()
   {
      if (this->exception != NULL)
      {
         this->exception->drop();
      }
      Memory_FREE_IF_NOT_NULL (this->arguments);
   }

   void
   Frame::set_exception_handler (t::Block* block)
   {
      ASSERT_NOT_NULL(block);

      if (this->exception_handler != NULL)
      {
         this->exception_handler->drop();
      }
      block->pick();
      this->exception_handler = block;
   }

   void
   Frame::throw_exception (t::Exception* pException)
   {
      if (this->exception != NULL)
      {
         this->exception->drop();
      }
      pException->pick();
      this->exception = pException;
   }
}
