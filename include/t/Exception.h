#ifndef T_EXCEPTION
#define T_EXCEPTION t::Exception

#include "t/Int.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tEXCEPTION;
   extern T_OBJECT* tRUNTIME_EXCEPTION;
   extern T_OBJECT* tINDEX_OUT_OF_RANGE_EXCEPTION;

   /**
    * An exception signaling an error in a program flow.
    */
   class Exception : public Object
   {
      public: T_OBJECT* message;       ///< Error message.
      public: T_OBJECT* stack_trace;   ///< A representation of the stack trace when the exception was thrown.

      /**
       * Constructor.
       */
      public: Exception();

      /**
       * Asserts that an object is of type @cls{t::Exception}.
       *
       * @param obj Object to test.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tEXCEPTION);
      }

      /**
       * Builds an empty exception.
       *
       * @return An emtpy @cls{t::Exception}
       */
      public: static T_OBJECT* build();

      /**
       * Builds an exception with message @prm{message}.
       *
       * @param message Error message.
       * @return A @cls{t::Exception} with a message.
       */
      public: static T_OBJECT* build(T_OBJECT* message);

      /**
       * Builds a string from an exception @prm{error}.
       *
       * @param error The exception from which to build a string.
       * @return A @cls{t::String} representing the exception.
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* error);

      /**
       * Checks if an object is of type @cls{t::Exception}.
       *
       * @param obj An object to be checked.
       * @return true if @prm{obj} is of type @cls{t::Exception}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tEXCEPTION);
      }

      /**
       * Builds a string from exception @prm{error} and prints it to the console.
       *
       * @param error An exception that will be converted to string so as to be printed
       */
      public: static void print(T_OBJECT* error);

      /**
       * Sets the message of exception @prm{error} to @prm{message}.
       *
       * @param error The exception to set the message to
       * @param message The message to use
       * @return The message (unchanged)
       */
      public: static T_OBJECT* set_message(T_OBJECT* error, T_OBJECT* message);

      /**
       * Sets the stack trace of exception @prm{exception} to @prm{stack_trace}.
       *
       * @param exception The exception to set the stack trace to
       * @param stack_trace The stack trace to use
       * @return The stack trace (unchanged)
       */
      public: static T_OBJECT* set_stack_trace(T_OBJECT* exception, T_OBJECT* stack_trace);
   };
}

#endif
