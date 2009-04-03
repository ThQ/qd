#include "util/Int.h"

namespace NS_UTIL
{
   t::Object*
   IntUtil::list_to_iii(t::Object* src, t::Object* dest, t::Object* step)
   {
      Long lsrc= ((t::Int*)src)->value;
      Long ldest = ((t::Int*)dest)->value;
      Long lstep = ((t::Int*)step)->value;
      t::Object* result = t::List::build();

      ASSERT(step != 0, "Step must not be 0, exception should have been thrown.");

      if (lstep < 0)
      {
         lstep = lstep * -1;
      }

      if (lsrc < ldest)
      {
         for (Long i = lsrc ; i <= ldest ; i += lstep)
         {
            t::List::push(result, t::Int::build(i));
         }
      }
      else
      {
         for (Long i = lsrc ; i >= ldest ; i -= lstep)
         {
            t::List::push(result, t::Int::build(i));
         }
      }

      return result;
   }
}
