#include "vm/Engine.h"

namespace NS_VM
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
         T_OBJECT::drop(this->blocks[i]);
      }
      delete this->blocks;
      T_OBJECT::drop_safe(this->current_block);
   }

   void
   Engine::append_block(t::Block* block)
   {
      ++ this->block_count;
      // @TODO: Stop intensive REALLOC
      this->blocks = (t::Block**)REALLOC(this->blocks, sizeof(t::Block*) * this->block_count);
      this->blocks[this->block_count - 1] = block;
      T_OBJECT::pick(block);
   }

   t::Object*
   Engine::build_traceback()
   {
      t::Object* traceback = t::List::build();
      t::List::assert(traceback);
      t::Object::pick(traceback);
      for (ULong i = this->stack.count() - 1 ; i > 0 ; --i)
      {
         t::Object* entry = svm::Map::build();
         t::Map::assert(entry);
         t::Object::pick(entry);
         std::string s_key;
         s_key.assign("function");
         t::Map::set_item(entry, s_key, this->stack.blocks[i]->name);
         t::List::append(traceback, entry);
      }
      return (t::Object*)traceback;
   }

   void
   Engine::clear_arguments(UInt& argc, t::Object**& argv)
   {
      for (UInt i = 0 ; i < argc ; ++ i)
      {
         t::Object::drop_safe(argv[i]);
      }
      // @TODO: Free / delete / something ?
      argv = 0;
      argc = 0;
   }

   void
   Engine::clear_blocks()
   {
      this->block_count = 0;
      free(this->blocks);
   }

   t::Object*
   Engine::call(std::string method_name, UInt argc, t::Object**& argv)
   {
      t::Object* result = NULL;
      t::CoreFunction* f = (t::CoreFunction*)this->functions.get((std::string)method_name);

      if  (f != NULL)
      {
         if (check_arguments(f, argc, argv))
         {
            NS_VM::MethodPointer ptr = (NS_VM::MethodPointer)f->function_pointer;
            result = ptr(argc, argv);
         }
      }

      if (result == NULL)
      {
         result = t::gNULL;
      }

      T_OBJECT::assert_not_null(result);

      return result;
   }

   t::Object*
   Engine::call_object(std::string method_name, UInt argc, t::Object**& argv)
   {
      #ifdef _SHOW_INTERNAL_
      INTERNAL("<%s>.<%s> (", ((t::Class*)argv[0]->cls)->name.c_str(), method_name.c_str());
      for (ULong i = 0 ; i < argc ; ++i)
      {
         if (i != 0)
         {
            printf(", ");
         }
         printf("%s[@%lu]", ((t::Class*)argv[i]->cls)->name.c_str(), (ULong)argv[i]);
      }
      printf(") [parameters=%u]\n", argc);
      #endif

      t::Class* cls = (t::Class*)argv[0]->cls;
      t::Class::assert(cls);
      t::Object::pick(cls);

      t::Object* result = NULL;

      t::Function* f = this->classes.get_method(((t::Class*)argv[0]->cls), method_name);
      t::Object::pick(f);

      if (f != NULL)
      {
         if (this->check_arguments(f, argc, argv))
         {
            // TODO: Check the result object type
            if (f->is_user == true)
            {
               t::Object::assert_not_null(((t::UserFunction*)f)->block);
               this->heap.append(argc, argv);
               this->run_block(((t::UserFunction*)f)->block);
               if (this->heap.item_count >= 1)
               {
                  result = this->heap.get(0);
                  this->heap.pop();
               }
               else
               {
                  result = t::gNULL;
               }
            }
            else
            {
               NS_VM::ClassMethodPointer ptr = (NS_VM::ClassMethodPointer)((t::CoreFunction*)f)->function_pointer;
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
      t::Object::drop(f);
      t::Object::drop(cls);

      if (result == NULL)
      {
         WARNING(
            "Result of function <%s>.<%s> is C's <null> instead of <svm::Null>.\n",
            cls->name.c_str(),
            method_name.c_str()
         );
         result = t::gNULL;
      }

      return result;

   }

   bool
   Engine::check_arguments(int argc, ...)
   {
      bool result = true;
      va_list l;
      va_start(l, argc);
      for (int i = 0 ; i < argc ; i +=2)
      {
         t::Object* obj = va_arg(l, t::Object*);
         t::Class* cls = va_arg(l, t::Class*);
         if (obj->cls != cls)
         {
            std::string s_msg;
            s_msg.assign("Expected type<");
            s_msg.append(cls->name);
            s_msg.append("> but got <");
            s_msg.append(((svm::Class*)obj->cls)->name);
            s_msg.append(">.");

            t::Object* msg = t::String::build(s_msg);
            t::Exception* e = new t::Exception();
            e->set_class(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
            t::Exception::set_message(e, msg);
            this->throw_exception((t::Object*)e);

            result = false;
            break;
         }
      }
      va_end(l);
      return result;
   }

   bool
   Engine::check_arguments(t::Function* f, UInt argc, t::Object**& argv)
   {
      bool result = true;
      if (argc != f->arguments_count)
      {
         // TODO: Throw an exception instead !
         WARNING("Bad argument count, got <%d> instead of <%d>\n", argc, f->arguments_count);
      }
      else
      {
         //DEBUG("Testing arguments\n");
         for (ULong i = 0; i < f->arguments_count ; ++ i)
         {
            //DEBUG("Testing arg #%d/%d(%d)\n", i, argc, f->arguments_count);
            t::Variable* expected_type = ((t::Variable*)f->arguments[i]);
            t::Object::pick(expected_type);
            t::Object* given_type = argv[i]->cls;
            t::Object::pick(given_type);

            t::Variable* func_var_arg = ((t::Variable*)f->arguments[i])->object_type;
            result = t::Class::is_child_of(argv[i]->cls, func_var_arg);
            if (result != true)
            {
               WARNING(
                  "Bad argument type: <%s@%lu is not child of type <%s@%lu>.\n",
                  ((t::Class*)argv[i]->cls)->name.c_str(),
                  (ULong)argv[i]->cls,
                  ((t::Class*)((t::Variable*)f->arguments[i])->object_type)->name.c_str(),
                  (ULong)((t::Variable*)f->arguments[i])->object_type
               );

               // TODO: Throw an exception or what ?
               //svm::throw_bad_type(((svm::Variable*)f->arguments[i])->object_type, argv[i]->cls);
               break;
            }

            t::Object::drop(expected_type);
            t::Object::drop(given_type);
         }
      }

      return result;
   }

   void
   Engine::exit()
   {
      // @TODO: Make it a real exit() !
   }

   t::Block*
   Engine::find_nearest_exception_handler()
   {
      t::Block* result = NULL;
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

   t::Block*
   Engine::get_block(std::string name)
   {
      //INTERNAL("Engine::get_block(%s)\n", name.c_str());
      t::Block* result = NULL;
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
   Engine::run_block(t::Block* block, bool add_to_stack)
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
            t::String::assert(block->argv[i]);
            t::Object* obj = this->heap.pick_last_and_pop();

            t::Class* cls = (t::Class*)obj->cls;
            #ifdef _DEBUG_
            if (cls->name != ((t::String*)block->argv[i])->value)
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
      ASSERT(block != NULL, "Cannot use a <NULL> t::Block*.\n");

      t::Object::drop_safe(this->current_block);
      this->current_block = block;
      t::Object::pick(block);

      if (add_to_stack == true)
      {
         this->stack.append(block);
      }

      // Execute each opcode in this block
      t::OpCode* opc;
      for (ULong i = 0 ; i < block->count() ; ++i)
      {
         //INTERNAL("BLOCK LOOP\n");
         opc = block->get(i);
         t::Object::assert_not_null(opc);
         t::Object** args;
         //INTERNAL("Make empty object array\n");
         t::make_empty_object_array(args, opc->argc);

         // If opcode have arguments, replace each HeapObject by its real value
         //INTERNAL("Passing through arguments\n");
         for (ULong j = 0 ; j < opc->argc ; ++j)
         {
            //INTERNAL("arg %lu\n", j);
            t::Object::assert_not_null(opc->argv[j]);
            if (opc->argv[j]->cls == t::tHEAP_OBJECT)
            {
               t::HeapObject* hobj = (t::HeapObject*)opc->argv[j];
               args[j] = this->current_block->heap.get(hobj->position);
            }
            else
            {
               args[j] = opc->argv[j];
            }
            t::Object::assert_not_null(args[j]);
            t::Object::pick(args[j]);
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
               t::Object* o = args[k];
               t::Object::pick(o);
               if (k != 0)
               {
                  printf(", ");
               }
               printf("%lu/%d @%lu ::", (k+1), opc->argc, (ULong)o);
               if (o->cls != NULL)
               {
                  printf("%s", ((t::Class*)o->cls)->name.c_str());
               }
               else
               {
                  printf("<UnknownClass>");
               }

               t::Object::drop(o);
            }
            printf(")\n");
         }
         #endif

         t::Object::assert_not_null(this->current_block);
         t::Object::assert_not_null(block);

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

         // EXCEPTION HANDLING
         // ------------------
         // If current opcode has an exception, try to find an exception handler
         // (starting in the current block and going up in the stack) and run it,
         // otherwise just die printing a stacktrace.
         if (this->current_block->exception != NULL)
         {
            t::Block* exception_handler = this->find_nearest_exception_handler();
            if (exception_handler != NULL)
            {
               t::Object::assert_not_null(exception_handler);
               this->run_block(exception_handler);
            }
            else
            {
               t::Exception* e = (t::Exception*)this->current_block->exception;
               t::Class* e_cls = (t::Class*)this->current_block->exception->cls;
               t::Object::assert_not_null(e_cls);
               printf("[Uncaught exception]\n%s: ", e_cls->name.c_str());
               t::UnicodeString::print((svm::UnicodeString*)e->message);
               printf("\n");
               this->build_traceback();
               i = block->count();
               this->exit();
               break;
            }
         }

         for (ULong j = 0 ; j < opc->argc ; ++j)
         {
            t::Object::assert_not_null(args[j]);
            t::Object::drop(args[j]);
         }
         delete[] args;
         //opc = opc->next_opcode;
         // TODO: Problem here ! Damn'it ! Reference counting is great ! << WTF ?
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
      t::Block* block = this->get_block(s_main);

      ASSERT(block != NULL, "No <MAIN> block found.");
      this->run_block(block);

      INTERNAL("/ <%s> : Running file...\n", file_path);
   }

   void
   Engine::throw_exception(t::Object* exception)
   {
      t::Object::assert_not_null(this->current_block);
      this->current_block->throw_exception(exception);
   }
}
