#include "svm/HeapObject.h"

namespace svm
{
   Object* heap_object_type = NULL;

   HeapObject::HeapObject()
   {
      this->local = true;
      this->position = 0;
      this->cls = svm::heap_object_type;
   }

   Object* 
   HeapObject::build(bool local, long position)
   {
      HeapObject* result = new HeapObject();
      result->local = local;
      result->position = position;

      return (Object*)result;
   }
}
