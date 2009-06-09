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
#include "t/HeapObject.h"
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
#include "vm/OpCode.h"
#include "vm/Parser.h"
#include "vm/Stack.h"
#include "util/Int.h"
#include "util/List.h"
// @MODULES[INCLUDE]

#define SVM_METHOD(name) t::Object* name(vm::Engine* engine, int argc, t::Object** argv)
#define SVM_CLASS_METHOD(name) t::Object* name(vm::Engine* engine, t::Object* self, int argc, t::Object** argv)

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

namespace vm
{

   /**
    * The Real Virtual Machine.
    *
    * It contains all the classes, the functions, the blocks, etc.
    */
   class Engine
   {
      public: t::Block** blocks;       ///< An array of @cls{t::Block}.
      public: UInt block_count;        ///< The number of blocks.
      public: ClassTable classes;      ///< A class table.
      public: t::Block* current_block; ///< The block being currently run.
      public: FunctionTable functions; ///< A function table.
      public: Heap heap;               ///< Global heap, also called the swap.
      public: Stack stack;             ///< Call stack.

      /**
       * Constructor.
       */
      public: Engine();

      /**
       * Destructor.
       */
      public: ~Engine();

      /**
       * Appends a pointer to a t::Block to [blocks].
       *
       * @param block The block to append.
       */
      public: void append_block(t::Block* block);

      /**
       * Creates a t::List containing a traceback.
       *
       * @return A pointer to a t::List containing the traceback.
       */
      public: t::Object* build_traceback();

      /**
       * Calls a function.
       *
       * @param method_name Name of the function.
       * @param argc Number of arguments passed.
       * @param argv An array of pointers to t::Object's which are the arguments passed.
       * @return A pointer to a t::Object returned by the function.
       */
      public: t::Object* call(std::string method_name, UInt argc, t::Object**& argv);

      /**
       * Calls an instance method.
       *
       * @param method_name Name of the instance method.
       * @param argc Number of arguments passed.
       * @param argv An array of pointers to t::Object's which are the arguments passed. The first one being the object to call.
       * @return A pointer to a t::Object returned by the function.
       */
      public: t::Object* call_object(std::string method_name, UInt argc, t::Object**& argv);

      /**
       * Checks if an array of t::Object's matches the list of arguments needed by a function.
       *
       * @param f A pointer to a t::Function to check against.
       * @param argc The number of arguments to check.
       * @param argv The arguments to check.
       * @return true if argv matches f.
       */
      public: bool check_arguments(t::Function* f, UInt argc, t::Object**& argv);

      /**
       * Checks if a list of t::Object's are of type of a list of t::Class's
       *
       * @param argc A number of pairs (object, type) to check.
       * @return true if each pair matches.
       */
      public: bool check_arguments(int argc, ...);

      /**
       * Replaces [argc] arguments of [argv] with NULL.
       *
       * @param argc How many arguments to clear.
       * @param argv An array of pointer to t::Object's to clear.
       */
      public: void clear_arguments(UInt& argc, t::Object**& argv);

      /**
       * Clears [blocks].
       */
      public: void clear_blocks();

      /**
       * Exits the currently running engine.
       */
      public: void exit();

      /**
       * Going up the stack from the current frame to find an exception handler.
      *
      * @return An exception handler block if found, NULL otherwise.
      */
      public: t::Block* find_nearest_exception_handler();

      /**
       * Get the block associated with the name [name].
       *
       * @param name The block's name to search.
       * @return The block if found, NULL otherwise.
       */
      public: t::Block* get_block(std::string name);

      /**
       * Imports the swap content into a block's stack.
       *
       * @param block A pointer to a t::Block that is importing the swap.
       */
      public: void import_swap(t::Block* block);

      /**
       * Makes an empty array of t::Object's of length [count].
       *
       * @param obj An array of pointer to t::Object's.
       * @param count The length of the new array.
       */
      public: static void make_empty_object_array(t::Object**& obj, UInt count);

      /**
       * Prints information about the engine to the console.
       */
      public: static void print_version();

      /**
       * Runs each opcode of a [block].
       *
       * @param block The block to run.
       * @param add_to_stack Wether add this block to the call stack.
       */
      public: void run_block(t::Block* block, bool add_to_stack = true);
      // [!opcodes:prototypes]

      /**
       * Reads the file at [file_path], parses it and runs its opcodes.
       *
       * @param file_path The path to the file to run.
       */
      public: void run_file(const char* file_path);

      /**
       * Throws a t::Exception.
       *
       * @param exception The exception to throw.
       */
      public: void throw_exception(t::Object* exception);
   };

   // @TODO: Shouldn't be elsewhere ? in NS_T ?
   typedef t::Object*(*MethodPointer)(int argc, t::Object** argv);
   typedef t::Object*(*ClassMethodPointer)(vm::Engine* engine, t::Object* &self, int argc, t::Object** argv);
}

#endif
