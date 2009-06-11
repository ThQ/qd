#ifndef UTIL_LIST
#define UTIL_LIST NS_UTIL::List

#include "t/Bool.h"
#include "t/Int.h"
#include "t/List.h"
#include "t/String.h"

namespace util
{
   /**
    * Utilities for @cls{t::List}.
    */
   class List
   {
      /**
       * Prints a list to the console.
       *
       * @param list The list to print.
       */
      public: static void print(t::List* list);
   };
}

#endif
