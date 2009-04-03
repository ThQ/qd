#ifndef VM_FUNCTION_TABLE
#define VM_FUNCTION_TABLE NS_VM::FunctionTable

#include "t/Function.h"
#include "vm/FunctionTableEntry.h"

namespace NS_VM
{
   class FunctionTable
   {
      public: FunctionTableEntry** functions;
      public: unsigned long function_count;

      public: FunctionTable();
      public: ~FunctionTable();
      public: void append(FunctionTableEntry* entry);
      public: void append(t::Function* func);
      #ifdef _DEBUG_
      public: void assert_validity();
      #endif
      public: unsigned long count();
      public: long find(std::string name);
      public: long find(t::Function* func);
      public: t::Function* get(std::string name);
      public: bool has(std::string name);
      public: bool has(t::Function* func);
      #ifdef _DEBUG_
      public: void list();
      #endif
   };
}

#endif
