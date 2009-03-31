#ifndef T_HEAP_OBJECT
#define T_HEAP_OBJECT NS_TYPE::HeapObject

#include "t/Object.h"

namespace NS_TYPE
{
   extern T_OBJECT* tHEAP_OBJECT;

   class HeapObject : public T_OBJECT
   {
      public: bool local;
      public: long position;

      public: HeapObject();
      public: static T_OBJECT* build(bool local, long position);
   };
}

#endif
