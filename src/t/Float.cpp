#include "t/Float.h"

namespace NS_TYPE
{
   T_OBJECT* float_type = NULL;

   Float::Float()
   {
      this->value = 0;
      this->set_class(float_type);
   }

   T_OBJECT*
   Float::build(long double d)
   {
      Float* f = new Float();
      f->value = d;

      return (T_OBJECT*)f;
   }
}
