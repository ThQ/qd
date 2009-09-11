#include "opcodes/Jump.h"

namespace opcodes
{
   bool
   Jump::run (vm::OpCode* pOpCode, t::Value* pArguments, uint& nOpcodeIndex)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_JUMP_TO:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestOpcodeIndex);

            nOpcodeIndex = (nDestOpcodeIndex == 0) ? 0 : (nDestOpcodeIndex - 1);
            INTERNAL("<Opcode 0x%x> JUMP_TO (.index %u)\n", (uint)pOpCode, (nOpcodeIndex+1));
            break;
         }

         case OPC_JUMP_IF:
         {
            VM__OPCODE__GET_ARG(0, uint, nCondition);
            VM__OPCODE__GET_ARG(1, uint, nDestOpcodeIndex);

            if (nCondition != 0)
            {
               nOpcodeIndex = nDestOpcodeIndex == 0 ? 0 : nDestOpcodeIndex - 1;
            }
            break;
         }

         case OPC_JUMP_IF_LE:
         {
            VM__OPCODE__GET_ARG(0, u3, nDestOpcodeIndex);
            VM__OPCODE__GET_ARG(1, i3, nVal1);
            VM__OPCODE__GET_ARG(2, i3, nVal2);

            LOG_OPCODE(
                  pOpCode,
                  "OPC_JUMP_IF_LE"
                  "(.destination %u, .value1 %d, value2 %d, .condition %s)\n",
                  nDestOpcodeIndex,
                  nVal1,
                  nVal2,
                  nVal1 < nVal2 ? "True" : "False"
            );

            if (nVal1 <= nVal2)
            {
               nOpcodeIndex = nDestOpcodeIndex == 0 ? 0 : nDestOpcodeIndex - 1;
            }
            break;
         }

         case OPC_JUMP_IF_LT:
         {
            VM__OPCODE__GET_ARG(0, u3, nDestOpcodeIndex);
            VM__OPCODE__GET_ARG(1, i3, nVal1);
            VM__OPCODE__GET_ARG(2, i3, nVal2);

            LOG_OPCODE(
                  pOpCode,
                  "OPC_JUMP_IF_LT"
                  "(.destination %u, .value1 %u, value2 %u, .condition %s)\n",
                  nDestOpcodeIndex,
                  nVal1,
                  nVal2,
                  nVal1 < nVal2 ? "True" : "False"
            );

            if (nVal1 < nVal2)
            {
               nOpcodeIndex = nDestOpcodeIndex == 0 ? 0 : nDestOpcodeIndex - 1;
            }
            break;
         }

         case OPC_JUMP_IF_ELSE:
         {
            VM__OPCODE__GET_ARG(0, uint, nCondition);
            VM__OPCODE__GET_ARG(1, uint, nIfDestOpcodeIndex);
            VM__OPCODE__GET_ARG(2, uint, nElseDestOpcodeIndex);

            if (nCondition != 0)
            {
               nOpcodeIndex = nIfDestOpcodeIndex == 0 ? 0 : nIfDestOpcodeIndex - 1;
            }
            else
            {
               nOpcodeIndex = nElseDestOpcodeIndex == 0 ? 0 : nElseDestOpcodeIndex - 1;
            }
            break;
         }

         case OPC_JUMP_IF_NOT:
         {
            VM__OPCODE__GET_ARG(0, uint, nCondition);
            VM__OPCODE__GET_ARG(1, uint, nDestOpcodeIndex);

            LOG_OPCODE
            (
               pOpCode,
               "OPC_JMP_UNLESS (.condition %s, .dest_index %u)\n",
               (nCondition == 0 ? "False" : "True"),
               (nOpcodeIndex+1)
            );

            if (nCondition == 0)
            {
               nOpcodeIndex = nDestOpcodeIndex == 0 ? 0 : nDestOpcodeIndex - 1;
            }
            break;
         }

         default:
            bHandled = false;
      }

      return bHandled;
   }
}
