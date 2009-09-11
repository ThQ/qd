#include "opcodes/Debug.h"

namespace opcodes
{
   bool
   Debug::run (vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_DEBUG_BREAK:
         {
            while (true)
            {

            }

            break;
         }

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
