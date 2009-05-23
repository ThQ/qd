#ifndef T_HEAP_OBJECT
#define T_HEAP_OBJECT NS_TYPE::HeapObject

#include "t/Object.h"

namespace NS_TYPE
{
   extern T_OBJECT* tHEAP_OBJECT;

   /**
    * A heap object is an object representing an object from the heap.
    *
    * An heap object is replaced by the object pointed just before an opcode
    * call.
    */
   class HeapObject : public T_OBJECT
   {
      public: bool local;
      public: long position;

      /**
       * Constructor.
       */
      public: HeapObject();

      /**
       * Creates a t::HeapObject.
       *
       * @param local Whether the object is from the local heap or not.
       * @param position The position from the heap.
       * @return A new t::HeapObject.
       */
      public: static T_OBJECT* build(bool local, long position);
   };
}

#endif
