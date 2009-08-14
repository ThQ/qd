#include "opcodes/Registers.h"

namespace opcodes
{
   bool
   Registers::run (t::Block* pBlock, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_REGISTERS_PRINT:
         {
            pBlock->registers.print();
            break;
         }

         case OPC_REGISTERS_SIZE:
         {
            VM__OPCODE__GET_ARG(0, uint, nInts);
            VM__OPCODE__GET_ARG(1, uint, nLongs);
            VM__OPCODE__GET_ARG(2, uint, nObjects);

            pBlock->registers.size(nInts, nLongs, nObjects);
            break;
         }

         case OPC_REGISTERS_SET_INT:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            VM__OPCODE__GET_ARG(1, int, nVal);

            pBlock->registers.set_int(nRegPos, nVal);
            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}

