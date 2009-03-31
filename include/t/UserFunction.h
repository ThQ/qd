#ifndef T_USER_FUNCTION
#define T_USER_FUNCTION NS_TYPE::UserFunction

#include "t/Block.h"
#include "t/Function.h"

namespace NS_TYPE
{
   class UserFunction : public T_FUNCTION
   {
      public: T_BLOCK* block;

      public: UserFunction();
      public: void set_block(T_BLOCK* block);
   };
}

#endif
