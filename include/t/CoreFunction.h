#ifndef T_CORE_FUNCTION
#define T_CORE_FUNCTION NS_TYPE::CoreFunction

#include "t/Function.h"

namespace NS_TYPE
{
   /**
    * An internal function created internally.
    */

   class CoreFunction : public T_FUNCTION
   {
      public: ULong function_pointer;

      /**
       * Creates a t::CoreFunction object whose name is <name> and return type
       * is <return_type>, it uses the function pointed by <pointer>.
       */
      public: static CoreFunction* build(const char* name, ULong pointer, T_OBJECT* return_type);
   };
}

#endif
