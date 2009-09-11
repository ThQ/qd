#include "opcodes/Dummy.h"

namespace opcodes
{
   bool
   Dummy::run (vm::OpCode* pOpcode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpcode->method)
      {
         case OPC_DUMMY_HELLO:
         {
            LOG_OPCODE(pOpcode, "OPC_DUMMY_HELLO\n");
            printf("Hello World !\n");
            break;
         }

         case OPC_DUMMY_PRINT_INTS:
         {
            ASSERT(pOpcode->argument_count == 3, "Bad argument count.");

            LOG_OPCODE(pOpcode, "DUMMY_PRINT_INTS ");
            for (uint i = 0 ; i < 3 ; ++i)
            {
               if (i != 0)
               {
                  printf(", ");
               }
               printf(".i%d%d", i, (int)pArguments[i]);
            }
            printf(")\n");
            break;
         }

         case OPC_DUMMY_NIL:
            break;

         default:
            bHandled = false;
      }
      return bHandled;
   }
}
