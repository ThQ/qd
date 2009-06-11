#ifndef UTIL_STRING
#define UTIL_STRING NS_UTIL::String

#include "t/Bool.h"
#include "t/Float.h"
#include "t/Int.h"
#include "t/String.h"

namespace util
{
   /**
    * Utilities for @cls{t::String}.
    */
   class String
   {
      /**
       * Formats a string (like printf in C).
       *
       * @param format_str The format string to use.
       * @param argc Number of arguments.
       * @param argv Arguments.
       * @return A pointer to the @cls{t::String} newly created
       */
      public: static t::Object* format(t::Object* format_str, ULong argc, t::Object** argv);
   };
}


#endif
