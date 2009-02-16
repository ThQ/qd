#ifndef SVM_USER_FUNCTION_H
#define SVM_USER_FUNCTION_H

#include "svm/Block.h"
#include "svm/Function.h"

namespace svm
{
   class UserFunction : public Function
   {
      public: Block* block;

      public: UserFunction();
      public: void set_block(Block* block);
   };
}

#endif
