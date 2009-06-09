#ifndef VM_OPCODE_H
#define VM_OPCODE_H


#define OPC_NS_NIL      59  /*  ;  */

// [!opcodes:constants]

#include <string>

#include "t/Object.h"

namespace vm
{
   /**
    * The tinyest executable unit. It is identified by a namespace and a name,
    * and takes arguments.
    */
   class OpCode
   {
      public: UInt argc;            ///< Number of arguments.
      public: t::Object** argv;     ///< A @cls{t::Object} array of arguments.
      public: std::string content;  ///< A content is a string data, most frequently a name (function name), but it seems to be useless now.
      public: OpCode* next_opcode;  ///< A pointer to the next opcode in the block.
      public: UShort type;          ///< Opcode namespace.
      public: UShort method;        ///< Opcode method.

      /**
       * Constructor.
       */
      public: OpCode();
   };
}

#endif
