#ifndef T_FLOAT
#define T_FLOAT t::Float

#include "t/Object.h"

namespace t
{
   extern T_OBJECT* tFLOAT;

   /**
    * An internal representation of a float.
    */
   class Float : public Object
   {
      public: long double value; ///< Float value.

      /**
       * Constructor.
       */
      public: Float();

      /**
       * Builds a @cls{t::Float} from a c long double @prm{d}.
       *
       * @param d A c long double to use.
       * @return A pointer to a @cls{t::Float} newly created.
       */
      public: static T_OBJECT* build(long double d);
   };
}

#endif
