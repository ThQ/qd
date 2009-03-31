#ifndef T_LIST
#define T_LIST NS_TYPE::List

#include <stdlib.h>
#include <stdio.h>

#include "t/Object.h"
#include "t/String.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_LIST(o) \
   DEPRECATED() \
   SVM_ASSERT_NOT_NULL(o); \
   if (o->cls != NS_TYPE::tLIST) \
   { \
      FATAL("Should be of type <system.List>.\n"); \
      abort(); \
   }
#else
   #define SVM_ASSERT_LIST(o) DEPRECATED()
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_LIST(o) \
   DEPRECATED() \
   SVM_CHECK_NOT_NULL(o); \
   if (o->cls != NS_TYPE::tLIST) \
   { \
      WARNING("Bad type given, expected <system.List>.\n"); \
   }
#else
   #define SVM_CHECK_LIST(o) DEPRECATED()
#endif

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

      public: List();

      /**
       * Asserts that an object is of type t::List.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tLIST);
      }

      /**
       * DEPRECATED! (Use List::push(...) instead) Appends an object to a list.
       */
      public: static T_OBJECT* append(T_OBJECT* list, T_OBJECT* obj);

      /**
       * Creates an empty t::List.
       */
      public: static T_OBJECT* build();

      /*
       * Checks if an object is of type t::List.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tLIST);
      }

      /**
       * Replaces each item of a list with svm::Null.
       */
      public: static T_OBJECT* clear(T_OBJECT* list);

      /**
       * If a list contains other lists, recursively replaces those lists
       * with their own items.
       */
      public: static T_OBJECT* flatten(T_OBJECT* list);

      /**
       * Gets an item at <index> from <list>.
       */
      public: static T_OBJECT* get_item(T_OBJECT* list, UInt index);

      /**
       * Inserts an object into <list> at <index>.
       */
      public: static T_OBJECT* insert(T_OBJECT* list, UInt index, T_OBJECT* obj);

      /**
       * Pops one object off <list>.
       */
      public: static T_OBJECT* pop(T_OBJECT* list);

      /**
       * Pops n objects off <list>.
       */
      public: static T_OBJECT* pop(T_OBJECT* list, UInt num);

      /**
       * Pushes an object onto <list>.
       */
      public: static T_OBJECT* push(T_OBJECT* list, T_OBJECT* obj);

      /**
       * Pushes items from <push_list> into <base_list>.
       */
      public: static void push_list(T_OBJECT* base_list, T_OBJECT* push_list);

      /**
       * Removes an object at <index> from <list>.
       */
      public: static T_OBJECT* remove_item(T_OBJECT* list, UInt index);

      /**
       * Reverses the items of <list>. (First becomes last, etc.)
       */
      public: static T_OBJECT* reverse(T_OBJECT* list);

      /**
       * Resizes <list> to its new <size>.
       */
      public: static T_OBJECT* resize(T_OBJECT* list, UInt size);

      /**
       * Sets the object of a list at a specified index.
       */
      public: static T_OBJECT* set_item(T_OBJECT* list, UInt at, T_OBJECT* obj);

      /**
       * Gets a slice from <list> from <start> to <end> stepping <step>.
       */
      public: static T_OBJECT* slice(T_OBJECT* list, UInt start, UInt end, UInt step);
   };
}

#endif
