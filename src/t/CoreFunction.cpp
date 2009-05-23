#include "t/CoreFunction.h"

namespace NS_TYPE
{
   CoreFunction*
   CoreFunction::build(const char* name, ULong pointer, Object* return_type)
   {
      ASSERT(strlen(name) > 0, "<svm::CoreFunction>.name must be longer than 0 characters.\n");
      ASSERT(pointer != 0, "<svm::CoreFunction> cannot bind a null pointer.\n");
      T_OBJECT::assert_not_null(return_type);

      CoreFunction* f = new CoreFunction();
      T_CLASS::assert(f->cls);
      T_OBJECT::assert_not_null(f);
      f->name = name;
      f->function_pointer = pointer;
      f->set_return_type(return_type);

      return f;
   }
}

