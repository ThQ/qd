#ifndef T_LIST
#define T_LIST NS_TYPE::List

#include <stdlib.h>
#include <stdio.h>

#include "t/Collection.h"
//#include "t/String.h"

#define T__LIST__ASSERT_IN_RANGE(pList, Index) \
   ASSERT( \
         Index >= 0 && Index < pList->length, \
         "Index [%lu] is out of list range [0:%lu[.", \
         (ulong)Index, \
         (ulong)pList->length \
   );

namespace t
{
   extern vm::Class cLIST;

   /**
    * A list is an ordered and resizable collection of values.
    *
    * If you want a fixed size collection, use t::Array.
    */
   class List : public Collection
   {
      public: ushort item_type;        ///< The type of the values stored.
      public: vm::Class* item_class;   ///< The class of the values stored.
      public: Value* items;            ///< An array of values stored.

      /**
       * @brief Default Constructor
       */
      public: List();

      /**
       * @brief Initializes a list with an item type.
       *
       * @param ItemType The type of the items stored.
       */
      public: List(ushort ItemType);

      /**
       * @brief Initializes a list with an item type and class.
       *
       * @param ItemType The type of the items stored.
       * @param pItemClass The class of the items stored.
       */
      public: List(ushort ItemType, vm::Class* pItemClass);

      /**
       * @brief Asserts that an object is of type t::List.
       *
       * @param obj Object to check.
       */
      public: inline static void assert(Object* obj)
      {
         obj->assert_type(t::LIST_TYPE);
      }

      /**
       * @brief Checks if an object is of type t::List.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type t::List.
       */
      public: inline static bool check(Object* obj)
      {
         return obj->check_type(t::LIST_TYPE);
      }

      /**
       * @brief Replaces each item of a list with NULL.
       *
       * @param list The list to clear.
       * @todo Make it less REALLOC intensive.
       */
      public: void clear();

      /**
       * @brief Copies a list.
       *
       * @return The list copied to another object.
       */
      public: List* copy();

      /**
       * If a list contains other lists, recursively replaces those lists
       * with their own items.
       *
       * @return A new list with all elements from [list] flattened.
       */
      public: List* copy_flatten();

      /**
       * Creates a t::List filled with the items of [list] reverser (First becomes last, etc.).
       *
       * @return A new list with all objects reversed.
       */
      public: Object* copy_reverse();

      /**
       * @brief Destroys a @cls{t::List}.
       *
       * @param pList A pointer to a @cls{t::List} to destroy.
       * @return true if everything went OK.
       */
      public: static bool destroy(Value pList);

      /**
       * @brief Gets an object.
       *
       * @param index The position at which to get the object.
       * @return A pointer to an object.
       */
      public: Value get_object_at(UInt64 index);

      /**
       * @brief Gets a value.
       *
       * @param index The position at which to get the value.
       * @return A value.
       */
      public: Value get_value_at(UInt64 index);

      /**
       * @brief Inserts an object.
       *
       * @param index The position at which to insert an item.
       */
      public: void insert(UInt64 index, Object* obj);

      /**
       * Pops one object off.
       *
       * @todo Make it less REALLOC intensive.
       */
      public: void pop();

      /**
       * Pops n objects off [list].
       *
       * @param num The number of items to pop.
       */
      public: void pop(UInt64 num);

      /**
       * Prints a string represention in the console.
       *
       * @param pList The list to print.
       */
      public: static void print(Value pList);

      /**
       * Prints a string represention on a new line in the console.
       *
       * @param pList The list to print.
       */
      public: static void print_line(Value pList);

      /**
       * Pushes an object onto [list].
       *
       * @param obj An object to push.
       */
      public: void push(Object* obj);

      /**
       * Pushes items from [push_list] into [base_list].
       *
       * @param base_list A list to push to.
       * @param push_list The list from which items will be pushed.
       */
      public: void push_list(List* push_list);

      /**
       * Removes an object at [index] from [list].
       *
       * @param index The index of the item to remove.
       */
      public: void remove_item(UInt64 index);

      /**
       * Resizes [list] to its new [size].
       *
       * @param size The new size of the list.
       */
      public: void resize(UInt64 size);

      /**
       * Sets the object of a list at a specified index.
       *
       * @param at The position at which to set the item in [list].
       * @param obj The object to set at [at].
       * @return [list].
       */
      public: void set_item(UInt64 at, Object* obj);

      /**
       * Slices the list
       *
       * @param start Slice start.
       * @param end Slice end.
       * @return A new list containing the slice.
       */
      public: List* slice(UInt64 start, UInt64 end)
      {
         return this->slice(start, end, 1);
      }

      /**
       * Slices the list
       *
       * @param start Slice start.
       * @param end Slice end.
       * @param step Slice step.
       * @return A new list containing the slice.
       *
       * @todo Make some asserts (start not > end, etc)
       */
      public: List* slice(UInt64 start, UInt64 end, UInt64 step);
   };
}

#endif
