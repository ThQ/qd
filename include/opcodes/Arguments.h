#ifndef OPCODES__ARGUMENTS__H
#define OPCODES__ARGUMENTS__H __FILE__

#define OPC_NS_ARGUMENTS            126 /* ~ */
#define OPC_ARGUMENTS_COUNT          99 /* c */
#define OPC_ARGUMENTS_GET_INT       105 /* i */

#include "t/Block.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"

namespace opcodes
{
   class Arguments
   {
      public: static bool run (vm::Frame* pFrame, vm::OpCode* pOpcode, t::Value* pArguments);
   };
}

#endif
