#ifndef SVM_FUNCTION_TABLE_H
#define SVM_FUNCTION_TABLE_H

#include "debug.h"
#include "svm/Function.h"
#include "svm/FunctionTableEntry.h"

namespace svm
{
   class FunctionTable
   {
      public: FunctionTableEntry** functions;
      public: unsigned long function_count;

      public: FunctionTable();
      public: ~FunctionTable();
      public: void append(FunctionTableEntry* entry);
      public: void append(Function* func);
      #ifdef _DEBUG_
      public: void assert_validity();
      #endif
      public: unsigned long count();
      public: long find(std::string name);
      public: long find(Function* func);
      public: Function* get(std::string name);
      public: bool has(std::string name);
      public: bool has(Function* func);
      #ifdef _DEBUG_
      public: void list();
      #endif
   };
}

#endif
