#ifndef T__USER_FUNCTION__H
#define T__USER_FUNCTION__H __FILE__

#include "t/Block.h"
#include "t/Function.h"

namespace t
{
   /**
    * @brief A function created by the user.
    */
   class UserFunction : public Function
   {
      public: Block* block; ///< A block of opcodes to run.

      /**
       * @brief Default constructor.
       */
      public: UserFunction();

      /**
       * @brief Destructor.
       */
      public: ~UserFunction();

      /**
       * @brief Sets the block of opcodes to run.
       *
       * @param pBlock A block of opcodes.
       */
      public: void set_block(Block* pBlock);
   };
}

#endif
