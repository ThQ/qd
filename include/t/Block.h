#ifndef T__BLOCK__H
#define T__BLOCK__H __FILE__

#include "t/Exception.h"
#include "t/Object.h"
#include "vm/RegisterPool.h"
#include "vm/OpCode.h"

#define T__BLOCK__GET_NAME(pBlock) "??"

namespace t
{
   extern vm::Class cBLOCK;
   /**
    * @brief An executable group of opcodes.
    */
   class Block : public Object
   {
      public: uchar              argument_count;      ///< Number of arguments.
      public: uchar*             argument_types;      ///< The types of the arguments.
      public: Exception*         exception;           ///< A pointer to a @cls{t::Exception} thrown, NULL otherwise.
      public: Block*             exception_handler;   ///< A pointer to @cls{t::Block} used as exception handler, NULL if none.
      public: vm::RegisterPool   registers;           ///< A register manager.
      //public: vm::Stack          stack;               ///< Block's heap.
      public: vm::OpCode**       opcodes;             ///< An array of @cls{vm::OpCode}s.
      public: ulong              opcode_count;        ///< Number of opcodes.

      /**
       * @brief Default constructor.
       */
      public: Block ();

      /**
       * @brief Destructor.
       */
      public: ~Block ();

      /**
       * @brief Deletes a t::Block
       *
       * @param pObject The t::Block to delete.
       */
      public: static void __delete__ (Value pObject);

      /**
       * @brief Creates a new t::Block.
       *
       * @return A pointer to the t::Block created.
       */
      public: static Value __new__ ();

      /**
       * @brief Prints a string representation of a t::Block.
       *
       * @param pObject The t::Block to print.
       */
      public: static void __print__ (Value pObject);

      /**
       * @brief Prints a string representation of a t::Block on a new line.
       *
       * @param pObject The t::Block to print.
       */
      public: static void __print_line__ (Value pObject);

      /**
       * @brief Appends an opcode to the block.
       *
       * @param opc A pointer to a @cls{vm::OpCode} to append.
       * @todo Make this less REALLOC intensive.
       */
      public: void append (vm::OpCode* opc);

      /**
       * @brief Returns the number of opcodes.
       *
       * @return The number of opcodes in this block.
       */
      public: ulong count ();

      /**
       * @brief Sets the arguments.
       *
       * @param nCount How many arguments are passed.
       * @param pArgs Arguments to set.
       */
      public: void define_arguments (uchar nCount, uchar* pArgs);

      /**
       * @brief The real destructor.
       */
      public: void destroy ();

      /**
       * @brief Returns the opcode at @prm{index}.
       *
       * @param index The index at which get the opcode.
       * @return A pointer to a @cls{vm::OpCode} to get.
       */
      public: vm::OpCode* get (ulong index);

      /**
       * @brief Sets the exception handler for the block.
       *
       * @param block A pointer to a @cls{t::Block} to use as an exception handler.
       */
      public: void set_exception_handler (Block* block);

      /**
       * @brief Throws an exception inside the block.
       *
       * @param exception A pointer to a @cls{t::Object} that is a @cls{t::Exception} to throw.
       */
      public: inline void throw_exception (Object* exception)
      {
         Exception::assert(exception);
         this->throw_exception((Exception*)exception);
      }

      /**
       * @brief Throws an exception inside the block.
       *
       * @param exception A pointer to a @cls{t::Exception} to throw.
       */
      public: void throw_exception (Exception* exception);
   };
}

#endif
