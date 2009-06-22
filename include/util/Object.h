#ifndef UTIL_OBJECT
#define UTIL_OBJECT NS_UTIL::Object

#include "t/Class.h"
#include "t/Object.h"
#include "Stats.h"

namespace util
{
   /**
    * Utilities for @cls{t::Object}.
    */
   class Object
   {
      /**
       * Asserts that an object is of a certain type.
       *
       * @param object The object to check.
       * @param type The supposed type of @prm{object}.
       */
      public: static void assert_type(t::Object* object, t::Object* type);

      /**
       * Decreases the reference count of an object by one.
       *
       * @param pObject The object to drop.
       * @return true if everything went well.
       */
      public: static bool drop(t::Object* pObject);

      /**
       * Increases the reference count of an object by one.
       *
       * @param pObject The object to pick.
       * @return true if everything went well.
       */
      public: static bool pick(t::Object* pObject);
   };
}

#endif
