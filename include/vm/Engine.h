#ifndef ENGINE_H
#define ENGINE_H


#include <fstream>
#include <math.h>
#include <string>
#include <unicode/unistr.h>

#include "t/Array.h"
#include "t/Block.h"
#include "t/Bool.h"
#include "t/Class.h"
#include "t/Exception.h"
#include "t/Float.h"
#include "t/Function.h"
#include "t/Int.h"
#include "t/List.h"
#include "t/Map.h"
#include "t/Object.h"
#include "t/String.h"
#include "t/UnicodeString.h"
#include "t/UserObject.h"
#include "vm/ClassTable.h"
#include "vm/FunctionTable.h"
#include "vm/Heap.h"
#include "vm/HeapObject.h"
#include "vm/IntUtil.h"
#include "vm/ListUtil.h"
#include "vm/OpCode.h"
#include "vm/Parser.h"
#include "vm/Stack.h"
// @MODULES[INCLUDE]

#define SVM_METHOD(name) t::Object* name(svm::Engine* engine, int argc, t::Object** argv)
#define SVM_CLASS_METHOD(name) t::Object* name(svm::Engine* engine, t::Object* self, int argc, t::Object** argv)

#define SVM_THROW_CLASS_NOT_FOUND_EXCEPTION(eng, cls) \
   DEPRECATED(); \
   t::Object* e = t::Exception::build(); \
   e->set_class(t::tCLASS_NOT_FOUND_EXCEPTION); \
   eng->throw_exception(e);

#define SVM_THROW_INDEX_OUT_OF_RANGE_EXCEPTION(engine, index, count) \
   DEPRECATED(); \
   t::Object* e = t::Exception::build(); \
   e->set_class(t::tINDEX_OUT_OF_RANGE_EXCEPTION); \
   engine->throw_exception(e);

namespace NS_VM
{
   class Engine
   {
      public: t::Block** blocks;
      public: UInt block_count;
      public: ClassTable classes;
      public: t::Block* current_block;
      public: FunctionTable functions;
      public: Heap heap;
      public: Stack stack;

      public: Engine();
      public: ~Engine();
      public: void append_block(t::Block* block);
      public: t::Object* build_traceback();
      public: t::Object* call(std::string method_name, UInt argc, t::Object**& argv);
      public: t::Object* call_object(std::string method_name, UInt argc, t::Object**& argv);
      public: bool check_arguments(t::Function* f, UInt argc, t::Object**& argv);
      public: bool check_arguments(int argc, ...);
      public: void clear_arguments(UInt& argc, t::Object**& argv);
      public: void clear_blocks();

      /**
       * Exits the currently running engine.
       */
      public: void exit();

      /**
       * Going up the stack from the current frame to find an exception handler.
      *
      * \return An exception handler block if found, NULL otherwise.
      */
      public: t::Block* find_nearest_exception_handler();

      /**
       * Get the block associated with the name <name>.
       *
       * \return The block if found, NULL otherwise.
       */
      public: t::Block* get_block(std::string name);

      /**
       * Imports the swap content into a block's stack.
       */
      public: void import_swap(t::Block* block);

      /**
       * Makes an empty array of t::Object's of length <count>.
       */
      public: static void make_empty_object_array(t::Object**& obj, UInt count);

      /**
       * Runs each opcode of a <block>.
       */
      public: void run_block(t::Block* block, bool add_to_stack = true);
      // [!opcodes:prototypes]

      /**
       * Reads the file at <file_path>, parses it and runs its opcodes.
       */
      public: void run_file(const char* file_path);

      /**
       * Throws a t::Exception.
       */
      public: void throw_exception(t::Object* exception);
   };

   // @TODO: Shouldn't be elsewhere ? in NS_T ?
   typedef Object*(*MethodPointer)(int argc, t::Object** argv);
   typedef Object*(*ClassMethodPointer)(Engine* engine, t::Object* &self, int argc, t::Object** argv);
}

#endif
