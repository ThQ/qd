#include "opcodes/Exception.h"

namespace opcodes
{
   bool
   Exception::run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_EXCEPTION_NEW:
         {
            VM__OPCODE__GET_ARG(0, uint, nDestRegPos);

            t::Exception* pErr = new t::Exception();
            pFrame->registers.set_object(nDestRegPos, pErr);

            break;
         }

         case OPC_EXCEPTION_THROW:
         {
            VM__OPCODE__GET_ARG(0, uint, nSrcExceptionPos);

            t::Exception* pErr = (t::Exception*)pFrame->registers.get_object(nSrcExceptionPos);
            pFrame->throw_exception(pErr);

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
