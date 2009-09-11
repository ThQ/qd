#ifndef VM__ENGINE__H
#define VM__ENGINE__H __FILE__


#include <fstream>
#include <math.h>
#include <string>

#include "opcodes/Arguments.h"
#include "opcodes/Array.h"
#include "opcodes/Block.h"
#include "opcodes/Debug.h"
#include "opcodes/Dummy.h"
#include "opcodes/Exception.h"
#include "opcodes/Int.h"
#include "opcodes/List.h"
#include "opcodes/Jump.h"
#include "opcodes/Registers.h"

#include "t/Block.h"
#include "t/CoreFunction.h"
#include "t/Exception.h"
#include "t/Function.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/RegisterObject.h"
#include "t/String.h"
#include "t/UserFunction.h"

#include "vm/CallStack.h"
#include "vm/Class.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"

namespace vm
{
   /**
    * @brief The Real Virtual Machine.
    *
    * It contains all the classes, the functions, the blocks, etc.
    */
   class Engine
   {
      public: t::Block**      blocks;           ///< An array of @cls{t::Block}.
      public: t::Value*       block_arguments;  ///< Arguments of a block. (Cannot be in t::Block, because a block can call himself)
      public: ulong           block_count;      ///< The number of blocks.
      public: CallStack       call_stack;       ///< Call stack.
      public: vm::Class**     classes;          ///< A class table.
      public: ulong           class_count;      ///< How many classes.
      public: t::Block*       current_block;    ///< The block being currently run.
      public: vm::Frame*      current_frame;    ///< The current frame.
      public: t::Function**   functions;        ///< A function table.
      public: ulong           function_count;   ///< How many functions.
      public: vm::OpCode**    opcodes;          ///< An array of @cls{vm::OpCode}.
                                                ///< We store all the opcodes here,
                                                ///< and not in t::Block* because it lets
                                                ///< us make an alloc once and for all opcodes,
                                                ///< intead of a lot of small ones.
      public: t::Value*       opcode_arguments; ///< An array of t::Value's that will contain the formated arguments
                                                ///< for an opcode.
      public: uint            opcode_count;     ///< The number of opcodes.

      /**
       * @brief Default constructor.
       */
      public: Engine();

      /**
       * @brief Destructor.
       */
      public: ~Engine();

      /**
       * @brief Calls a function.
       *
       * @param nFunctionIndex Index of the function.
       * @param nArgumentCount Number of arguments passed.
       * @param pArgumentTypes An array of the types of the arguments.
       * @param pArguments An array of pointers to t::Object's which are the arguments passed.
       * @return A value return by the function.
       */
      public: t::Value call (ulong nFunctionIndex, uchar nArgumentCount, uchar* pArgumentTypes, t::Value* pArguments);

      /**
       * @brief Clears the block array.
       */
      public: void clear_blocks ();

      public: void copy_arguments (vm::OpCode* pOpcode, t::Value*& pArguments);

      /**
       * @brief Exits the currently running engine.
       */
      public: void exit ();

      /**
       * @brief Finds the nearest exception handler block.
       *
       * Going up the stack from the current block to find an exception handler.
       *
       * @return A pointer to an exception handler block if found, NULL otherwise.
       */
      public: t::Block* find_nearest_exception_handler ();

      /**
       * @todo Handle object types more appropriatly.
       */
      public: void format_arguments (vm::OpCode* pOpcode, t::Value* pArguments);

      /**
       * @brief Gets a block.
       *
       * @param nIndex The index of the block to get.
       * @return A pointer to the block if found, NULL otherwise.
       */
      public: t::Block* get_block (ulong nIndex);

      /**
       * @brief Gets a function.
       *
       * @param nIndex The index of the function to get.
       * @return A pointer to the function.
       * @todo Do some ASSERTs
       */
      public: inline t::Function* get_function (ulong nIndex)
      {
         return this->functions[nIndex];
      }

      public: bool handle_exception ();

      /**
       * @brief Imports the swap content into a block's heap.
       *
       * @param pBlock A pointer to the block importing the swap.
       */
      /**public: inline void import_swap (t::Block* pBlock)
      {
         this->import_swap(pBlock, this->swap.count());
      }
      */

      /**
       * @brief Imports a portion of the swap into a block's heap.
       *
       * @param pBlock A pointer to the block importing the swap.
       * @param nCount How many item to import.
       */
      // public: void import_swap (t::Block* pBlock, ulong nCount);

