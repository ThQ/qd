#ifndef VM_OPCODE_H
#define VM_OPCODE_H


#define OPC_NS_NIL      59  /*  ;  */

// [!opcodes:constants]

#include <string>

#include "t/Object.h"

namespace NS_VM
{
   class OpCode
   {
      public: UInt argc;
      public: t::Object** argv;
      public: std::string content;
      public: OpCode* next_opcode;
      public: UShort type;
      public: UShort method;

      public: OpCode();
   };
}

#endif
