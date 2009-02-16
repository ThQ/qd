#ifndef SVM_HEAP_OBJECT_H
#define SVM_HEAP_OBJECT_H

#include "svm/Object.h"

namespace svm
{
   extern Object* heap_object_type;

   class HeapObject : public Object
   {
      public: bool local;
      public: long position;

      public: HeapObject();
      public: static Object* build(bool local, long position);
   };
}

#endif
