#include "t/CoreFunction.h"

namespace t
{
   CoreFunction::CoreFunction(void* pFunc, ushort nReturnType, vm::Class* pReturnClass)
   {
      ASSERT_NOT_NULL(pFunc);
      ASSERT_TYPE(nReturnType);

      this->function_pointer = pFunc;
      this->is_user = false;
      this->set_return_type(nReturnType, pReturnClass);
   }
}

