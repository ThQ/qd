#ifndef T_CORE_FUNCTION
#define T_CORE_FUNCTION NS_TYPE::CoreFunction

#include "t/Function.h"

namespace NS_TYPE
{
   class CoreFunction : public T_FUNCTION
   {
      public: unsigned long function_pointer;

      public: static CoreFunction* build(const char* name, long int pointer, Object* return_type);
   };
}

#endif
