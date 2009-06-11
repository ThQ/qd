#ifndef UTIL_CLASS
#define UTIL_CLASS NS_UTIL::Class

#include "t/Class.h"
#include "t/Variable.h"

namespace util
{
   /**
    * Some utilities for @cls{t::Class}.
    */
   class Class
   {
      /**
       * Declares a new field for a class.
       *
       * @param cls The class to which add a field.
       * @param type The type of the field.
       * @param name The name of the field. (USELESS now).
       */
      public: static void declare_field(t::Object* cls, t::Object* type, std::string name);
   };
}

#endif
