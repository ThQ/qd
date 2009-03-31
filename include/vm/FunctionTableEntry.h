#ifndef SVM_FUNCTION_TABLE_ENTRY_H
#define SVM_FUNCTION_TABLE_ENTRY_H

#include <string.h>

#include "svm/Class.h"
#include "svm/Function.h"
#include "svm/Variable.h"

namespace svm
{
   class FunctionTableEntry
   {
      public: Function* function;
      public: std::string signature;

      public: FunctionTableEntry();
      public: FunctionTableEntry(Function* func);
      public: ~FunctionTableEntry();
      public: void set_function(Function* func);
   };
}
#endif
