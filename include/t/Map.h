#ifndef T_MAP
#define T_MAP t::Map

#include "t/Collection.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tMAP;

   /**
    * A map is a list of unordered key-value pairs.
    *
    * @todo Make it a tree.
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
      public: void clear();

      /**
       * Finds the position of a key in a map.
       *
       * @param key The key to look for.
       * @param dwPos Will receive the index of the key, if found.
       * @return true if the key is found.
       */
      public: bool find_key(Object* pKey, UInt64& dwPos);

      /**
       * Tests if it contains a key.
       *
       * @param key The key to look for.
       * @return true if the key is found.
       */
      public: bool has_key(Object* pKey);

      /**
       * Sets an item in a map.
       *
       * @param key The key to set.
       * @param value The value to use.
       * @return true if item has been set.
       * @todo Make it way more realloc intensive.
       */
      public: bool set_item(Object* key, Object* value);

      /**
       * Sets an item in a map.
       *
       * @param key The key to set.
       * @param value The value to use.
       * @return true if item has been set.
       */
      public: inline bool set_item(std::string key, std::string value)
      {
         return this->set_item((Object*)new String(key), (Object*)new String(value));
      }
   };
}

#endif
