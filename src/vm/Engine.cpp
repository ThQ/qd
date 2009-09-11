#include "vm/Engine.h"

namespace vm
{
   Engine::Engine ()
   {
      this->blocks = NULL;
      this->block_count = 0;
      this->classes = NULL;
      this->class_count = 0;
      this->current_block = NULL;
      this->functions = NULL;
      this->function_count = 0;
      this->opcodes = NULL;
      Memory_ALLOC(this->opcode_arguments, t::Value, VM__OPCODE__MAX_ARGUMENTS);
      ASSERT_NOT_NULL(this->opcode_arguments);
      this->opcode_count = 0;
   }

   Engine::~Engine ()
   {
      this->clear_blocks();

      // Clean up opcodes
      for (ulong i = 0 ; i < this->opcode_count ; ++i)
      {
         if (this->opcodes[i] != NULL)
         {
            delete this->opcodes[i];
         }
      }
      Memory_FREE_IF_NOT_NULL(this->opcodes);
      Memory_FREE_IF_NOT_NULL(this->opcode_arguments);
      Memory_FREE_IF_NOT_NULL(this->classes);
      Memory_FREE_IF_NOT_NULL(this->functions);
   }

   t::Value
   Engine::call (ulong nIndex, uchar nArgumentCount, uchar* pArgumentTypes, t::Value* pArguments)
   {
      t::Value pResult = NULL;
      t::CoreFunction* pFunc = (t::CoreFunction*)this->get_function(nIndex);

      if (pFunc != NULL) // && check_arguments(pFunc, nArgumentCount, pArguments))
      {
         CoreFunctionPointer fpFunc = (CoreFunctionPointer)pFunc->function_pointer;
         pResult = fpFunc(this, nArgumentCount, pArgumentTypes, pArguments);
      }

      return pResult;
   }

   void
   Engine::clear_blocks ()
   {
      for (ulong i = 0 ; i < this->block_count ; ++i)
      {
         if (this->blocks[i] != NULL)
         {
            this->blocks[i]->drop();
         }
      }
      Memory_FREE_IF_NOT_NULL(this->blocks);
      this->block_count = 0;
   }

   void
   Engine::copy_arguments (vm::OpCode* pOpcode, t::Value*& pArguments)
   {
      uchar nCount = pOpcode->count_arguments();
      uchar* pArgumentTypes = pOpcode->argument_types;

      for (uchar i = 0 ; i < nCount ; ++i)
      {
         pArguments[i] = (t::Value)pOpcode->get_argument(i);
         if (T__IS_OBJECT_TYPE(pArgumentTypes[i]))
         {
            ASSERT_NOT_NULL(pArguments[i]);
            ((t::Object*)pArguments[i])->pick();
         }
      }
   }

   void
   Engine::exit ()
   {
      // @TODO: Make it a real exit() !
   }

   t::Block*
   Engine::find_nearest_exception_handler ()
   {
      t::Block* pResult = NULL;
      if (this->call_stack.count() > 0)
      {
         vm::Frame* pFrame = this->call_stack.last_frame;
         while (pFrame != NULL)
         {
            ASSERT_NOT_NULL(pFrame);
            if (pFrame->exception_handler != NULL)
            {
               pResult = pFrame->exception_handler;
               break;
            }
            pFrame = pFrame->parent_frame;
         }
      }
      return pResult;
   }

   void
   Engine::format_arguments (vm::OpCode* pOpcode, t::Value* pArguments)
   {
      uchar nCount = pOpcode->count_arguments();
      uchar* pArgumentTypes = pOpcode->argument_types;
      t::Value* pBaseObjects = pOpcode->get_arguments();

      for (uchar i = 0 ; i < nCount ; ++i)
      {
         if (pArgumentTypes[i] == t::REGISTER_VALUE_TYPE)
         {
            t::RegisterObject* pRegObj = (t::RegisterObject*)pBaseObjects[i];
            switch (pRegObj->object_type)
            {
               case t::BOOL_TYPE:
               case t::CHAR_TYPE:
               case t::U_CHAR_TYPE:
               case t::SHORT_TYPE:
               case t::U_SHORT_TYPE:
               case t::INT_TYPE:
               case t::U_INT_TYPE:
                  pArguments[i] = (t::Value)this->current_frame->registers.get_int(pRegObj->position);
                  break;

               case t::LONG_TYPE:
               case t::U_LONG_TYPE:
                  pArguments[i] = (t::Value)this->current_frame->registers.get_long(pRegObj->position);
                  break;

               default:
                  pArguments[i] = (t::Value)this->current_frame->registers.get_object(pRegObj->position);
                  ASSERT_NOT_NULL(pArguments[i]);
                  ((t::Object*)pArguments[i])->pick();
            }
         }
         else
         {
            pArguments[i] = (t::Value)pBaseObjects[i];
            if (T__IS_OBJECT_TYPE(pArgumentTypes[i]))
            {
               ASSERT_NOT_NULL(pArguments[i]);
               ((t::Object*)pArguments[i])->pick();
            }
         }
      }
   }

