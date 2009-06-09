#include "t/HeapObject.h"

namespace t
{
   T_OBJECT* tHEAP_OBJECT = NULL;

   HeapObject::HeapObject()
   {
      this->local = true;
      this->position = 0;
      this->set_class(NS_TYPE::tHEAP_OBJECT);
   }

   T_OBJECT*
   HeapObject::build(bool local, long position)
   {
      HeapObject* result = new HeapObject();
      result->local = local;
      result->position = position;

      return (T_OBJECT*)result;
   }
}
