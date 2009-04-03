#ifndef VM_FUNCTION_TABLE_ENTRY
#define VM_FUNCTION_TABLE_ENTRY NS_VM::FunctionTableEntry

#include <string.h>

#include "t/Class.h"
#include "t/Function.h"
#include "t/Variable.h"

namespace NS_VM
{
   class FunctionTableEntry
   {
      public: t::Function* function;
      public: std::string signature;

      public: FunctionTableEntry();
      public: FunctionTableEntry(t::Function* func);
      public: ~FunctionTableEntry();
      public: void set_function(t::Function* func);
   };
}
#endif
