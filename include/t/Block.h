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

      /**
       * Constructor.
       */
      public: Block();

      /**
       * Destructor.
       */
      public: ~Block();

      /**
       * Appends an opcode to the block.
       *
       * @param opc A pointer to a vm::OpCode to append.
       */
      public: void append(vm::OpCode* opc);

      /**
       * Frees the opcode array.
       */
      public: void clear();

      /**
       * Returns the number of opcodes.
       *
       * @return The number of opcodes in this block.
       */
      public: ULong count();

      /**
       * Returns the opcode at [index].
       *
       * @param index The index at which get the opcode.
       * @return A pointer to a vm::OpCode to get.
       */
      public: vm::OpCode* get(ULong index);

      /**
       * Sets the exception handler for the block.
       *
       * @param block A pointer to a @class{t::Block} to use as an exception handler.
       */
      public: void set_exception_handler(Block* block);

      /**
       * Throws an exception inside the block.
       *
       * @param exception A pointer to a @class{t::Object} that is a @class{t::Exception} to throw.
       */
      public: inline void throw_exception(T_OBJECT* exception)
      {
         T_EXCEPTION::assert(exception);
         this->throw_exception((T_EXCEPTION*)exception);
      }

      /**
       * Throws an exception inside the block.
       *
       * @param exception A pointer to a @class{t::Exception} to throw.
       */
      public: void throw_exception(T_EXCEPTION* exception);

   };
}

#endif
