#include "svm/Engine.h"

namespace svm
{
   Engine::Engine()
   {
      this->current_block = NULL;
      this->blocks = NULL;
      this->block_count = 0;
   }

   Engine::~Engine()
   {
      for (ULong i = 0 ; i < this->block_count ; ++ i)
      {
         SVM_DROP(this->blocks[i]);
      }
      delete this->blocks;
      SVM_DROP_SAFE(this->current_block);
   }

   void
   Engine::append_block(svm::Block* block)
   {
      ++ this->block_count;
      this->blocks = (svm::Block**)REALLOC(this->blocks, sizeof(svm::Block*) * this->block_count);
      this->blocks[this->block_count - 1] = block;
      SVM_PICK(block);
   }

   svm::Object*
   Engine::build_traceback()
   {
      svm::Object* traceback = svm::List::build();
      SVM_ASSERT_LIST(traceback);
      SVM_PICK(traceback);
      for (ULong i = this->stack.count() - 1 ; i > 0 ; --i)
      {
         svm::Object* entry = svm::Map::build();
         SVM_ASSERT_MAP(entry);
         SVM_PICK(entry);
         std::string s_key;
         s_key.assign("function");
         svm::Map::set_item(entry, s_key, this->stack.blocks[i]->name);
         svm::List::append(traceback, entry);
      }
      return (svm::Object*)traceback;
   }

   void
   Engine::clear_arguments(UInt& argc, svm::Object**& argv)
   {
      for (UInt i = 0 ; i < argc ; ++ i)
      {
         SVM_DROP_SAFE(argv[i]);
      }
      argv = 0;
      argc = 0;
   }

   void
   Engine::clear_blocks()
   {
      this->block_count = 0;
      free(this->blocks);
   }

   svm::Object*
   Engine::call(std::string method_name, UInt argc, svm::Object**& argv)
   {
      svm::Object* result = NULL;
      svm::CoreFunction* f = (svm::CoreFunction*)this->functions.get((std::string)method_name);

      if  (f != NULL)
      {
         if (check_arguments(f, argc, argv))
         {
            svm::MethodPointer ptr = (svm::MethodPointer)f->function_pointer;
            result = ptr(argc, argv);
         }
      }

      if (result == NULL)
      {
         result = svm::Null;
      }

      ASSERT_NOT_NULL(result);

      return result;
   }

   svm::Object*
   Engine::call_object(std::string method_name, UInt argc, svm::Object**& argv)
   {
      #ifdef _SHOW_INTERNAL_
      INTERNAL("<%s>.<%s> (", ((svm::Class*)argv[0]->cls)->name.c_str(), method_name.c_str());
      for (ULong i = 0 ; i < argc ; ++i)
      {
         if (i != 0)
         {
            printf(", ");
         }
         printf("%s[@%lu]", ((svm::Class*)argv[i]->cls)->name.c_str(), (ULong)argv[i]);
      }
      printf(") [parameters=%u]\n", argc);
      #endif

      svm::Class* cls = (svm::Class*)argv[0]->cls;
      SVM_ASSERT_CLASS(cls);
      SVM_PICK(cls);

      svm::Object* result = NULL;

      svm::Function* f = this->classes.get_method(((svm::Class*)argv[0]->cls), method_name);
      SVM_PICK(f);

      if (f != NULL)
      {
         if (this->check_arguments(f, argc, argv))
         {
            // TODO: Check the result object type
            if (f->is_user == true)
            {
               SVM_ASSERT_NOT_NULL(((svm::UserFunction*)f)->block);
               this->heap.append(argc, argv);
               this->run_block(((svm::UserFunction*)f)->block);
               if (this->heap.item_count >= 1)
               {
                  result = this->heap.get(0);
                  this->heap.pop();
               }
               else
               {
                  result = svm::Null;
               }
            }
            else
            {
               svm::ClassMethodPointer ptr = (svm::ClassMethodPointer)((svm::CoreFunction*)f)->function_pointer;
               result = ptr(this, argv[0], argc, argv);
            }
         }
      }
      else
      {
         #ifdef __DEBUG__
         WARNING("Method not found : <%s>.<%s>.\n", cls->name.c_str(), method_name.c_str());
         #endif
         //this->throw_ethrow_class_method_not_found(argv[0], *method_name);
      }
      SVM_DROP(f);
      SVM_DROP(cls);

      if (result == NULL)
      {
         WARNING(
            "Result of function <%s>.<%s> is C's <null> instead of <svm::Null>.\n",
            cls->name.c_str(),
            method_name.c_str()
         );
         result = svm::Null;
      }

      return result;

   }

