#include "svm/UserFunction.h"

namespace svm
{
   UserFunction::UserFunction()
   {
      this->is_user = true;
      this->block = NULL;
   }

   void
   UserFunction::set_block(Block* block)
   {
      SVM_DROP_SAFE(this->block);
      SVM_PICK_SAFE(block);
      this->block = block;
   }
}

