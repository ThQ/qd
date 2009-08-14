#ifndef T__COLLECTION__H
#define T__COLLECTION__H __FILE__

#include "t/Object.h"

namespace t
{
   /**
    * @brief A base class for any kind of collection (array, list, map, set, etc).
    */
   class Collection : public Object
   {
      public: uint length;        ///< Number of items in the collection.
      public: uint slot_count;    ///< How many slots.
   };
}

#endif
