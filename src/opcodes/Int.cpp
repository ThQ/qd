#include "opcodes/Int.h"

namespace opcodes
{
   bool
   Int::run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_INT_ADD:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(nRegPos, (i1 + i2));

            break;
         }

         case OPC_INT_DIV:
         {
            VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(pRegDest->position, (i1 / i2));

            break;
         }

         case OPC_INT_INCR:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            int nValue = pFrame->registers.get_int(nRegPos) + 1;
            LOG_OPCODE(
                  pOpCode,
                  "OPC_INT_INCR (.int_register %u, .new_value %u)\n",
                  nRegPos,
                  nValue
            );
            pFrame->registers.set_int(nRegPos, nValue);
            break;
         }

         case OPC_INT_LE:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(nRegPos, (i1 <= i2) ? 1 : 0);

            break;
         }

         case OPC_INT_LT:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegPos);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            bool bResult = (i1 < i2) ? 1 : 0;
            LOG_OPCODE(
                  pOpCode,
                  "OPC_INT_LT (.i1 %d, .i2 %d, .result %s)\n",
                  i1,
                  i2,
                  bResult ? "True" : "False"
            );
            pFrame->registers.set_int(nRegPos, bResult);

            break;
         }

         case OPC_INT_MOD:
         {
            VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(pRegDest->position, (i1 % i2));

            break;
         }

         case OPC_INT_MUL:
         {
            VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(pRegDest->position, (i1 * i2));

            break;
         }

         case OPC_INT_PRINT:
         {
            VM__OPCODE__GET_ARG(0, int, i);

            printf("%d", i);

            break;
         }

         case OPC_INT_PRINTL:
         {
            VM__OPCODE__GET_ARG(0, int, i);

            printf("%d\n", i);

            break;
         }

         case OPC_INT_SUB:
         {
            VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
            VM__OPCODE__GET_ARG(1, int, i1);
            VM__OPCODE__GET_ARG(2, int, i2);

            pFrame->registers.set_int(pRegDest->position, (i1 - i2));

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}

