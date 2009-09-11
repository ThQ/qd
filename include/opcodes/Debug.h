#ifndef OPCODES__DEBUG__H
#define OPCODES__DEBUG__H __FILE__

#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_DEBUG           35 /*  #  */
#define OPC_DEBUG_BREAK        98 /*  b  */

namespace opcodes
{
   class Debug
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_DEBUG.
       *
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
