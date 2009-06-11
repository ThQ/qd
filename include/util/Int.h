#ifndef UTIL_INT
#define UTIL_INT NS_UTIL::Int

#include "t/Int.h"
#include "t/List.h"

namespace util
{
   /**
    * Utilities for @cls{t::Int}.
    */
   class Int
   {
      /**
       * Creates a @cls{t::List}} filled with @cls{t::Int}'s in a given range.
       *
       * @param src Range start.
       * @param dest Range end.
       * @param step Range step.
       * @todo WTH is that function name ??
       */
      public: static t::Object* list_to_iii(t::Object* src, t::Object* dest, t::Object* step);
   };
}

#endif