   bool
   Engine::check_arguments(int argc, ...)
   {
      SVM_ASSERT_NOT_NULL(svm::bad_argument_type_exception_type);
      bool result = true;
      va_list l;
      va_start(l, argc);
      for (int i = 0 ; i < argc ; i +=2)
      {
         svm::Object* obj = va_arg(l, svm::Object*);
         svm::Class* cls = va_arg(l, svm::Class*);
         if (obj->cls != cls)
         {
            std::string s_msg;
            s_msg.assign("Expected type<");
            s_msg.append(cls->name);
            s_msg.append("> but got <");
            s_msg.append(((svm::Class*)obj->cls)->name);
            s_msg.append(">.");

            svm::Object* msg = svm::String::build(s_msg);
            svm::Exception* e = new svm::Exception();
            e->set_class(svm::bad_argument_type_exception_type);
            svm::Exception::set_message(e, msg);
            this->throw_exception((Object*)e);

            result = false;
            break;
         }
      }
      va_end(l);
      return result;
   }

   bool
   Engine::check_arguments(svm::Function* f, UInt argc, svm::Object**& argv)
   {
      bool result = true;
      if (argc != f->arguments_count)
      {
         WARNING("Bad argument count, got <%d> instead of <%d>\n", argc, f->arguments_count);
         // TODO: Throw an exception !
         //svm::throw_bad_argument_count(argc, f->arguments_count);
      }
      else
      {
         //DEBUG("Testing arguments\n");
         for (ULong i = 0; i < f->arguments_count ; ++ i)
         {
            //DEBUG("Testing arg #%d/%d(%d)\n", i, argc, f->arguments_count);
            svm::Variable* expected_type = ((svm::Variable*)f->arguments[i]);
            SVM_PICK(expected_type);
            svm::Object* given_type = argv[i]->cls;
            SVM_PICK(given_type);

            result = svm::Class::is_child_of(argv[i]->cls, ((svm::Variable*)f->arguments[i])->object_type);
            if (result != true)
            {
               WARNING(
                  "Bad argument type: <%s@%lu is not child of type <%s@%lu>.\n",
                  ((svm::Class*)argv[i]->cls)->name.c_str(),
                  (ULong)argv[i]->cls,
                  ((svm::Class*)((svm::Variable*)f->arguments[i])->object_type)->name.c_str(),
                  (ULong)((svm::Variable*)f->arguments[i])->object_type
               );

               // TODO: Throw an exception or what ?
               //svm::throw_bad_type(((svm::Variable*)f->arguments[i])->object_type, argv[i]->cls);
               break;
            }

            SVM_DROP(expected_type);
            SVM_DROP(given_type);
         }
      }

      return result;
   }

   void
   Engine::exit()
   {

   }

   /**
    * Going up the stack from the current frame to find an exception handler.
    *
    * @return An exception handler block if found, NULL otherwise.
    **/
   svm::Block*
   Engine::find_nearest_exception_handler()
   {
      svm::Block* result = NULL;
      if (this->stack.count() > 0)
      {
         for (ULong i = this->stack.count() - 1; i > 0 ; --i)
         {
            if (this->stack.get(i)->exception_handler != NULL)
            {
               result = this->stack.get(i)->exception_handler;
               break;
            }
         }
      }
      return result;
   }

