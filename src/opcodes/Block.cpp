#include "opcodes/Block.h"

namespace opcodes
{
   bool
   Block::run (vm::OpCode* pOpCode, t::Value* pArguments, t::Block** pBlocks, t::Block*& pBlockToRun)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_BLOCK_INVOKE:
            pBlockToRun = Block::run_invoke(pBlocks, pOpCode, pArguments);
            break;

         default:
            bHandled = false;
      }
      return bHandled;
   }

   t::Block*
   Block::run_invoke (t::Block** pBlocks, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, uint, nBlockIndex);
      printf("INVOKE BLOCK\n");
      t::Block* pResult = pBlocks[nBlockIndex];

      return pResult;
   }
}

