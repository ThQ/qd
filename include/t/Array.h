#ifndef T_ARRAY
#define T_ARRAY t::Array

#include "t/Int.h"
#include "t/Object.h"

namespace NS_TYPE
{
   extern Object* tARRAY;

   /**
    * A t::Array is a list of t::Object's who can only contain elements of a
    * predetermined type and who can never exceed a predetermined number of
    * elements.
    */
   class Array: public T_OBJECT
   {
      public: Object* type;
      public: Object** items;
      public: ULong item_count;

      public: Array();
      public: ~Array();

      /**
       * Asserts that an object is of type t::Array
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Creates a t::Array object of type <type> and length <len>.
       */
      public: static Object* build(T_OBJECT* type, T_OBJECT* len);

      /**
       * Creates a t::Array object of type <type> and length <len>.
       */
      public: static Object* build(T_OBJECT* type, ULong len);

      /**
       * Creates a t::Array object of type <type> and length <len>
       * and who contains <items>.
       *
       * Take care: <len> must be the length of objects in <items>.
       */
      public: static Object* build(T_OBJECT* type, ULong len, T_OBJECT** items);

      /*
       * Checks if an object is of type t::Array.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Replaces each item of a t::Array with svm::Null.
       */
      public: static void clear(T_OBJECT* arr);

      /**
       * Replaces an item of a t::Array with svm::Null.
       */
      public: static void clear_item(T_OBJECT* arr, ULong at);

      /**
       * Replaces a range of items (from <start> to <end>) with svm::Null.
       */
      public: static void clear_range(T_OBJECT* arr, ULong start, ULong end);

      /**
       * Replaces the item at <at> in <arr> with <obj>.
       */
      public: static void set_item(T_OBJECT* array, ULong at, Object* obj);

      /**
       * Sets the type of the objects that can possibly be stored in a
       * t::Array.
       */
      public: static void set_type(T_OBJECT* obj, T_OBJECT* type);
   };
}

#endif
