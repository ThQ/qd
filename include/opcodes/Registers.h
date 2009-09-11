#ifndef OPCODES__REGISTERS__H
#define OPCODES__REGISTERS__H __FILE__

#include "t/Block.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"
#include "vm/RegisterPool.h"

#define OPC_NS_REGISTERS                   82 /* R */
#define OPC_REGISTERS_PRINT               112 /* p */
#define OPC_REGISTERS_COPY_INT             62 /* > */
#define OPC_REGISTERS_COPY_INT_TO_LONG     76 /* L */
#define OPC_REGISTERS_SET_INT             105 /* i  */
#define OPC_REGISTERS_SET_LONG            108 /* l  */ ///< @todo Implement !
#define OPC_REGISTERS_SET_OBJECT          111 /* o  */ ///< @todo Implement !
#define OPC_REGISTERS_SIZE                115 /* s  */

namespace opcodes
{
   /**
    * @brief Runs an opcode whose namespace is OPC_NS_REGISTERS.
    */
   class Registers
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_DUMMY.
       *
       * @param pBlock The block being currently run.
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#
#endif
