#ifndef SVM_INT_UTIL_H
#define SVM_INT_UTIL_H

#include "debug.h"
#include "svm/Int.h"
#include "svm/List.h"

namespace svm
{
   class IntUtil
   {
      public: static Object* list_to_iii(Object* src, Object* dest, Object* step);
   };
}

#endif
