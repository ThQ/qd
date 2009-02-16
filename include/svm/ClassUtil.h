#ifndef SVM_CLASS_UTIL_H
#define SVM_CLASS_UTIL_H

#include "svm/Class.h"
#include "svm/Variable.h"

namespace svm
{
   class ClassUtil
   {
      public: static void declare_field(Object* cls, Object* type, std::string name);
   };
}

#endif
