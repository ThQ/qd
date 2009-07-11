#ifndef T_MAP_H
#define T_MAP_H

#include "t/Collection.h"
#include "t/String.h"
#include "vm/Class.h"

namespace t
{
   extern vm::Class cMAP;

   /**
    * @brief An unordered list of key-value pairs.
    *
    * @todo Make it a tree.
    */
   class Map : public Collection
   {
      public: ushort key_type;         ///< Type of the keys.
      public: vm::Class* key_class;    ///< Class of the keys.
      public: ushort item_type;        ///< Type of the items.
      public: vm::Class* item_class;   ///< Class of the items.
      public: T_OBJECT** keys;         ///< An array of keys.
      public: T_OBJECT** items;        ///< An array of items.

      /**
       * @brief Default constructor.
       */
      public: Map();

      /**
       * @brief Default destructor.
       */
      public: ~Map();

      /**
       * @brief Asserts that an object is of type t::Map.
       *
       * @param obj An object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         obj->assert_type(t::MAP_TYPE);
      }

      /**
       * @brief Checks if an object is of type t::Map.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type t::Map.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return obj->check_type(t::MAP_TYPE);
      }

      /**
       * @brief Clears the map
       *
       * Drop every object.
       */
      public: void clear();

      /**
       * @brief Destroys a @cls{t::Map}.
       *
       * @param pObject A pointer to a @cls{t::Map} to destroy.
       * @return true if everything went well.
       */
      public: static bool destroy(Value pObject);

      /**
       * @brief Finds the position of a key in a map.
       *
       * @param pKey The key to look for.
       * @param dwPos Will receive the index of the key, if found.
       * @return true if the key is found.
       */
      public: bool find_key(Object* pKey, UInt64& dwPos);

      /**
       * @brief Tests if it contains a key.
       *
       * @param pKey The key to look for.
       * @return true if the key is found.
       */
      public: bool has_key(Object* pKey);

      /**
       * @brief Prints a string representation of a map in the console.
       *
       * @param pMap A pointer to a @cls{t::Map}.
       */
      public: static void print(Value pMap);

      /**
       * @brief Prints a string representation of a map in the console on a new line.
       *
       * @param pMap A pointer to a @cls{t::Map}.
       */
      public: static void print_line(Value pMap);

      /**
       * @brief Sets an item in a map.
       *
       * @param key The key to set.
       * @param value The value to use.
       * @return true if item has been set.
       * @todo Make it way more realloc intensive.
       */
      public: bool set_item(Object* key, Object* value);

      /**
       * @brief Sets an item in a map.
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
