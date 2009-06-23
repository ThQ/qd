#ifndef T_LIST
#define T_LIST NS_TYPE::List

#include <stdlib.h>
#include <stdio.h>

#include "t/Collection.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tLIST;

   /**
    * A list is an ordered and resizable collection of objects.
    *
    * If you want a fixed size collection, use t::Array.
    */
   class List : public Collection
   {
      public: T_OBJECT** items; ///< An array of @cls{t::Object}s.

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
       * Replaces each item of a list with NULL.
       *
       * @param list The list to clear.
       */
      public: void clear();

      /**
       * Destroys a @cls{t::List}.
       *
       * @param pList A pointer to a @cls{t::List} to destroy.
       * @return true if everything went OK.
       */
      public: static bool destroy(Object* pList);

      /**
       * If a list contains other lists, recursively replaces those lists
       * with their own items.
       *
       * @param list A list to flatten.
       * @return A new list with all elements from [list] flattened.
       */
      public: List* flatten();

      /**
       * Gets an item at [index]  from [list].
       *
       * @param index The position at which to get an item.
       * @return An object from [list] at [index].
       */
      public: Object* get_item(UInt64 index);

      /**
       * Inserts an object into [list] at [index].
       *
       * @param index The position at which to insert an item.
       */
      public: void insert(UInt64 index, Object* obj);

      /**
       * Pops one object off [list].
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
      public: static void print(Object* pList);

      /**
       * Prints a string represention on a new line in the console.
       *
       * @param pList The list to print.
       */
      public: static void print_line(Object* pList);

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
       * Creates a t::List filled with the items of [list] reverser (First becomes last, etc.).
       *
       * @return A new list with all objects reversed.
       */
      public: Object* reverse();

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
       * Gets a slice from [list] from [start] to [end] stepping [step].
       *
       * @param list The list to slice.
       * @param start Slice start.
       * @param end Slice end.
       * @param step Slice step.
       * @return A new list containing the slice.
       */
      public: List* slice(UInt64 start, UInt64 end, UInt64 step);
   };
}

#endif