   /**
    * Get the block associated with the name <name>.
    *
    * @return The block if found, NULL otherwise.
    **/
   svm::Block*
   Engine::get_block(std::string name)
   {
      //INTERNAL("Engine::get_block(%s)\n", name.c_str());
      svm::Block* result = NULL;
      for (ULong i = 0 ; i < this->block_count ; ++ i)
      {
         if (this->blocks[i]->name.compare(name) == 0)
         {
            result = this->blocks[i];
            break;
         }
      }
      //INTERNAL("/ Engine::get_block(%s) = %lu\n", result->name.c_str(), (ULong)result);
      return result;
   }

   void
   Engine::import_swap(Block* block)
   {
      ULong swap_len = this->heap.count();
      for (ULong i = 0 ; i < swap_len ; ++i)
      {
         block->heap.append(this->heap.get(0));
         this->heap.pop(1);
      }
   }

   void
   Engine::make_empty_object_array(svm::Object**& obj, UInt count)
   {
      switch (count)
      {
         case 0:
            obj = NULL;
            break;

         default:
            obj = new svm::Object*[count];
      }
   }

   // -----------------------------------------
   // This is a placeholder. DO NOT REMOVE!
   // -----------------------------------------
   // [!opcodes:definitions]
   // -----------------------------------------

