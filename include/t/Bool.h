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
       *
       * @param obj A t::Object to be checked.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Creates a t::Bool from a C boolean.
       *
       * @param b A c boolean.
       * @return t::gTRUE if b==true, t::gFALSE otherwise.
       */
      public: static T_OBJECT* build(bool b);

      /**
       * Creates a t::Bool from a C integer.
       *
       * @param i A c integer.
       * @return t::gFALSE if i==0, t::gTRUE otherwise.
       */
      public: static T_OBJECT* build(int i);

      /**
       * Produces a t::Bool string representation in a t::String.
       *
       * @param b A t::Bool to be casted.
       * @return A t::String representing [b].
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* b);

      /*
       * Checks if an object is of type t::Bool.
       *
       * @param obj A pointer to a t::Object to be checked.
       * @return true if obj is a pointer to a t::Bool.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Creates a new t::Bool with the same value as [base_bool].
       *
       * @param base_bool A t::Bool to be copied.
       * @return A new t::Bool with the same value as [base_bool].
       */
      public: static T_OBJECT* copy(T_OBJECT* base_bool);

      /**
       * Returns true only if an t::Bool is t::gFALSE.
       *
       * @param base_bool A t::Bool to be checked.
       * @return t::gTRUE if [base_bool] is t::gFALSE.
       */
      public: static bool is_false(T_OBJECT* base_bool);

      /**
       * Returns true only if an object is t::gTRUE.
       *
       * @param base_bool A t::Bool to be checked.
       * @return t::gTRUE if [base_bool] is t::gTRUE.
       */
      public: static bool is_true(T_OBJECT* base_bool);

      /**
       * Prints the string representation of a t::Bool.
       *
       * @param base_bool A t::Bool to be converted to t::String and printed.
       */
      public: static void print(T_OBJECT* base_bool);

      /**
       * Prints the string representation of a t::Bool on a new line.
       *
       * @param base_bool A t::Bool to be converted to t::String and printed on a new line.
       */
      public: static void print_line(T_OBJECT* base_bool);

      /**
       * Creates a new t::Bool that is the inverse of [base_bool].
       *
       * @param base_bool A t::Bool to reverse.
       * @return A t::Bool that is the inverse of [base_bool] : t::gTRUE if [base_bool] is t::gFALSE, t::gFALSE otherwise.
       */
      public: static T_OBJECT* reverse(T_OBJECT* base_bool);
   };
}

#endif
