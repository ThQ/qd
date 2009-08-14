#ifndef T__LIST__H
#define T__LIST__H __FILE__

#include <stdlib.h>
#include <stdio.h>

#include "t/BaseArray.h"

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
   class List : public BaseArray
   {
      /**
       * @brief Default Constructor
       */
      public: List ();

      /**
       * @brief Initializes a list with an item type.
       *
       * @param ItemType The type of the items stored.
       */
      public: List (ushort ItemType);

      /**
       * @brief Initializes a list with an item type and class.
       *
       * @param ItemType The type of the items stored.
       * @param pItemClass The class of the items stored.
       */
      public: List (ushort ItemType, vm::Class* pItemClass);

      /**
       * @brief Deletes a t::List.
       *
       * @param pObject The t::List to delete.
       */
      public: static void __delete__ (Value pObject);

      /**
       * @brief Creates a new t::List.
       *
       * @return A pointer to the t::List created.
       */
      public: static Value __new__ ();

      /**
       * @brief Prints the string representation of an list.
       *
       * @param o An list to print.
       * @todo Make it print objects too.
       */
      public: static void __print__ (Value o);

      /**
       * @brief Prints on a new line the string representation of an list.
       *
       * @param pObject An list to print.
       */
      public: static void __print_line__ (Value pObject);

      /**
       * @brief Asserts that an object is of type t::List.
       *
       * @param obj Object to check.
       */
      public: inline static void assert (Object* obj)
      {
         obj->assert_type(t::LIST_TYPE);
      }

      /**
       * @brief Checks if an object is of type t::List.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type t::List.
       */
      public: inline static bool check (Object* obj)
      {
         return obj->check_type(t::LIST_TYPE);
      }

      /**
       * @brief Copies a list.
       *
       * @return The list copied to another object.
       */
      public: List* copy ();

      /**
       * @brief If a list contains other lists, recursively replaces those lists
       * with their own items.
       *
       * @return A new list with all elements from [list] flattened.
       */
      public: List* copy_flatten ();

      /**
       * @brief Creates a t::List filled with the items of [list] reverser (First becomes last, etc.).
       *
       * @return A new list with all objects reversed.
       */
      public: Object* copy_reverse ();

      /**
       * @brief Destroys a @cls{t::List}.
       *
       * @param pList A pointer to a @cls{t::List} to destroy.
       * @return true if everything went OK.
       */
      public: static bool destroy (Value pList);

      /**
       * @brief Inserts a value.
       *
       * @param index The position at which to insert an item.
       * @param pValue A pointer to an object to insert.
       */
      public: void insert (uint index, Value pValue);

      /**
       * @brief Inserts an object
       *
       * @param index The position at which to insert an item.
       * @param pObj A pointer to an object to insert.
       */
      public: inline void insert (uint index, Object* pObj)
      {
         pObj->pick();
         this->insert(index, (Value)pObj);
      }

      /**
       * @brief Pops one object off.
       *
       * @todo Make it less REALLOC intensive.
       */
      public: void pop ();

      /**
       * @brief Pops n objects off [list].
       *
       * @param num The number of items to pop.
       */
      public: void pop (uint num);

      /**
       * @brief Prints a string represention in the console.
       *
       * @param pList The list to print.
       */
      public: static void print (Value pList);

      /**
       * @brief Prints a string represention on a new line in the console.
       *
       * @param pList The list to print.
       */
      public: static void print_line (Value pList);

      /**
       * @brief Pushes a bool.
       *
       * @param b A boolean to push.
       */
      public: inline void push (Bool b)
      {
         this->push((Value)b);
      }

      public: inline void push (int nValue)
      {
         this->push ((Value)nValue);
      }

      /**
       * @brief Pushes an object
       *
       * @param pObject An object to push.
       */
      public: inline void push (Object* pObject)
      {
         this->push((Value)pObject);
         pObject->pick();
      }

      /**
       * @brief Pushes a value.
       *
       * @param pValue A value to push.
       */
      public: void push (Value pValue);

      /**
       * @brief Pushes items from [push_list] into [base_list].
       *
       * @param push_list The list from which items will be pushed.
       */
      public: void push_list (List* push_list);

      /**
       * @brief Removes an object at [index] from [list].
       *
       * @param index The index of the item to remove.
       */
      public: void remove_item (uint index);

      /**
       * @brief Resizes [list] to its new [size].
       *
       * @param size The new size of the list.
       */
      public: void resize (uint size);

      /**
       * @brief Slices the list.
       *
       * @param start Slice start.
       * @param end Slice end.
       * @return A new list containing the slice.
       */
      public: List* slice (uint start, uint end)
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
      public: List* slice (uint start, uint end, uint step);
   };
}

#endif
