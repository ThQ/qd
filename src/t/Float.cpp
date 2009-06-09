#include "t/Float.h"

namespace t
{
   T_OBJECT* tFLOAT = NULL;

   Float::Float()
   {
      this->value = 0;
      this->set_class(NS_TYPE::tFLOAT);
   }

   T_OBJECT*
   Float::build(long double d)
   {
      Float* f = new Float();
      f->value = d;

      return (T_OBJECT*)f;
   }
}
