#ifndef OPCODES__EXCEPTION__H
#define OPCODES__EXCEPTION__H __FILE__

#include "t/Block.h"
#include "t/Exception.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"

#define OPC_NS_EXCEPTION         101 /*  e  */
#define OPC_EXCEPTION_NEW         33 /*  !  */
#define OPC_EXCEPTION_THROW      116 /*  t  */

namespace opcodes
{
   class Exception
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_EXCEPTION.
       *
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
