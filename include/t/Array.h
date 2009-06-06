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

      /**
       * Constructor.
       */
      public: Array();

      /**
       * Destructor.
       */
      public: ~Array();

      /**
       * Asserts that an object is of type t::Array
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Creates a t::Array object of type [type] and length [len].
       * @param type A pointer to a t::Class to use a array type.
       * @param len A pointer to a t::Int representing the length of the array to create.
       * @return A pointer to a t::Array newly created.
       */
      public: static Object* build(T_OBJECT* type, T_OBJECT* len);

      /**
       * Creates a t::Array object of type [type] and length [len].
       *
       * @param type A pointer to a t::Class to use a array type.
       * @param len The length of the array to create.
       * @return A pointer to a t::Array newly created.
       */
      public: static Object* build(T_OBJECT* type, ULong len);

      /**
       * Creates a t::Array object of type [type] and length [len]
       * and who contains [items].
       *
       * Take care: [len] must be the length of objects in [items].
       *
       * @param type A pointer to a t::Class to use a array type.
       * @param len The length of the array to create.
       * @param items An array of t::Object's to populate the new array.
       * @return A pointer to a t::Array newly created.
       */
      public: static Object* build(T_OBJECT* type, ULong len, T_OBJECT** items);

      /*
       * Checks if an object is of type t::Array.
       *
       * @param obj A pointer to a t::Object to check.
       * @return true if [obj] is a pointer to a t::Object.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tARRAY);
      }

      /**
       * Replaces each item of a t::Array with t::gNULL.
       *
       * @param arr A pointer to a t::Array to clear.
       */
      public: static void clear(T_OBJECT* arr);

      /**
       * Replaces an item of a t::Array with t::gNULL.
       *
       * @param arr A pointer to a t::Array to clear.
       * @param at The index of the item to replace with t::gNULL.
       */
      public: inline static void clear_item(T_OBJECT* arr, ULong at);

      /**
       * Replaces a range of items (from [start] to [end]) with t::gNULL.
       *
       * @param arr A pointer to a t::Array to clear.
       * @param start The index at which to start clearing.
       * @param end The index at which to stop clearing.
       */
      public: static void clear_range(T_OBJECT* arr, ULong start, ULong end);

      /**
       * Replaces the item at [at] in [array] with [obj].
       *
       * @param array A pointer to a t::Array to set an item to.
       * @param at The index of the item to set.
       * @param obj A pointer to an t::Object to use as a replacement.
       */
      public: static void set_item(T_OBJECT* array, ULong at, Object* obj);

      /**
       * Sets the type of the objects that can possibly be stored in a
       * t::Array.
       *
       * @param array A pointer to a t::Array to set the type.
       * @param type A pointer to a t::Class to use a type.
       */
      public: static void set_type(T_OBJECT* array, T_OBJECT* type);
   };
}

#endif
