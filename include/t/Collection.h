#ifndef T_COLLECTION
#define T_COLLECTION NS_TYPE::Collection

#include "t/Object.h"

namespace t
{
   class Collection : public Object
   {
      public: ULong length; ///< Number of items in the collection.
   };
}

#endif
