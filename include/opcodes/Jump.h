#ifndef OPCODES__JUMP__H
#define OPCODES__JUMP__H __FILE__

#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_JUMP            62  /*  >  */
#define OPC_JUMP_TO            50  /*  2  */
#define OPC_JUMP_IF           105 /*  i  */
#define OPC_JUMP_UNLESS       117 /*  u  */
#define OPC_JUMP_IF_ELSE       63  /*  ?  */

namespace opcodes
{
   /**
    * @brief A runner of all jump/goto/branch related opcodes.
    *
    * * OPC_JUMP_TO__i : Jumps to the opcode at a specific index in the block.
    * * OPC_JUMP_IF__ii : Jumps to an opcode if a parameter is true.
    * * OPC_JUMP_UNLESS__ii : Jumps to an opcode if a parameter is false.
    * * OPC_JUMP_IF_ELSE__iii : Jumps to a certain opcode if a parameter is true, jump to another one if it's false.
    */
   class Jump
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_JUMP.
       *
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       * @param nOpcodeIndex A reference to the variable used to identify which opcode to run in the current block.
       */
      public: static bool run (vm::OpCode* pOpCode, t::Value* pArguments, uint& nOpcodeIndex);
   };
}

#endif
