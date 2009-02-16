#include "svm/Float.h"

namespace svm
{
   Object* float_type = NULL;

   Float::Float()
   {
      this->references = 0;
      this->value = 0;
      this->cls = float_type;
   }

   Object*
   Float::build(long double d)
   {
      Float* f = new Float();
      f->value = d;

      return (Object*)f;
   }
}
