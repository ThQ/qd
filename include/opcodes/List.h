#ifndef OPCODES__LIST__H
#define OPCODES__LIST__H __FILE__

#include "t/List.h"
#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_LIST           76 /*  L  */
#define OPC_LIST_NEW          33 /*  !  */
#define OPC_LIST_PRINT       112 /*  p  */
#define OPC_LIST_PRINTL       80 /*  P  */
#define OPC_LIST_PUSH_INT    105 /*  i  */

namespace opcodes
{
   /**
    * @brief A class that runs list opcodes.
    *
    * * OPC_LIST_NEW[3]          (nDestReg :uint, nType :uint)
    */
   class List
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_LIST.
       *
       * @param pBlock The block being currently run.
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (t::Block* pBlock, vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
