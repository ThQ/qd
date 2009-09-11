#ifndef OPCODES__BLOCK__H
#define OPCODES__BLOCK__H __FILE__


#include "t/Block.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"


#define OPC_NS_BLOCK                 66 /*  B  */
#define OPC_BLOCK_GET_INT_ARG       105 /*  i  */
#define OPC_BLOCK_GET_OBJECT_ARG    111 /*  o  */
#define OPC_BLOCK_INVOKE             46 /*  .  */
#define OPC_BLOCK_PRINTL_INT_ARG     73 /*  I  */


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
      public: static bool run (t::Block* pBlock, vm::Frame* pFrame, vm::OpCode* pOpcode, t::Value* pArguments, t::Block** pBlocks, t::Block*& pBlockToRun);

      public:
   };
}

#endif
