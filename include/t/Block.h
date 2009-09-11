#ifndef T__BLOCK__H
#define T__BLOCK__H __FILE__

#include "t/Object.h"
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
      protected: t::Value*       arguments;
      public: u1                 argument_count;      ///< Number of arguments.
      public: uchar*             argument_types;      ///< The types of the arguments.
      public: vm::OpCode**       opcodes;             ///< An array of @cls{vm::OpCode}s.
      public: uint               opcode_count;        ///< Number of opcodes.

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

      public: inline uint count_arguments ()
      {
         return this->argument_count;
      }

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
      public: inline vm::OpCode* get (uint nIndex)
      {
         ASSERT(
               nIndex < this->opcode_count,
               "[svm::Block::get] Index [%u] out of range [0:%u].\n",
               nIndex,
               this->opcode_count -1
         );

         return this->opcodes[nIndex];
      }

      public: inline t::Value get_argument (uchar nIndex)
      {
         return this->arguments[nIndex];
      }

      public: inline char* get_file_name ()
      {
         return (char*)"??";
      }

      public: inline u3 get_line_number ()
      {
         return 0;
      }

      public: inline char* get_name ()
      {
         return (char*)"??";
      }

      public: void print_arguments ();

      public: inline void set_argument (uchar nIndex, t::Value pVal)
      {
         this->arguments[nIndex] = pVal;
      }
   };
}

#endif
