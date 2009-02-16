#ifndef SVM_CORE_FUNCTION_H
#define SVM_CORE_FUNCTION_H

#include "svm/Function.h"

namespace svm
{
   class CoreFunction : public Function
   {
      public: unsigned long function_pointer;

      public: static CoreFunction* build(const char* name, long int pointer, Object* return_type);
   };
}

#endif
