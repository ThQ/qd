#ifndef T_ARRAY
#define T_ARRAY t::Array

#include "t/Int.h"
#include "t/Collection.h"

namespace t
{
   extern Object* tARRAY;

   /**
    * A @cls{t::Array} is a list of @cls{t::Object}'s who can only contain elements of a
    * predetermined type and who can never exceed a predetermined (and fixed) number of
    * elements.
    */
   class Array: public Collection
   {
      public: Object* type; ///< A pointer to a @cls{t::Class} representing the class of the objects stored.
      public: Object** items; ///< The @cls{t::Object} stored.
      /// @todo attribute [length] is from t::Collection, remove [item_count].
      public: ULong item_count; ///< Number of item stored.

      /**
       * Constructor.
       */
      public: Array();

      /**
       * Destructor.
       */
      public: ~Array();

      /**
       * Asserts that an object is of type @cls{t::Array}
       *
       * @param obj The object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Creates a t::Array object of type @prm{array_type} and length @prm{array_length}.
       * @param array_type A pointer to a @cls{t::Class} to use a array type.
       * @param array_length A pointer to a @cls{t::Int} representing the length of the array to create.
       * @return A pointer to a @cls{t::Array} newly created.
       */
      public: static Object* build(T_OBJECT* array_type, T_OBJECT* array_length);

      /**
       * Creates a @cls{t::Array} object of type @prm{array_type} and length @prm{array_length}.
       *
       * @param array_type A pointer to a @cls{t::Class} to use a array type.
       * @param array_length The length of the array to create.
       * @return A pointer to a @cls{t::Array} newly created.
       */
      public: static Object* build(T_OBJECT* array_type, ULong array_length);

      /**
       * Creates a @cls{t::Array} object of type @prm{array_type} and length
       * @prm{array_length} and who contains @prm{array_items}.
       *
       * Take care: @prm{array_length} must be the length of objects in @prm{items}.
       *
       * @param array_type A pointer to a @cls{t::Class} to use a array type.
       * @param array_length The length of the array to create.
       * @param array_items An array of @cls{t::Object}'s to populate the new array.
       * @return A pointer to a @cls{t::Array} newly created.
       */
      public: static Object* build(T_OBJECT* array_type, ULong array_length, T_OBJECT** array_items);

      /**
       * Checks if an object is of type @cls{t::Array}.
       *
       * @param obj A pointer to a @cls{t::Object} to check.
       * @return true if @prm{obj} is a pointer to a @cls{t::Object}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Replaces each item with t::gNULL.
       */
      public: void clear();

      /**
       * Replaces each item of a @cls{t::Array} with t::gNULL.
       *
       * @param arr A pointer to a @cls{t::Array} to clear.
       */
      public: inline static void clear (T_OBJECT* arr)
      {
         Array::assert(arr);
         ((Array*)arr)->clear();
      }

      /**
       * Replaces an item of a @cls{t::Array} with t::gNULL.
       *
       * @param item_index The index of the item to replace with t::gNULL.
       */
      public: void clear_item (ULong item_index);

      /**
       * Replaces an item of a @cls{t::Array} with t::gNULL.
       *
       * @param array A pointer to a @cls{t::Array} to clear.
       * @param item_index The index of the item to replace with t::gNULL.
       */
      public: inline static void clear_item (T_OBJECT* array, ULong item_index)
      {
         Array::assert(array);
         ((Array*)array)->clear_item(item_index);
      }

      /**
       * Replaces a range of items with t::gNULL.
       *
       * @param range_start The index at which to start clearing.
       * @param range_end The index at which to stop clearing.
       */
      public: void clear_range(ULong range_start, ULong range_end);

      /**
       * Replaces a range of items with t::gNULL.
       *
       * @param array A pointer to a @cls{t::Array} to clear.
       * @param start The index at which to start clearing.
       * @param end The index at which to stop clearing.
       */
      public: inline static void clear_range(T_OBJECT* array, ULong start, ULong end)
      {
         Array::assert(array);
         ((Array*)array)->clear_range(start, end);
      }

      /**
       * Replaces an item with another one.
       *
       * @param item_index The index of the item to set.
       * @param new_item A pointer to an object to use as a replacement.
       */
      public: void set_item(ULong item_index, T_OBJECT* new_item);

      /**
       * Replaces an item with another one.
       *
       * @param array A pointer to a @cls{t::Array} to set an item to.
       * @param item_index The index of the item to set.
       * @param new_item A pointer to an @cls{t::Object} to use as a replacement.
       */
      public: static void set_item(T_OBJECT* array, ULong item_index, Object* new_item)
      {
         Array::assert(array);
         T_OBJECT::assert_not_null(new_item);
         ((Array*)array)->set_item(item_index, new_item);
      }

      /**
       * Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param type A pointer to a @cls{t::Class} to use a type.
       */
      public: void set_type(T_CLASS* type);

      /**
       * Sets the type of the objects that can possibly be stored in a
       * @cls{t::Array}.
       *
       * @param array A pointer to a @cls{t::Array} to set the type.
       * @param type A pointer to a @cls{t::Class} to use a type.
       */
      public: inline static void set_type(T_OBJECT* array, T_OBJECT* type)
      {
         Array::assert(array);
         T_CLASS::assert(type);
         ((Array*)array)->set_type((T_CLASS*)type);
      }

      /**
       * Allocates memory for @prm{array_size} items in array [this->items] and
       * fills each dimension with t::gNULL.
       *
       * @param array_size The size of the array.
       */
      public: void size (ULong array_size);
   };
}

#endif