   t::Block*
   Engine::get_block (ulong nIndex)
   {
      ASSERT(
            nIndex < this->block_count,
            "<Engine @x%x> INDEX_OUT_OF_BLOCK_RANGE (.from 0, .to %lu, .at %lu)",
            (uint)this,
            this->block_count,
            nIndex
      );

      return this->blocks[nIndex];
   }

   bool
   Engine::handle_exception ()
   {
      bool bHandled = false;

      t::Block* pExceptionHandler = this->find_nearest_exception_handler();
      if (pExceptionHandler != NULL)
      {
         ASSERT_NOT_NULL(pExceptionHandler);
         this->run_block(pExceptionHandler, true);
         bHandled = true;
      }
      else
      {
         printf("[Uncaught exception]\n");
      }

      return bHandled;
   }

   void
   Engine::make_empty_value_array (t::Value*& pArray, uchar nCount)
   {
      switch (nCount)
      {
         case 0:
            pArray = NULL;
            break;

         default:
            Memory_ALLOC(pArray, t::Value, nCount);
      }
   }

   void
   Engine::print_block (uint nBlockIndex, t::Block* pBlock)
   {
      printf(
            "  %u: @x%x %s\n"
            " -----------------------------------\n",
            nBlockIndex,
            (uint)pBlock,
            T__BLOCK__GET_NAME(pBlock)
      );
      for (ulong i = 0 ; i < pBlock->opcode_count ; ++ i)
      {
         this->print_opcode(i, pBlock->opcodes[i]);
      }
      printf("\n");
   }

   void
   Engine::print_blocks ()
   {
      for (uint i = 0 ; i < this->block_count ; ++i)
      {
         this->print_block(i, this->blocks[i]);
      }
   }

   void
   Engine::print_opcode (uint nOpcodeIndex, vm::OpCode* pOpcode)
   {
      printf("  %u: @x%x [", nOpcodeIndex, (uint)pOpcode);
      printf("%0d", pOpcode->ns);
      if (pOpcode->ns < 100)
      {
      }
      else
      {
         //printf("%d", pOpcode->ns);
      }
      printf(".");
      if (pOpcode->method < 100)
      {
         printf(" %d", pOpcode->method);
      }
      else
      {
         printf("%d", pOpcode->method);
      }
      printf("]");
      if (pOpcode->argument_count > 0)
      {
         printf(" (");
         for (uint i = 0 ; i < pOpcode->argument_count ; ++ i)
         {
            if (i != 0)
            {
               printf(" ");
            }
            switch (pOpcode->argument_types[i])
            {
               case t::REGISTER_VALUE_TYPE:
                  printf("$");
                  printf("%u", ((t::RegisterObject*)pOpcode->get_argument(i))->position);
                  break;

               case t::CHAR_TYPE:
               case t::SHORT_TYPE:
               case t::INT_TYPE:
                  printf("%d", (int)pOpcode->get_argument(i));
                  break;

               case t::U_CHAR_TYPE:
               case t::U_SHORT_TYPE:
               case t::U_INT_TYPE:
                  printf("%u", (uint)pOpcode->get_argument(i));
                  break;

               default:
                  FATAL("Unknown type <%d>\n", pOpcode->argument_types[i]);
                  abort();
            }
         }
         printf(")");
      }
      printf("\n");
   }

   void
   Engine::print_opcode_arguments ()
   {
      for (uint i = 0 ; i < VM__OPCODE__MAX_ARGUMENTS ; ++i)
      {
         INTERNAL("#%u = %d\n", i, (int)this->opcode_arguments[i]);
      }
   }

   void
   Engine::print_version ()
   {
      printf("%s v%s\n\n", QD__NAME, QD__VERSION);
      printf("name: %s\n", QD__NAME);
      printf("version: %s\n", QD__VERSION);
      printf("author: %s\n", QD__AUTHOR_NAME);
   }

   void
   Engine::run ()
   {
      t::Block* pBlock = this->get_block(0);
      this->run_block(pBlock, true);
   }

