#ifndef T_LIST
#define T_LIST NS_TYPE::List

#include <stdlib.h>
#include <stdio.h>

#include "t/Object.h"
#include "t/String.h"

namespace NS_TYPE
{
   extern T_OBJECT* tLIST;

   /**
    * A list is an ordered and resizable collection of objects.
    *
    * If you want a fixed size collection, use t::Array.
    */
   class List : T_OBJECT
   {
      public: UInt length;
      public: T_OBJECT** items;

      /**
       * Constructor
       */
      public: List();

      /**
       * Asserts that an object is of type t::List.
       *
       * @param obj Object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tLIST);
      }

      /**
       * Appends an item to a list
       *
       * @param list A list to append to.
       * @param obj An object to append.
       * @return [list]
       * @deprecated (Use List::push(...) instead) Appends an object to a list.
       */
      public: static T_OBJECT* append(T_OBJECT* list, T_OBJECT* obj);

      /**
       * Creates an empty t::List.
       *
       * @return An empty list.
       */
      public: static T_OBJECT* build();

      /**
       * Checks if an object is of type t::List.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type t::List.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tLIST);
      }

      /**
       * Replaces each item of a list with t::gNULL.
       *
       * @param list The list to clear.
       * @return Cleared [list]
       */
      public: static T_OBJECT* clear(T_OBJECT* list);

      /**
       * If a list contains other lists, recursively replaces those lists
       * with their own items.
       *
       * @param list A list to flatten.
       * @return A new list with all elements from [list] flattened.
       */
      public: static T_OBJECT* flatten(T_OBJECT* list);

      /**
       * Gets an item at [index]  from [list].
       *
       * @param list A List to get an item from.
       * @param index The position at which to get an item.
       * @return An object from [list] at [index].
       */
      public: static T_OBJECT* get_item(T_OBJECT* list, UInt index);

      /**
       * Inserts an object into [list] at [index].
       *
       * @param list A list to insert an item into.
       * @param index The position at which to insert an item.
       * @param obj The object to insert.
       * @return [list].
       */
      public: static T_OBJECT* insert(T_OBJECT* list, UInt index, T_OBJECT* obj);

      /**
       * Pops one object off [list].
       *
       * @param list A list from which to pop an object off.
       * @return The object popped.
       */
      public: static T_OBJECT* pop(T_OBJECT* list);

      /**
       * Pops n objects off [list].
       *
       * @param list A list from which to pop some objects off.
       * @param num The number of items to pop.
       * @return The last item of list before popping.
       */
      public: static T_OBJECT* pop(T_OBJECT* list, UInt num);

      /**
       * Pushes an object onto [list].
       *
       * @param list A list to push to.
       * @param obj An object to push.
       * @return [list].
       */
      public: static T_OBJECT* push(T_OBJECT* list, T_OBJECT* obj);

      /**
       * Pushes items from [push_list] into [base_list].
       *
       * @param base_list A list to push to.
       * @param push_list The list from which items will be pushed.
       */
      public: static void push_list(T_OBJECT* base_list, T_OBJECT* push_list);

      /**
       * Removes an object at [index] from [list].
       * @param list A list from which to remove items.
       * @param index The index of the item to remove.
       * @return [list].
       */
      public: static T_OBJECT* remove_item(T_OBJECT* list, UInt index);

      /**
       * Creates a t::List filled with the items of [list] reverser (First becomes last, etc.).
       *
       * @param list The list to reverse
       * @return A new list with all objects reversed.
       */
      public: static T_OBJECT* reverse(T_OBJECT* list);

      /**
       * Resizes [list] to its new [size].
       *
       * @param list The list to resize.
       * @param size The new size of the list.
       * @return [list].
       */
      public: static T_OBJECT* resize(T_OBJECT* list, UInt size);

      /**
       * Sets the object of a list at a specified index.
       *
       * @param list The list to set an item to.
       * @param at The position at which to set the item in [list].
       * @param obj The object to set at [at].
       * @return [list].
       */
      public: static T_OBJECT* set_item(T_OBJECT* list, UInt at, T_OBJECT* obj);

      /**
       * Gets a slice from [list] from [start] to [end] stepping [step].
       *
       * @param list The list to slice.
       * @param start Slice start.
       * @param end Slice end.
       * @param step Slice step.
       * @return A new list containing the slice.
       */
      public: static T_OBJECT* slice(T_OBJECT* list, UInt start, UInt end, UInt step);
   };
}

#endif
