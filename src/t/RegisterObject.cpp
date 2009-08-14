#include "t/RegisterObject.h"

namespace t
{
   VM_CLASS__NEW(cREGISTER_OBJECT, t::Object, t::REGISTER_VALUE_TYPE, &cOBJECT);

   RegisterObject::RegisterObject ()
   {
      this->klass = &t::cREGISTER_OBJECT;
      this->object_type = t::UNDEFINED_TYPE;
      this->position = 0;
      this->type = t::REGISTER_VALUE_TYPE;
   }

   RegisterObject::RegisterObject (uchar nType, uint nPosition)
   {
      this->klass = &t::cREGISTER_OBJECT;
      this->object_type = nType;
      this->position = nPosition;
      this->type = t::REGISTER_VALUE_TYPE;
   }
}

