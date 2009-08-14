#ifndef T__CORE_FUNCTION__H
#define T__CORE_FUNCTION__H __FILE__

#include "t/Function.h"

namespace t
{
   /**
    * @brief An internal function created internally.
    */

   class CoreFunction : public t::Function
   {
      public: void* function_pointer; ///< A pointer to a C function to call.

      /**
       * @brief Constructs a CoreFunction given its return type and class and function pointer.
       *
       * @param pFunc A pointer to the c function to call.
       * @param nReturnType The type of the object to return.
       * @param pReturnClass The class of the object to return.
       */
      public: CoreFunction (void* pFunc, ushort nReturnType, vm::Class* pReturnClass);
   };
}

#endif
