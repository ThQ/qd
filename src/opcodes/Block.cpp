#include "opcodes/Block.h"

namespace opcodes
{
   bool
   Block::run (t::Block* pBlock, vm::Frame* pFrame, vm::OpCode* pOpcode, t::Value* pArguments, t::Block** pBlocks, t::Block*& pBlockToRun)
   {
      bool bHandled = true;
      switch (pOpcode->method)
      {
         case OPC_BLOCK_GET_INT_ARG:
         {
            VM__OPCODE__GET_ARG(0, uint, nIntReg);
            VM__OPCODE__GET_ARG(1, uint, nArgIndex);

            int nValue = (int)pFrame->arguments[nArgIndex];

            LOG_OPCODE(
                  pOpcode,
                  "OPC_BLOCK_GET_INT_ARG"
                  " (.register_index %u, .argument_index %u, .value %d)\n",
                  nIntReg,
                  nArgIndex,
                  nValue
            )

            pFrame->registers.set_int(nIntReg, nValue);

            break;
         }

         case OPC_BLOCK_INVOKE:
         {
            VM__OPCODE__GET_ARG(0, uint, nBlockIndex);
            LOG_OPCODE(
                  pOpcode,
                  "OPC_BLOCK_INVOKE"
                  " (.block_at_index %u, .block_at 0x%x)\n",
                  nBlockIndex,
                  (uint)pBlocks[nBlockIndex]
            );

            pBlockToRun = pBlocks[nBlockIndex];
            ASSERT_NOT_NULL(pBlockToRun);
            pBlockToRun->argument_count = pOpcode->argument_count - 1;

            // Copy arguments
            // @todo Can we do better at reusing existing arrays of arguments ?
            for (uchar i = 0 ; i < pBlockToRun->argument_count ; ++i)
            {
               pBlockToRun->set_argument(i, pArguments[i + 1]);
            }

            break;
         }

         case OPC_BLOCK_PRINTL_INT_ARG:
         {
            VM__OPCODE__GET_ARG(0, uint, nArgIndex);

            int nValue = (int)pFrame->arguments[nArgIndex];
            printf("%d\n", nValue);

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