   void
   Engine::run_block (t::Block* pBlock, bool bAddToStack)
   {
      ASSERT_NOT_NULL(pBlock);
      ASSERT_NOT_NULL(pBlock->klass);
      ASSERT_NOT_NULL(this->opcode_arguments);

      INTERNAL(
            "<Block:0x%x> RUN (.depth %u)\n",
            (uint)this,
            this->call_stack.count()
      );
      /**
      ASSERT(
            this->swap.count() >= pBlock->argument_count,
            "<Block:?? @x%x> NOT_ENOUGH_OBJECTS_STORED_IN_THE_HEAP"
            " (.real %lu, .expected %hu)\n",
            (uint)pBlock,
            this->swap.count(),
            pBlock->argument_count
      );
      */


      pBlock->pick();
      this->current_block = pBlock;
      this->current_frame = new vm::Frame(pBlock); // This frame is destroyed by the callstack

      if (bAddToStack == true)
      {
         this->call_stack.append(this->current_frame);
      }

      //t::Value* pBlockArguments = NULL;
      if (pBlock->argument_count > 0)
      {

      }

      // Execute each opcode in this block
      ASSERT_NOT_NULL(pBlock);
      vm::OpCode* pOpcode = NULL;

      for (uint i = 0 ; i < pBlock->count() ; ++i)
      {
         pOpcode = pBlock->get(i);
         ASSERT_NOT_NULL(pOpcode);
         ASSERT(
               pOpcode->count_arguments() < VM__OPCODE__MAX_ARGUMENTS,
               "TOO_MUCH_ARGUMENTS (.max %d, .now %d)",
               VM__OPCODE__MAX_ARGUMENTS,
               pOpcode->count_arguments()
         );

         if (pOpcode->count_arguments() > 0)
         {
            if (pOpcode->has_register_arguments)
            {
               this->format_arguments(pOpcode, this->opcode_arguments);
            }
            else
            {
               this->copy_arguments(pOpcode, this->opcode_arguments);
            }
         }

         bool opc_handled = false;
         bool opc_namespace_handled = true;

         INTERNAL(
               "<OpCode:0x%x> RUN (.index %u, .ns %u, .function %u .argument_count %u)\n",
               (uint)pOpcode,
               i,
               pOpcode->ns,
               pOpcode->method,
               pOpcode->argument_count
         );

         switch (pOpcode->ns)
         {
            #ifdef OPCODES__ARGUMENTS__H
            case OPC_NS_ARGUMENTS:
            {
               opc_handled = opcodes::Arguments::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__ARRAY__H
            case OPC_NS_ARRAY:
            {
               opc_handled = opcodes::Array::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__BLOCK__H
            case OPC_NS_BLOCK:
            {
               t::Block* pBlockToRun = NULL;
               opc_handled = opcodes::Block::run(pBlock, this->current_frame, pOpcode, this->opcode_arguments, this->blocks, pBlockToRun);
               if (pBlockToRun != NULL)
               {
                  this->run_block(pBlockToRun, true);
               }
               break;
            }
            #endif

            #ifdef OPCODES__DEBUG__H
            case OPC_NS_DEBUG:
            {
               opc_handled = opcodes::Debug::run(pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__DUMMY__H
            case OPC_NS_DUMMY:
            {
               opc_handled = opcodes::Dummy::run(pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__EXCEPTION__H
            case OPC_NS_EXCEPTION:
            {
               opc_handled = opcodes::Exception::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__INT__H
            case OPC_NS_INT:
            {
               opc_handled = opcodes::Int::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__JUMP__H
            case OPC_NS_JUMP:
            {
               opc_handled = opcodes::Jump::run(pOpcode, this->opcode_arguments, i);
               break;
            }
            #endif

            #ifdef OPCODES__LIST__H
            case OPC_NS_LIST:
            {
               opc_handled = opcodes::List::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            #ifdef OPCODES__REGISTERS__H
            case OPC_NS_REGISTERS:
            {
               opc_handled = opcodes::Registers::run(this->current_frame, pOpcode, this->opcode_arguments);
               break;
            }
            #endif

            default:
               opc_namespace_handled = false;

         }

         #ifdef _DEBUG_
         if (! opc_namespace_handled)
         {
            WARNING("<opcode-namespace:%c> not handled.\n", pOpcode->ns);
         }
         else if (! opc_handled)
         {
            WARNING("<opcode:%c%c> not handled.\n", pOpcode->ns, pOpcode->method);
         }
         #endif

         // Exception handling
         if (this->current_frame->exception != NULL && !this->handle_exception())
         {
            i = pBlock->count();
            this->exit();
            break;
         }
      }

      pBlock->drop();
      ASSERT_NOT_NULL(pBlock->klass);

      if (bAddToStack == true)
      {
         this->call_stack.pop();
      }
   }

   void
   Engine::size_blocks(ulong nCount)
   {
      this->block_count = nCount;
      Memory_ALLOC(this->blocks, t::Block*, nCount);
   }

   void
   Engine::size_classes(ulong nCount)
   {
      this->class_count = nCount;
      Memory_ALLOC(this->classes, vm::Class*, nCount);
   }

   void
   Engine::size_functions(ulong nCount)
   {
      this->function_count = nCount;
      Memory_ALLOC(this->functions, t::Function*, nCount);
   }

   void
   Engine::size_opcodes (uint nCount)
   {
      this->opcode_count = nCount;
      Memory_ALLOC(this->opcodes, vm::OpCode*, nCount);
   }
}
