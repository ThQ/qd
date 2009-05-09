#ifndef UTIL_OBJECT
#define UTIL_OBJECT NS_UTIL::Object

#include "t/Class.h"
#include "t/Object.h"

namespace NS_UTIL
{
   class Object
   {
      public: static void assert_type(t::Object* object, t::Object* type);
   };
}

#endif
