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
       * Creates a t::CoreFunction object whose name is [name] and return type
       * is [return_type], it uses the function pointed by [pointer].
       *
       * @param name A pointer to a string containing the name of the function.
       * @param pointer An integer that points to the function to call.
       * @param return_type A pointer to a t::Class representing the return type.
       * @return A pointer to the CoreFunction newly created.
       */
      public: static CoreFunction* build(const char* name, ULong pointer, T_OBJECT* return_type);
   };
}

#endif
