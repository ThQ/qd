#ifndef VM__CALL_STACK__H
#define VM__CALL_STACK__H __FILE__

#include "t/Block.h"
#include "t/Object.h"
#include "t/String.h"

namespace vm
{
   /**
    * @brief A call stack.
    *
    * Stores a pointer to all the block previously called.
    *
    * @todo Think about sizing up/down the stack.
    * (Only a stupid resize up is done right now).
    */
   class CallStack
   {
      public: t::Block**   blocks;        ///< An array of all the blocks.
      public: ulong        block_count;   ///< How many blocks in the call stack.

      /**
       * @brief Default constructor.
       */
      public: CallStack();

      /**
       * @brief Destructor.
       */
      public: ~CallStack();

      /**
       * @brief Appends a block.
       *
       * @param pBlock A pointer to a block to append.
       */
      public: void append(t::Block* pBlock);

      /**
       * @brief Counts how many blocks in the stack.
       *
       * @return The number of blocks.
       */
      public: ulong count();

      /**
       * @brief Gets a specific block.
       *
       * @param nAt The index of the block to get.
       * @return A pointer to the block.
       */
      public: t::Block* get(ulong nAt);

      /**
       * @brief Pops a block off.
       *
       * @return The poped block.
       * @todo Way too REALLOC intensive.
       */
      public: t::Block* pop();

      /**
       * @brief Prints the call stack to the screen.
       */
      public: void print();
   };
}

#endif
