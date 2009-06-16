#ifndef T_COLLECTION
#define T_COLLECTION NS_TYPE::Collection

#include "t/Object.h"

namespace t
{
   /**
    * A base class for any kind of collection (array, list, map, set, etc).
    */
   class Collection : public Object
   {
      public: uint64_t length; ///< Number of items in the collection.
   };
}

#endif
