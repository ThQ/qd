#ifndef OPCODES__BLOCK__H
#define OPCODES__BLOCK__H __FILE__

#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_BLOCK                 66 /*  B  */
#define OPC_BLOCK_INVOKE             46 /*  .  */

namespace opcodes
{
   class Block
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_BLOCK.
       *
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::OpCode* pOpCode, t::Value* pArguments, t::Block** pBlocks, t::Block*& pBlockToRun);

      /**
       * @brief Runs an OPC_BLOCK_INVOKE opcode.
       *
       * @param pOpc The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static inline t::Block* run_invoke (t::Block** pBlocks, vm::OpCode* pOpc, t::Value* pArguments);
   };
}

#endif
