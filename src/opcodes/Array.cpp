#include "opcodes/Array.h"

namespace opcodes
{
   bool
   Array::run (t::Block* pBlock, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_ARRAY_GET_INT:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestReg);
            VM__OPCODE__GET_ARG(1, uint, nArrayReg);
            VM__OPCODE__GET_ARG(2, uint, nArrayIndex);

            t::Array* pArr = (t::Array*)pBlock->registers.get_object(nArrayReg);
            pBlock->registers.set_int(nDestReg, pArr->get_int(nArrayIndex));
            break;
         }

         case OPC_ARRAY_GET_OBJECT:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestReg);
            VM__OPCODE__GET_ARG(1, uint, nArrayReg);
            VM__OPCODE__GET_ARG(2, uint, nArrayIndex);

            t::Array* pArr = (t::Array*)pBlock->registers.get_object(nArrayReg);
            t::Object* pObj = pArr->get_object(nArrayIndex);
            pBlock->registers.set_object(nDestReg, pObj);
            break;
         }

         case OPC_ARRAY_NEW:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestRegPos);
            VM__OPCODE__GET_ARG(1, uint, nContainedObjType);
            VM__OPCODE__GET_ARG(2, uint, nArraySize);
            t::Array* pArr = new t::Array((uchar)nContainedObjType, nArraySize);
            pBlock->registers.set_object(nDestRegPos, (t::Object*)pArr);
            break;
         }

         case OPC_ARRAY_PRINT:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegSrc);
            t::Value pArr = (t::Value)pBlock->registers.get_object(nRegSrc);
            t::Array::__print__(pArr);
            break;
         }

         case OPC_ARRAY_PRINTL:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegSrc);
            t::Value pArr = (t::Value)pBlock->registers.get_object(nRegSrc);
            t::Array::__print_line__(pArr);
            break;
         }

         case OPC_ARRAY_SET_INT:
         {
            VM__OPCODE__GET_ARG(0, uint, nRegSrc);
            VM__OPCODE__GET_ARG(1, uint, nIndex);
            VM__OPCODE__GET_ARG(2, int, nValue);
            t::Array* pArr = (t::Array*)pBlock->registers.get_object(nRegSrc);
            pArr->set_int(nIndex, nValue);
            break;
         }

         case OPC_ARRAY_SLICE:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestReg);
            VM__OPCODE__GET_ARG(1, uint, nSrcReg);
            VM__OPCODE__GET_ARG(2, uint, nStartIndex);
            VM__OPCODE__GET_ARG(3, uint, nLength);
            VM__OPCODE__GET_ARG(4, uint, nStep);

            t::Array* pArray = (t::Array*)pBlock->registers.get_object(nSrcReg);
            t::Array* pSlice = pArray->slice(nStartIndex, nLength, nStep);
            pBlock->registers.set_object(nDestReg, pSlice);

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
