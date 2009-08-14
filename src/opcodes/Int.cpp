#include "opcodes/Int.h"


namespace opcodes
{
   bool
   Int::run (t::Block* pBlock, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_INT_ADD:
            Int::run_add(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_DIV:
            Int::run_divide(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_LE:
            Int::run_lower_or_equal(pBlock, pOpCode, pArguments);
            break;

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
            pBlock->registers.set_int(nRegPos, bResult);

            break;
         }

         case OPC_INT_MOD:
            Int::run_modulo(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_MUL:
            Int::run_multiply(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_PRINT:
            Int::run_print(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_PRINTL:
            Int::run_print_line(pBlock, pOpCode, pArguments);
            break;

         case OPC_INT_SUB:
            Int::run_subtract(pBlock, pOpCode, pArguments);
            break;

         default:
            bHandled = false;
      }
      return bHandled;
   }

   void
   Int::run_add (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, uint, nRegPos);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(nRegPos, (i1 + i2));
   }

   void
   Int::run_divide (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(pRegDest->position, (i1 / i2));
   }

   void
   Int::run_lower_or_equal (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, uint, nRegPos);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(nRegPos, (i1 <= i2) ? 1 : 0);
   }

   void
   Int::run_lower_than (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
   }

   void
   Int::run_modulo (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(pRegDest->position, (i1 % i2));
   }

   void
   Int::run_multiply (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(pRegDest->position, (i1 * i2));
   }

   void
   Int::run_print (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, int, i);
      printf("%d", i);
   }

   void
   Int::run_print_line (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, int, i);
      printf("%d\n", i);
   }

   void
   Int::run_subtract (t::Block* pBlock, vm::OpCode* pOpc, t::Value* pArguments)
   {
      VM__OPCODE__GET_ARG(0, t::RegisterObject*, pRegDest);
      VM__OPCODE__GET_ARG(1, int, i1);
      VM__OPCODE__GET_ARG(2, int, i2);

      pBlock->registers.set_int(pRegDest->position, (i1 - i2));
   }
}

