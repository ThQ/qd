#ifndef T_USER_FUNCTION
#define T_USER_FUNCTION NS_TYPE::UserFunction

#include "t/Block.h"
#include "t/Function.h"

namespace t
{
   /**
    * A function created by the user.
    */
   class UserFunction : public Function
   {
      public: T_BLOCK* block; ///< A block of opcodes to run.

      /**
       * Constructor.
       */
      public: UserFunction();

      /**
       * Sets the block of opcodes to run.
       *
       * @param block A block of opcodes.
       */
      public: void set_block(T_BLOCK* block);
   };
}

#endif
