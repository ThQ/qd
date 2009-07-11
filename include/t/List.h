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
    * @brief An ordered and resizable collection of values.
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
       * @brief If a list contains other lists, recursively replaces those lists
       * with their own items.
       *
       * @return A new list with all elements from [list] flattened.
       */
      public: List* copy_flatten();

      /**
       * @brief Creates a t::List filled with the items of [list] reverser (First becomes last, etc.).
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
       * @param obj A pointer to an object to insert.
       */
      public: void insert(UInt64 index, Object* obj);

      /**
       * @brief Pops one object off.
       *
       * @todo Make it less REALLOC intensive.
       */
      public: void pop();

      /**
       * @brief Pops n objects off [list].
       *
       * @param num The number of items to pop.
       */
      public: void pop(UInt64 num);

      /**
       * @brief Prints a string represention in the console.
       *
       * @param pList The list to print.
       */
      public: static void print(Value pList);

      /**
       * @brief Prints a string represention on a new line in the console.
       *
       * @param pList The list to print.
       */
      public: static void print_line(Value pList);

      /**
       * @brief Pushes a bool.
       *
       * @param b A boolean to push.
       */
      public: inline void push(Bool b)
      {
         this->push((Value)b);
      }

      /**
       * @brief Pushes a Int8.
       *
       * @param i A Int8 to push.
       */
      public: inline void push(Int8 i)
      {
         this->push((Value)i);
      }
      /**
       * @brief Pushes a Int16.
       *
       * @param i A Int16 to push.
       */
      public: inline void push(Int16 i)
      {
         this->push((Value)i);
      }
      /**
       * @brief Pushes a Int32.
       *
       * @param i A Int32 to push.
       */
      public: inline void push(Int32 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes a Int64.
       *
       * @param i A Int64 to push.
       */
      public: inline void push(Int64 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes a UInt8.
       *
       * @param i A UInt8 to push.
       */
      public: inline void push(UInt8 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes a UInt16.
       *
       * @param i A UInt16 to push.
       */
      public: inline void push(UInt16 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes a UInt32.
       *
       * @param i A UInt32 to push.
       */
      public: inline void push(UInt32 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes a UInt64.
       *
       * @param i A UInt64 to push.
       */
      public: inline void push(UInt64 i)
      {
         this->push((Value)i);
      }

      /**
       * @brief Pushes an object
       *
       * @param pObject An object to push.
       */
      public: inline void push(Object* pObject)
      {
         this->push((Value)pObject);
         pObject->pick();
      }

      /**
       * @brief Pushes a value.
       *
       * @param pValue A value to push.
       */
      public: void push(Value pValue);

      /**
       * @brief Pushes items from [push_list] into [base_list].
       *
       * @param push_list The list from which items will be pushed.
       */
      public: void push_list(List* push_list);

      /**
       * @brief Removes an object at [index] from [list].
       *
       * @param index The index of the item to remove.
       */
      public: void remove_item(UInt64 index);

      /**
       * @brief Resizes [list] to its new [size].
       *
       * @param size The new size of the list.
       */
      public: void resize(UInt64 size);

      /**
       * @brief Sets an item.
       *
       * @param at The position at which to set the item in [list].
       * @param obj The object to set at [at].
       * @return [list].
       */
      public: void set_item(UInt64 at, Object* obj);

      /**
       * @brief Slices the list.
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
       * @brief Slices the list.
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
