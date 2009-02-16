#ifndef SVM_STRING_UTIL_H
#define SVM_STRING_UTIL_H

#include "svm/Bool.h"
#include "svm/Float.h"
#include "svm/Int.h"
#include "svm/String.h"

namespace svm
{
   class StringUtil
   {
      public: static Object* format(Object* format_str, ULong argc, Object** argv);
   };
}


#endif
