#include "opcodes/Arguments.h"

namespace opcodes
{
   bool
   Arguments::run (vm::Frame* pFrame, vm::OpCode* pOpcode, t::Value* pArguments)
   {
      bool bHandled = true;

      switch (pOpcode->method)
      {
         case OPC_ARGUMENTS_COUNT:
         {
            VM__OPCODE__GET_ARG(0, u3, nIntReg);

            LOG_OPCODE(
               pOpcode,
               "OPC_ARGUMENTS_COUNT (.dest_int_register %u)\n",
               nIntReg
            );

            pFrame->registers.set_int(nIntReg, pFrame->argument_count);

            break;
         }

         case OPC_ARGUMENTS_GET_INT:
         {
            VM__OPCODE__GET_ARG(0, u3, nIntReg);
            VM__OPCODE__GET_ARG(1, u3, nArgIndex);

            LOG_OPCODE(
               pOpcode,
               "OPC_ARGUMENTS_GET_INT"
               " (.dest_int_register %u, .argument_index %u)\n",
               nIntReg,
               nArgIndex
            );

            i3 nVal = (i3)pFrame->arguments[nArgIndex];
            pFrame->registers.set_int(nIntReg, nVal);
            break;
         }

         default:
            bHandled = false;
      }

      return bHandled;
   }
}
