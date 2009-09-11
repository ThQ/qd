#include "opcodes/List.h"

namespace opcodes
{
   bool
   List::run (vm::Frame* pFrame, vm::OpCode* pOpcode, t::Value* pArguments)
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
            pFrame->registers.set_object(nDestRegPos, (t::Object*)pList);

            break;
         }

         case OPC_LIST_PRINT:
         {
            VM__OPCODE__GET_ARG(0, t::List*, pList);

            LOG_OPCODE(
               pOpcode,
               "OPC_LIST_PRINT (.list_at 0x%x)\n",
               (uint)pList
            );

            t::List::__print__(pList);

            break;
         }

         case OPC_LIST_PRINTL:
         {
            VM__OPCODE__GET_ARG(0, t::List*, pList);

            LOG_OPCODE(
               pOpcode,
               "OPC_LIST_PRINTL (.list_at 0x%x)\n",
               (uint)pList
            );

            t::List::__print_line__(pList);
            break;
         }

         case OPC_LIST_PUSH_INT:
         {
            VM__OPCODE__GET_ARG(0, t::List*, pList);
            VM__OPCODE__GET_ARG(1, int, nIntValue);

            pList->push(nIntValue);

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
