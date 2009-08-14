#include "opcodes/Dummy.h"

namespace opcodes
{
   bool
   Dummy::run (vm::OpCode* pOpCode, t::Value* pArguments)
   {
      bool bHandled = true;
      switch (pOpCode->method)
      {
         case OPC_DUMMY_HELLO:
            Dummy::run_hello();
            break;

         case OPC_DUMMY_PRINT_INTS:
            Dummy::run_print_ints(pOpCode, pArguments);
            break;

         case OPC_DUMMY_NIL:
            break;

         default:
            bHandled = false;
      }
      return bHandled;
   }

   void
   Dummy::run_hello ()
   {
      printf("DUMMY:HELLO | Hello world !\n");
   }

   void
   Dummy::run_print_ints (vm::OpCode* pOpc, t::Value* pArguments)
   {
      ASSERT(pOpc->argument_count == 3, "Bad argument count.");
      printf("DUMMY:PRINT_INTS | 3 good brave ints: ");
      for (ulong i = 0 ; i < 3 ; ++i)
      {
         if (i != 0)
         {
            printf(", ");
         }
         printf("%d", (int)pArguments[i]);
      }
      printf(".\n");
   }
}

