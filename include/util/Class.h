#ifndef UTIL_CLASS_UTIL
#define UTIL_CLASS_UTIL NS_UTIL::Class

#include "t/Class.h"
#include "t/Variable.h"

namespace NS_UTIL
{
   class Class
   {
      public: static void declare_field(t::Object* cls, t::Object* type, std::string name);
   };
}

#endif
