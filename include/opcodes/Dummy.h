#ifndef OPCODES__DUMMY__H
#define OPCODES__DUMMY__H __FILE__

#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_DUMMY           59 /*  ;  */
#define OPC_DUMMY_HELLO       112 /*  p  */
#define OPC_DUMMY_NIL          78 /*  N  */
#define OPC_DUMMY_PRINT_INTS   80 /*  P  */

namespace opcodes
{
   class Dummy
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_DUMMY.
       *
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
