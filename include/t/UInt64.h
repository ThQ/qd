#ifndef T_UINT64
#define T_UINT64 t::UInt64

#include "t/Int.h"

namespace t
{
   /**
    * Unsigned integer (from 0 to 18446744073709551615).
    */
   class UInt64: public Int<uint64_t>
   {

   };
}

#endif