      /**
       * @brief Makes an empty array of t::Object's of length [count].
       *
       * @param obj An array of pointer to t::Object's.
       * @param count The length of the new array.
       */
      public: static void make_empty_value_array (t::Value*& obj, uchar count);

      /**
       * @brief Prints a block and its opcodes.
       *
       * @param nBlockIndex Index of the block.
       * @param pBlock A pointer to the block to print.
       */
      public: void print_block (uint nBlockIndex, t::Block* pBlock);

      /**
       * @brief Prints all the blocks and their opcodes.
       */
      public: void print_blocks ();

      /**
       * @brief Prints an opcode and its arguments.
       *
       * @param nOpcodeIndex The index of the opcode in the block.
       * @param pOpcode The opcode to print.
       */
      public: void print_opcode (uint nOpcodeIndex, vm::OpCode* pOpcode);

      public: void print_opcode_arguments ();

      /**
       * @brief Prints information about the engine to the console.
       */
      public: static void print_version ();

      /**
       * @brief Runs the first block.
       */
      public: void run ();

      /**
       * @brief Runs each opcode of a block.
       *
       * @param pBlock The block to run.
       * @param bAddToStack Wether to add this block to the call stack.
       */
      public: void run_block (t::Block* pBlock, bool bAddToStack);

      /**
       * @brief Sets a block at a given index.
       *
       * @param nIndex The index of the block to set.
       * @param pBlock The block to use.
       */
      public: inline void set_block (uint nIndex, t::Block* pBlock, uint nFirstOpcodeIndex, uint nOpcodeCount)
      {
         ASSERT_NOT_NULL(pBlock);
         pBlock->pick();
         pBlock->opcodes = (vm::OpCode**)(this->opcodes + nFirstOpcodeIndex);
         pBlock->opcode_count = nOpcodeCount;
         /*DEBUG(
               "\nopcodes=%d\nsizeof=%d\nfirst_op=%d\nresult=%d\n",
               (uint)this->opcodes,
               sizeof(vm::OpCode*),
               nFirstOpcodeIndex,
               (uint)pBlock->opcodes
         );
         */
         this->blocks[nIndex] = pBlock;
         INTERNAL(
               "<Engine:0x%x> SET_BLOCK "
               "(.index %u, .first_opcode %u, .opcode_count %u, .all_opcodes_start_at 0x%x, .block_opcodes_start_at 0x%x)\n",
               (uint)this,
               nIndex,
               nFirstOpcodeIndex,
               nOpcodeCount,
               (uint)this->opcodes,
               (uint)pBlock->opcodes
         );
         #ifdef QD__ASSERT__ALLOW
         for (uint i = 0 ; i < pBlock->opcode_count ; ++i)
         {
            ASSERT_NOT_NULL(pBlock->opcodes[i]);
         }
         #endif
      }

      /**
       * @brief Sets an opcode at a given index.
       *
       * @param nIndex The index of the opcode to set.
       * @param pBlock The opcode to use.
       */
      public: inline void set_opcode (uint nIndex, OpCode* pOpc)
      {
         ASSERT_NOT_NULL(pOpc);
         INTERNAL(
               "<Engine:0x%x> SET_OPCODE "
               "(.index %u, .opcode_at 0x%x)\n",
               (uint)this,
               nIndex,
               (uint)pOpc
         );
         this->opcodes[nIndex] = pOpc;
      }

      /**
       * @brief Sizes the block array.
       *
       * @param nCount Size of the block array.
       */
      public: void size_blocks (ulong nCount);

      /**
       * @brief Sizes the class array.
       *
       * @param nCount Size of the class array.
       */
      public: void size_classes (ulong nCount);

      /**
       * @brief Sizes of the function array.
       *
       * @param nCount Size of the function array.
       */
      public: void size_functions (ulong nCount);

      /**
       * @brief Sizes of the opcode array.
       *
       * @param nCount Size of the opcode array.
       */
      public: void size_opcodes (uint nCount);

      /**
       * @brief Throws a t::Exception.
       *
       * @param exception The exception to throw.
       */
      public: inline void throw_exception (t::Object* exception)
      {
         ASSERT_NOT_NULL(this->current_frame);
         ASSERT_NOT_NULL(exception);

         this->current_frame->throw_exception(exception);
      }
   };

   typedef t::Value (*CoreFunctionPointer)(vm::Engine* pEngine, uchar nArgumentCount, uchar* pArgumentTypes, t::Value* Arguments);
}

#endif
