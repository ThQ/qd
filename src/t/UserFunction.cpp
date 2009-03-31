#include "t/UserFunction.h"

namespace NS_TYPE
{
   UserFunction::UserFunction()
   {
      this->is_user = true;
      this->block = NULL;
   }

   void
   UserFunction::set_block(T_BLOCK* block)
   {
      T_OBJECT::drop_safe(this->block);
      T_OBJECT::pick_safe(block);
      this->block = block;
   }
}

