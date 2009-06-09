#ifndef T_HEAP_OBJECT
#define T_HEAP_OBJECT NS_TYPE::HeapObject

#include "t/Object.h"

namespace t
{
   extern T_OBJECT* tHEAP_OBJECT;

   /**
    * A heap object is an object representing an object from the heap.
    *
    * An heap object is replaced by the object pointed just before an opcode
    * call.
    */
   class HeapObject : public Object
   {
      public: bool local;     ///< Whether from local heap or not.
      public: long position;  ///< Position in the heap.

      /**
       * Constructor.
       */
      public: HeapObject();

      /**
       * Creates a @cls{t::HeapObject}.
       *
       * @param local Whether the object is from the local heap or not.
       * @param position The position in the heap.
       * @return A new @cls{t::HeapObject}.
       */
      public: static T_OBJECT* build(bool local, long position);
   };
}

#endif
