#include "opcodes/Registers.h"

namespace opcodes
{
   bool
   Registers::run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_REGISTERS_COPY_INT:
         {
            VM__OPCODE__GET_ARG(0, u3, nDstReg)
            VM__OPCODE__GET_ARG(1, u3, nSrcReg)

            u3 nInt = (u3)pFrame->registers.get_int(nSrcReg);

            LOG_OPCODE(
               pOpCode,
               "OPC_REGISTERS_COPY_INT"
               " (.source_int_register %" PRTF_u3 ","
               " .destination_int_register %" PRTF_u3 ","
               " .value %" PRTF_u3 ")\n",
               nSrcReg,
               nDstReg,
               nInt
            );

            pFrame->registers.set_int(nDstReg, nInt);

            break;
         }

         case OPC_REGISTERS_COPY_INT_TO_LONG:
         {
            VM__OPCODE__GET_ARG(0, uint, nIntRegister)
            VM__OPCODE__GET_ARG(1, uint, nLongRegister)

            u4 nConvertedInt = (u4)pFrame->registers.get_int(nIntRegister);
            pFrame->registers.set_long(nLongRegister, nConvertedInt);

            break;
         }

         case OPC_REGISTERS_PRINT:
         {
            pFrame->registers.print();
            break;
         }

         case OPC_REGISTERS_SIZE:
         {
            VM__OPCODE__GET_ARG(0, uint, nInts);
            VM__OPCODE__GET_ARG(1, uint, nLongs);
            VM__OPCODE__GET_ARG(2, uint, nObjects);
            LOG_OPCODE(
                  pOpCode,
                  "OPC_REGISTERS_SIZE (.ints %u, .longs %u, .objects %u)\n",
                  nInts,
                  nLongs,
                  nObjects
            );

            pFrame->registers.size(nInts, nLongs, nObjects);
            break;
         }

         case OPC_REGISTERS_SET_INT:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            VM__OPCODE__GET_ARG(1, int, nVal);

            pFrame->registers.set_int(nRegPos, nVal);
            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}