   void
   Engine::run_block(svm::Block* block, bool add_to_stack)
   {
      INTERNAL(
         "<block:%s @%lu> [%lu opcodes] : Running ... (heap_size=%lu)\n",
         block->name.c_str(),
         (ULong)block,
         block->count(),
         this->heap.count()
      );
      ASSERT(this->heap.count() >= block->argc, "There must be enough in the heap to run this block.\n");

      // If block have arguments, with HeapObject's replaced by their real values
      if (block->argc > 0)
      {
         for (long i = (long)block->argc - 1 ; i >= 0 ; -- i)
         {
            SVM_ASSERT_STRING(block->argv[i]);
            svm::Object* obj = this->heap.pick_last_and_pop();

            svm::Class* cls = (svm::Class*)obj->cls;
            #ifdef _DEBUG_
            if (cls->name != ((svm::String*)block->argv[i])->value)
            {
               WARNING(
                  "Bad block parameter type, expected <%s> but got <%s>.\n",
                  ((svm::String*)block->argv[i])->value.c_str(),
                  cls->name.c_str()
               );
            }
            #endif
            block->heap.append(obj);
         }
      }
      ASSERT(block != NULL, "Cannot use a <NULL> svm::Block*.\n");

      SVM_DROP_SAFE(this->current_block);
      this->current_block = block;
      SVM_PICK(block);

      if (add_to_stack == true)
      {
         this->stack.append(block);
      }

      // Execute each opcode on this block
      svm::OpCode* opc;
      for (ULong i = 0 ; i < block->count() ; ++i)
      {
         //INTERNAL("BLOCK LOOP\n");
         opc = block->get(i);
         ASSERT_NOT_NULL(opc);
         svm::Object** args;
         //INTERNAL("Make empty object array\n");
         Engine::make_empty_object_array(args, opc->argc);

         // If opcode have arguments, replace each HeapObject by its real value
         //INTERNAL("Passing through arguments\n");
         for (ULong j = 0 ; j < opc->argc ; ++j)
         {
            //INTERNAL("arg %lu\n", j);
            ASSERT_NOT_NULL(opc->argv[j]);
            if (opc->argv[j]->cls == svm::heap_object_type)
            {
               svm::HeapObject* hobj = (svm::HeapObject*)opc->argv[j];
               args[j] = this->current_block->heap.get(hobj->position);
            }
            else
            {
               args[j] = opc->argv[j];
            }
            ASSERT_NOT_NULL(args[j]);
            SVM_PICK(args[j]);
         }
         //INTERNAL("// Passing through arguments\n");

         //INTERNAL("Print info about opcode\n");
         #ifdef _SHOW_INTERNAL_
         if (opc->argc == 0)
         {
            INTERNAL("Running <opcode:%c%c> [%lu/%lu] \n", opc->type, opc->method, i, block->count());
         }
         else
         {
            //INTERNAL("opcode has arguments\n");
            INTERNAL("Running <opcode:%c%c> [%lu/%lu] (", opc->type, opc->method, i, block->count());
            //INTERNAL("looping through opcode args\n");
            for (ULong k = 0 ; k < opc->argc ; ++k)
            {
               svm::Object* o = args[k];
               SVM_PICK(o);
               if (k != 0)
               {
                  printf(", ");
               }
               printf("%lu/%d @%lu ::", (k+1), opc->argc, (ULong)o);
               if (o->cls != NULL)
               {
                  printf("%s", ((svm::Class*)o->cls)->name.c_str());
               }
               else
               {
                  printf("<UnknownClass>");
               }

               SVM_DROP(o);
            }
            printf(")\n");
         }
         #endif

         //INTERNAL("Some block assertions\n");
         SVM_ASSERT_NOT_NULL(this->current_block);
         SVM_ASSERT_NOT_NULL(block);

         bool opc_handled = false;
         bool opc_namespace_handled = false;
         //ULong i = 0 ; // TODO: Ugly lazy trick, damn' I'm lazy, yeah < What the fuck ?
         //INTERNAL("SWITCH OPC->TYPE\n");
         switch (opc->type)
         {
            // --------------------------------------
            // This is a place holder, DO NOT REMOVE !
            // --------------------------------------
            // [!opcodes:ns_switch]
            // --------------------------------------
            case OPC_NS_NIL: opc_namespace_handled = true; opc_handled = true; break;
         }
         #ifdef _DEBUG_
         if (! opc_namespace_handled)
         {
            WARNING("<opcode-namespace:%c> not handled.\n", opc->type);
         }
         if (! opc_handled)
         {
            WARNING("<opcode:%c%c> not handled.\n", opc->type, opc->method);
         }
         #endif

         // EXECPTION HANDLING
         // If current opcode has an exception, try to find an exception handler
         // (starting in the current block and going up in the stack) and run it,
         // otherwise just die printing a stacktrace.
         if (this->current_block->exception != NULL)
         {
            svm::Block* exception_handler = this->find_nearest_exception_handler();
            if (exception_handler != NULL)
            {
               SVM_ASSERT_NOT_NULL(exception_handler);
               this->run_block(exception_handler);
            }
            else
            {
               svm::Exception* e = (svm::Exception*)this->current_block->exception;
               svm::Class* e_cls = (svm::Class*)this->current_block->exception->cls;
               SVM_ASSERT_NOT_NULL(e_cls);
               printf("[Uncaught exception]\n%s: ", e_cls->name.c_str());
               svm::UString::print((svm::UString*)e->message);
               printf("\n");
               this->build_traceback();
               i = block->count();
               this->exit();
               break;
            }
         }

         for (ULong j = 0 ; j < opc->argc ; ++j)
         {
            ASSERT_NOT_NULL(args[j]);
            SVM_DROP(args[j]);
         }
         delete[] args;
         //opc = opc->next_opcode;
         // TODO: Problem here ! Damn'it ! Reference counting is great !
         //delete args;
      }
   }

   void
   Engine::run_file(const char* file_path)
   {
      INTERNAL("<%s> : Running file...\n", file_path);

      std::fstream file(file_path, std::fstream::in);
      std::string content = "";

      char buff[128] = "";

      while (!file.eof())
      {
         file.read(buff, 127);
         content.append(buff, 0, file.gcount());
      }

      file.close();

      this->block_count = Parser::parse_lines(content, this->blocks);

      std::string s_main;
      s_main.assign("MAIN");
      svm::Block* block = this->get_block(s_main);

      ASSERT(block != NULL, "No <MAIN> block found.");
      this->run_block(block);

      INTERNAL("/ <%s> : Running file...\n", file_path);
   }

   void
   Engine::throw_exception(svm::Object* exception)
   {
      SVM_ASSERT_NOT_NULL(this->current_block);
      this->current_block->throw_exception(exception);
   }
}
