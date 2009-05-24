#ifndef T_INT
#define T_INT t::Int
#define T_INTEGER T_INT

#include <stdio.h>
#include <stdlib.h>

#include "t/Class.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"

namespace NS_TYPE
{
   extern T_OBJECT* tINT;

   /**
    * An integer used in the VM.
    */
   class Int : T_OBJECT
   {
      public: long int value;

      public: Int();
      public: static T_OBJECT* add(T_OBJECT* base, T_OBJECT* to_add);
      public: static T_OBJECT* add_to(T_OBJECT* &base, T_OBJECT* to_add);

      /**
       * Asserts that an object is of type t::Int.
       *
       * @param obj An object to be checked.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tINT);
      }

      /**
       * Builds an empty t::Int
       *
       * @return An empty t::Int.
       */
      public: static T_OBJECT* build();

      /**
       * Creates a t::Int from a float.
       * @param value A float
       * @return A t::Int whose value is base on a rounded float.
       */
      public: static T_OBJECT* build(float value);

      /**
       * Creates a t::Int from a long.
       *
       * @param value A long
       * @return a t::Int whose value is base on a (eventually rounded) long.
       */
      public: static T_OBJECT* build(long value);

      /**
       * Creates a new t::Int whose value is the one of [obj].
       *
       * @param obj A base t::Int.
       * @return A new t::Int with the same value as [obj].
       */
      public: static T_OBJECT* build(T_OBJECT* obj);

      /**
       * Creates a t::String representing [i] in decimal.
       *
       * @param i A base t::Int.
       * @return A t::String representing [i].
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* i);

      /**
       * Creates a t::String representing [i] in base [base].
       *
       * @param i A base t::Int.
       * @param base The base to use to represent [i].
       * @return A t::String representing [i] in base [base].
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* i, T_OBJECT* base);

      /*
       * Checks if an object is of type t::Int.
       *
       * @param obj An object to be checked.
       * @return true if [obj] is of type t::Int.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tINT);
      }

      /**
       * Compares two t::Int.
       * @param i1 First t::Int.
       * @param i2 Second t::Int.
       * @return 0 if i1==i2, -1 if i1 <i2 and 1 otherwise.
       */
      public: static Short compare_to(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Creates a new t::Int whose value is [base] / [divider].
       *
       * @param base A base t::Int.
       * @param divider A t::Int used to divide [base].
       * @return The result.
       */
      public: static T_OBJECT* divide(T_OBJECT* base, T_OBJECT* divider);
      public: static T_OBJECT* modulus(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Creates a new t::Int whose value is [base] * [item].
       *
       * @param base A base t::Int.
       * @param item A t::Int used as multiplier.
       * @return The result.
       */
      public: static T_OBJECT* multiply(T_INT* base, T_INT* item);

      /**
       * Multiply an t::Int by another one, in place.
       *
       * @param base A base t::Int.
       * @param i A t::Int used a multiplier.
       * @return [base].
       * @todo Is this really relevant ? t::Int's are immutable right ?
       */
      public: static T_OBJECT* multiply_to(T_OBJECT* &base, T_OBJECT* i);

      /**
       * Prints a t::Int to the console.
       *
       * @param i A t::Int to be printed.
       */
      public: static void print(T_OBJECT* i);

      /**
       * Prints a t::Int to the console on a new line.
       *
       * @param i A t::Int to be printed.
       */
      public: static void print_line(T_OBJECT* i);

      /**
       * Makes a t::List filled with t::Int ranging from [self] to [to] stepping [step].
       *
       * @param self Start of the range.
       * @param to End of the range.
       * @param step Step of the range.
       * @return The t::List.
       * @todo Move it to util/Int.
       */
      public: static T_OBJECT* range_to(T_OBJECT* self, T_OBJECT* to, T_OBJECT* step);

      /**
       * Subtracts a t::Int with another.
       *
       * @param i1 A base t::Int.
       * @param i2 A t::Int to substract to [i1].
       * @return The result of the substraction as a t::Int.
       */
      public: static T_OBJECT* substract(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Subtracts a t::Int with another, in place.
       *
       * @param i1 A base t::Int.
       * @param i2 A t::Int to substract to [i1].
       * @return [base]
       * @todo Is this really relevant ? t::Int's are immutable right ?
       */
      public: static T_OBJECT* subtract_to(T_OBJECT* base, T_OBJECT* n);
   };
}

#endif
