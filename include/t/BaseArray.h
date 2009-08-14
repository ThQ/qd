#ifndef T__BASE_ARRAY__H
#define T__BASE_ARRAY__H __FILE__

#include "t/Collection.h"

namespace t
{
   /**
    * @brief A base classes for all C array based types (Array, List).
    */
   class BaseArray : public Collection
   {
      public: vm::Class*   item_class;    ///< A pointer to a @cls{t::Class} representing the class of the objects stored, if needed, NULL otherwise.
      public: uchar        slot_size;     ///< How many Value's for one item. Some items may need two slots.
                                          ///< For ex on 32bit machines, UInt64 will need two slots per item.
      public: ushort       item_type;     ///< What kind of object these items are (Bool, Array, String, UserObject).
      public: Value*       items;         ///< An array of the values stored.

      /**
       * @brief Default constructor.
       */
      public: BaseArray ();

      /**
       * @brief Replaces each item with NULL.
       */
      public: void clear ();

      /**
       * @brief Replaces an item of a @cls{t::Array} with NULL.
       *
       * @param item_index The index of the item to clear.
       */
      public: void clear_item (UInt64 item_index);

      /**
       * @brief Replaces a range of items with NULL.
       *
       * @param range_start The index at which to start clearing.
       * @param range_end The index at which to stop clearing.
       */
      public: void clear_range (UInt64 range_start, UInt64 range_end);

      /**
       * @brief Gets an object.
       *
       * @param index The position at which to get the object.
       * @return A pointer to an object.
       */
      public: Value get_object_at (UInt64 index);

      /**
       * @brief Gets a value.
       *
       * @param index The position at which to get the value.
       * @return A value.
       */
      public: Value get_value_at (UInt64 index);

      /**
       * @brief Reverses the values in a portion of the array.
       *
       * @param nStartIndex The start of the portion to reverse.
       * @param nLength The length of the portion.
       */
      public: void reverse (uint nStartIndex, uint nLength);

      /**
       * @brief Replaces an item with another one.
       *
       * @param item_index The index of the item to set.
       * @param new_value A value to use a replacement
       */
      public: void set_item (UInt64 item_index, Value new_value);

      /**
       * @brief Sets an item.
       *
       * @param at The position at which to set the item in [list].
       * @param obj The object to set at [at].
       * @return [list].
       */
      public: inline void set_item (UInt64 at, Object* obj)
      {
         this->set_item(at, (Value)obj);
      }

      /**
       * @brief Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param type A pointer to a @cls{t::Class} to use a type.
       */
      public: inline void set_item_type (ushort type)
      {
         this->set_item_type(type, NULL);
      }

      /**
       * @brief Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param type A pointer to a @cls{t::Class} to use a type.
       * @param cls The class to use.
       */
      public: void set_item_type (ushort type, vm::Class* cls);
   };
}

#endif
