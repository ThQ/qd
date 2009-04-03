#include "svm/IntUtil.h"

namespace svm
{
   Object*
   IntUtil::list_to_iii(Object* src, Object* dest, Object* step)
   {
      Long lsrc= ((Int*)src)->value;
      Long ldest = ((Int*)dest)->value;
      Long lstep = ((Int*)step)->value;
      Object* result = List::build();

      ASSERT(step != 0, "Step must not be 0, exception should have been thrown.");

      if (lstep < 0)
      {
         lstep = lstep * -1;
      }

      if (lsrc < ldest)
      {
         for (Long i = lsrc ; i <= ldest ; i += lstep)
         {
            List::push(result, Int::build(i));
         }
      }
      else
      {
         for (Long i = lsrc ; i >= ldest ; i -= lstep)
         {
            List::push(result, Int::build(i));
         }
      }


      return result;
   }
}
