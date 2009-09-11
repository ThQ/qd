#ifndef VM__CALL_STACK__H
#define VM__CALL_STACK__H __FILE__

#include "t/Block.h"
#include "t/Object.h"
#include "t/String.h"
#include "vm/Frame.h"

namespace vm
{
   /**
    * @brief A call stack.
    *
    * Stores a pointer to all the frames previously called.
    */
   class CallStack
   {
      public: u3           frame_count;   ///< How many blocks in the call stack.
      public: vm::Frame*   last_frame;
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
      public: void append(vm::Frame* pBlock);

      /**
       * @brief Counts how many blocks in the stack.
       *
       * @return The number of blocks.
       */
      public: inline u3 count()
      {
         return this->frame_count;
      }

      /**
       * @brief Pops a frame off.
       *
       * @todo Way too REALLOC intensive.
       */
      public: void pop();

      /**
       * @brief Returns the frame at the top of the stack.
       *
       * @return The last frame appended.
       */
      public: vm::Frame* peek ();

      /**
       * @brief Prints the call stack to the screen.
       */
      public: void print();
   };
}

#endif
