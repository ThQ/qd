#ifndef UTIL_INT
#define UTIL_INT NS_UTIL::Int

#include "t/Int.h"
#include "t/List.h"

namespace NS_UTIL
{
   class Int
   {
      // @TODO : WTH is that function name ??
      public: static t::Object* list_to_iii(t::Object* src, t::Object* dest, t::Object* step);
   };
}

#endif
