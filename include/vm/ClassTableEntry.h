#ifndef VM_CLASS_TABLE_ENTRY
#define VM_CLASS_TABLE_ENTRY NS_VM::ClassTableEntry

#include "t/Class.h"
#include "t/CoreFunction.h"
#include "t/UserFunction.h"
#include "vm/FieldTable.h"
#include "vm/FunctionTable.h"

namespace NS_VM
{
   class ClassTableEntry
   {
      public: t::Class* cls;
      public: FieldTable fields;
      public: FunctionTable functions;

      public: ClassTableEntry();
      public: ~ClassTableEntry();
      public: void set_class(t::Class* cls);
   };
}

#endif
