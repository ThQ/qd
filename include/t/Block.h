#ifndef T_BLOCK
#define T_BLOCK NS_TYPE::Block

#include "t/Exception.h"
#include "t/Object.h"
#include "vm/Heap.h"
#include "vm/OpCode.h"

namespace NS_TYPE
{
   /**
    * A block is an executable group of opcodes.
    */
   class Block : public T_OBJECT
   {
      public: ULong argc;
      public: T_OBJECT** argv;
      public: T_OBJECT* exception;
      public: Block* exception_handler;
      public: vm::Heap heap;
      public: vm::OpCode** opcodes;
      public: ULong opcode_count;
      public: std::string name;

      public: Block();
      public: ~Block();

      /**
       * Appends an opcode to the block.
       */
      public: void append(vm::OpCode* opc);

      /**
       * Frees the opcode array.
       */
      public: void clear();

      /**
       * Returns the number of opcodes.
       */
      public: ULong count();

      /**
       * Returns the opcode at <index>.
       */
      public: vm::OpCode* get(ULong index);

      /**
       * Sets the exception handler for the block.
       */
      public: void set_exception_handler(Block* block);

      /**
       * Throws an exception inside the block.
       */
      public: void throw_exception(T_OBJECT* exception);

   };
}

#endif
