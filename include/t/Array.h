#ifndef T_ARRAY
#define T_ARRAY t::Array

#include "t/Collection.h"
#include "vm/Class.h"

namespace t
{
   extern vm::Class cARRAY;

   /**
    * A @cls{t::Array} is a list of @cls{t::Object}'s who can only contain elements of a
    * predetermined type and who can never exceed a predetermined (and fixed) number of
    * elements.
    * @todo Attribute [length] is from t::Collection, remove [item_count].
    */
   class Array: public Collection
   {
      public: vm::Class* item_class;    ///< A pointer to a @cls{t::Class} representing the class of the objects stored, if needed, NULL otherwise.
      public: UInt64 item_count;     ///< Number of item stored. REPLACE THIS WITH Collection::length.
      public: ushort item_type;     ///< What kind of object this items are (Bool, Array, String, UserObject).
      public: Value* items;         ///< The values stored.

      /**
       * @brief Default constructor.
       */
      public: Array ();

      /**
       * @brief Constructs an array whose type and length are known.
       *
       * @param nItemType A ushort describing the type of the items stored in the aray.
       * @param pItemClass A pointer to a @cls{t::Class} to use as item type.
       * @param dwArrayLength The length of the array to create.
       */
      public: Array (ushort nItemType, vm::Class* pItemClass, UInt64 dwArrayLength);

      /**
       * @brief Constructs an array whose type and length are known.
       *
       * @param nItemType A ushort describing the type of the items stored in the aray.
       * @param pItemClass A pointer to a @cls{t::Class} to use as item type.
       * @param dwArrayLength The length of the array to create.
       * @param pItems An array of @cls{t::Value}'s to fill the array. It must
       * contain at least @prm{dwArrayLength} objects.
       */
      public: Array (ushort nItemType, vm::Class* pItemClass, UInt64 dwArrayLength, Value* pItems);

      /**
       * Destructor.
       */
      public: ~Array ();

      /**
       * Initializes an Array object.
       */
      protected: inline void _init ()
      {
         this->klass = &cARRAY;
         this->type = t::ARRAY_TYPE;
         this->item_type = t::UNDEFINED_TYPE;
         this->item_class = NULL;
         this->items = NULL;
         this->item_count = 0;

         ASSERT_NOT_NULL(this->klass);
         ASSERT(this->type != t::UNDEFINED_TYPE, "Array object must have a type");
      }

      /**
       * Asserts that an object is of type t::ARRAY_TYPE.
       *
       * @param obj The object to check.
       */
      public: inline static void assert(Object* obj)
      {
         obj->assert_type(t::ARRAY_TYPE);
      }

      /**
       * Checks if an object is of type @cls{t::Array}.
       *
       * @param obj A pointer to a @cls{t::Object} to check.
       * @return true if @prm{obj} is a pointer to a @cls{t::Object}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return obj->check_type(t::ARRAY_TYPE);
      }

      /**
       * Replaces each item with t::gNULL.
       */
      public: void clear();

      /**
       * Replaces an item of a @cls{t::Array} with t::gNULL.
       *
       * @param item_index The index of the item to replace with t::gNULL.
       */
      public: void clear_item (UInt64 item_index);

      /**
       * Replaces a range of items with t::gNULL.
       *
       * @param range_start The index at which to start clearing.
       * @param range_end The index at which to stop clearing.
       */
      public: void clear_range(UInt64 range_start, UInt64 range_end);

      /**
       * Replaces an item with another one.
       *
       * @param item_index The index of the item to set.
       * @param new_value A value to use a replacement
       */
      public: void set_item(UInt64 item_index, Value new_value);

      /**
       * Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param type A pointer to a @cls{t::Class} to use a type.
       */
      public: inline void set_item_type(ushort type)
      {
         this->set_item_type(type, NULL);
      }

      /**
       * Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param type A pointer to a @cls{t::Class} to use a type.
       * @param cls The class to use.
       */
      public: void set_item_type(ushort type, vm::Class* cls);

      /**
       * Allocates memory for @prm{array_size} items in array [this->items] and
       * fills each dimension with t::gNULL.
       *
       * @param array_size The size of the array.
       */
      public: void size (UInt64 array_size);
   };
}

#endif
