#ifndef T_INT
#define T_INT t::Int
#define T_INTEGER T_INT

#include <stdio.h>
#include <stdlib.h>

#include "t/Class.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tINT;

   /**
    * An integer used in the VM.
    */
   class Int : Object
   {
      public: long int value; ///< Int value.

      /**
       * Constructor.
       */
      public: Int();

      /**
       * Computes the addition of two @cls{t::Int}s.
       *
       * @param int1 First @cls{t::Int}.
       * @param int2 Second @cls{t::Int}.
       * @return @prm{int1} + @prm{int2}
       */
      public: static T_OBJECT* add(T_OBJECT* int1, T_OBJECT* int2);

      /**
       * Adds an @cls{t::Int} to another one.
       *
       * @param base_int Base @cls{t::Int}. Its value will be modified.
       * @param int_to_add Another @cls{t::Int} whose value will be added to @prm{base_int}.
       * @return @prm{int1}
       */
      public: static T_OBJECT* add_to(T_OBJECT* &base_int, T_OBJECT* int_to_add);

      /**
       * Asserts that an object is of type @cls{t::Int}.
       *
       * @param obj An object to be checked.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::tINT);
      }

      /**
       * Builds an empty @cls{t::Int}.
       *
       * @return A pointer to a @cls{t::Int} newly created.
       */
      public: static T_OBJECT* build();

      /**
       * Creates a @cls{t::Int} from a float.
       * @param value A float
       * @return A pointer to a @cls{t::Int} newly created whose value is base on a rounded float.
       */
      public: static T_OBJECT* build(float value);

      /**
       * Creates a @cls{t::Int} from a long.
       *
       * @param value A long
       * @return A pointer to a @cls{t::Int} newly created whose value is base on a (eventually rounded) long.
       */
      public: static T_OBJECT* build(long value);

      /**
       * Creates a new @cls{t::Int} whose value is the one of [obj].
       *
       * @param obj A base @cls{t::Int}.
       * @return A pointer to a @cls{t::Int} newly created with the same value as [obj].
       */
      public: static T_OBJECT* build(T_OBJECT* obj);

      /**
       * Creates a @cls{t::String} representing @prm{i} in decimal.
       *
       * @param i A base @cls{t::Int}.
       * @return A @cls{t::String} representing @prm{i}.
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* i);

      /**
       * Creates a t::String representing @prm{i} in base @prm{base}.
       *
       * @param i A base @cls{t::Int}.
       * @param base The base to use to represent @prm{i}.
       * @return A @cls{t::String} representing @prm{i} in base @prm{base}.
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* i, T_OBJECT* base);

      /**
       * Checks if an object is of type @cls{t::Int}.
       *
       * @param obj An object to be checked.
       * @return true if @prm{obj} is of type @cls{t::Int}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tINT);
      }

      /**
       * Compares two @cls{t::Int}.
       * @param i1 First @cls{t::Int}.
       * @param i2 Second @cls{t::Int}.
       * @return 0 if @prm{i1}==@prm{i2}, -1 if @prm{i1} < @prm{i2} and 1 otherwise.
       */
      public: static Short compare_to(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Creates a new @cls{t::Int} whose value is @prm{base} / @prm{divider}.
       *
       * @param base A base @cls{t::Int}.
       * @param divider A @cls{t::Int} used to divide @prm{base}.
       * @return The result.
       */
      public: static T_OBJECT* divide(T_OBJECT* base, T_OBJECT* divider);

      /**
       * Computes the modulus of two @cls{t::Int}.
       *
       * @param i1 First @cls{t::Int}.
       * @param i2 Second @cls{t::Int}.
       * @return @prm{i1} % @prm{i2}.
       */
      public: static T_OBJECT* modulus(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Creates a new @cls{t::Int} whose value is @prm{base} * @prm{item}.
       *
       * @param base A base @cls{t::Int}.
       * @param item A @cls{t::Int} used as multiplier.
       * @return The result.
       */
      public: static T_OBJECT* multiply(T_INT* base, T_INT* item);

      /**
       * Multiply an @cls{t::Int} by another one, in place.
       *
       * @param base A base @cls{t::Int}.
       * @param i A @cls{t::Int} used a multiplier.
       * @return @prm{base}.
       * @todo Is this really relevant ? @cls{t::Int}'s are immutable right ?
       */
      public: static T_OBJECT* multiply_to(T_OBJECT* &base, T_OBJECT* i);

      /**
       * Prints a @cls{t::Int} to the console.
       *
       * @param i A @cls{t::Int} to be printed.
       */
      public: static void print(T_OBJECT* i);

      /**
       * Prints a @cls{t::Int} to the console on a new line.
       *
       * @param i A @cls{t::Int} to be printed.
       */
      public: static void print_line(T_OBJECT* i);

      /**
       * Makes a @cls{t::List} filled with @cls{t::Int} ranging from @prm{self} to @prm{to} stepping @prm{step}.
       *
       * @param self Start of the range.
       * @param to End of the range.
       * @param step Step of the range.
       * @return The @prm{t::List}.
       * @todo Move it to util/Int.
       */
      public: static T_OBJECT* range_to(T_OBJECT* self, T_OBJECT* to, T_OBJECT* step);

      /**
       * Subtracts a @cls{t::Int} with another.
       *
       * @param i1 A base @cls{t::Int}.
       * @param i2 A @cls{t::Int} to substract to @prm{i1}.
       * @return The result of the substraction as a @cls{t::Int}.
       */
      public: static T_OBJECT* substract(T_OBJECT* i1, T_OBJECT* i2);

      /**
       * Subtracts a @cls{t::Int} with another, in place.
       *
       * @param base_int A base @cls{t::Int}.
       * @param int_to_substract A @cls{t::Int} to substract to @prm{i1}.
       * @return @prm{base}
       * @todo Is this really relevant ? @cls{t::Int}'s are immutable right ?
       */
      public: static T_OBJECT* subtract_to(T_OBJECT* base_int, T_OBJECT* int_to_substract);
   };
}

#endif
