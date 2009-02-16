#include "svm/CoreFunction.h"

namespace svm
{
   CoreFunction*
   CoreFunction::build(const char* name, long pointer, Object* return_type)
   {
      ASSERT(strlen(name) > 0, "<svm::CoreFunction>.name must be longer than 0 characters.\n");
      ASSERT(pointer != 0, "<svm::CoreFunction> cannot bind a null pointer.\n");
      SVM_ASSERT_NOT_NULL(return_type);

      CoreFunction* f = new CoreFunction();
      SVM_ASSERT_CLASS(f->cls);
      SVM_ASSERT_NOT_NULL(f);
      f->name = name;
      f->function_pointer = pointer;
      f->set_return_type(return_type);

      return f;
   }
}

