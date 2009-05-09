#ifndef T_BOOL
#define T_BOOL NS_TYPE::Bool

#include "t/Object.h"
#include "t/String.h"

namespace NS_TYPE
{
   extern T_OBJECT* gTRUE;
   extern T_OBJECT* gFALSE;
   extern T_OBJECT* tBOOL;

   /**
    * A boolean object.
    */
   class Bool : public T_OBJECT
   {
      public: bool value;

      public: Bool();

      /**
       * Asserts that an object is of type t::tBOOL.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Creates a t::Bool from a C boolean.
       */
      public: static T_OBJECT* build(bool b);

      /**
       * Creates a t::Bool from a C integer.
       */
      public: static T_OBJECT* build(int i);

      /**
       * Produces a t::Bool string representation in a t::String.
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* b);

      /*
       * Checks if an object is of type t::Bool.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Makes a copy of a t::Bool
       */
      public: static T_OBJECT* copy(T_OBJECT* b);

      /**
       * Returns true only if an object is svm::False.
       */
      public: static bool is_false(T_OBJECT* b);

      /**
       * Returns true only if an object is svm::True.
       */
      public: static bool is_true(T_OBJECT* b);

      /**
       * Prints the string representation of a t::Bool.
       */
      public: static void print(T_OBJECT* b);

      /**
       * Prints the string representation of a t::Bool on a new line.
       */
      public: static void print_line(T_OBJECT* b);

      /**
       * Returns svm::True if b is svm::False, svm::False otherwise.
       */
      public: static T_OBJECT* reverse(T_OBJECT* b);
   };
}

#endif
