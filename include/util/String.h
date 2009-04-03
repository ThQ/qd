#ifndef UTIL_STRING
#define UTIL_STRING NS_UTIL::String

#include "t/Bool.h"
#include "t/Float.h"
#include "t/Int.h"
#include "t/String.h"

namespace NS_UTIL
{
   class String
   {
      public: static t::Object* format(t::Object* format_str, ULong argc, t::Object** argv);
   };
}


#endif
