#include "t/UserFunction.h"

namespace t
{
   UserFunction::UserFunction()
   {
      this->is_user = true;
      this->block = NULL;
   }

   UserFunction::~UserFunction()
   {
      if (this->block != NULL)
      {
         this->block->drop();
      }
   }

   void
   UserFunction::set_block(Block* pBlock)
   {
      if (this->block != NULL)
      {
         this->block->drop();
      }
      pBlock->drop();
      this->block = pBlock;
   }
}

