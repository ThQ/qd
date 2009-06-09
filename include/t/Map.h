#ifndef T_MAP
#define T_MAP t::Map

#include "t/Collection.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tMAP;

   /**
    * A map is a list of unordered key-value pairs.
    */
   class Map : public Collection
   {
      public: T_OBJECT** keys;   ///< An array of keys.
      public: T_OBJECT** items;  ///< An array of items.

      public: Map();

      /**
       * Asserts that an object is of type t::Map.
       *
       * @param obj An object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         ASSERT_NOT_NULL(NS_TYPE::tMAP);
         T_OBJECT::assert_type(obj, NS_TYPE::tMAP);
      }

      /**
       * Builds an empty t::Map.
       *
       * @return A pointer to a t::Map object newly created.
       */
      public: static T_OBJECT* build();

      /**
       * Checks if an object is of type t::Map.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type t::Map.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tMAP);
      }

      /**
       * Clears a map : Drop every object and resizes the map to zero.
       *
       * @param map The map to clear.
       * @return [map].
       */
      public: static T_OBJECT* clear(T_OBJECT* map);

      /**
       * Finds the position of a key in a map.
       *
       * @param map The map to search.
       * @param key The key to look for.
       * @return If found, the position of the key, otherwise -1.
       */
      public: static int find_key(Map* map, T_OBJECT* key);

      /**
       * Sets an item in a map.
       *
       * @param map The map to set an item to.
       * @param key The key to set.
       * @param value The value to use.
       * @return [value].
       */
      public: static T_OBJECT* set_item(T_OBJECT* map, T_OBJECT* key, T_OBJECT* value);

      /**
       * Sets an item in a map.
       *
       * @param map The map to set an item to.
       * @param key The key to set.
       * @param value The value to use.
       * @return [value].
       */
      public: static T_OBJECT* set_item(T_OBJECT* map, std::string key, std::string value);

      /**
       * Slices a map from [key1] to [key2].
       *
       * @param map The map to slice.
       * @param key1 Slice start
       * @param key2 Slice end.
       * @deprecated Maps are not supposed to be ordered, no slicing should be possible.
       */
      public: static T_OBJECT* slice(T_OBJECT* map, T_OBJECT* key1, T_OBJECT* key2);
   };
}

#endif
