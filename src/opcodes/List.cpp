#include "opcodes/List.h"

namespace opcodes
{
   bool
   List::run (t::Block* pBlock, vm::OpCode* pOpcode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpcode->method)
      {
         case OPC_LIST_NEW:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestRegPos);
            VM__OPCODE__GET_ARG(1, uint, nContainedObjType);

            LOG_OPCODE(
                  pOpcode,
                  "OPC_LIST_NEW (.dest_reg %u, .type %u)\n",
                  nDestRegPos,
                  nContainedObjType
            );

            t::List* pList = new t::List((uchar)nContainedObjType);
            pBlock->registers.set_object(nDestRegPos, (t::Object*)pList);

            break;
         }

         case OPC_LIST_PRINT:
         {
            VM__OPCODE__GET_ARG(0, uint, nListReg);

            LOG_OPCODE(
               pOpcode,
               "OPC_LIST_PRINT (.src_reg %u)\n",
               nListReg
            );

            t::Value pList = (t::Value)pBlock->registers.get_object(nListReg);
            t::List::__print__(pList);

            break;
         }

         case OPC_LIST_PRINTL:
         {
            VM__OPCODE__GET_ARG(0, uint, nListReg);

            LOG_OPCODE(
               pOpcode,
               "OPC_LIST_PRINTL (.src_reg %u)\n",
               nListReg
            );

            t::Value pList = (t::Value)pBlock->registers.get_object(nListReg);
            t::List::__print_line__(pList);
            break;
         }

         case OPC_LIST_PUSH_INT:
         {
            VM__OPCODE__GET_ARG(0, uint, nListRegPos);
            VM__OPCODE__GET_ARG(1, int, nIntValue);

            t::List* pList = (t::List*)pBlock->registers.get_object(nListRegPos);
            pList->push(nIntValue);

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
