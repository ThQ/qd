#ifndef T_EXCEPTION
#define T_EXCEPTION t::Exception

#include "t/Int.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"

namespace NS_TYPE
{
   extern T_OBJECT* tEXCEPTION;
   extern T_OBJECT* tRUNTIME_EXCEPTION;
   extern T_OBJECT* tINDEX_OUT_OF_RANGE_EXCEPTION;

   /**
    * An exception signaling an error in a program flow.
    */
   class Exception : public T_OBJECT
   {
      public: T_OBJECT* message;
      public: T_OBJECT* stack_trace;

      /**
       * Constructor.
       */
      public: Exception();

      /**
       * Asserts that an object is of type t::Exception.
       *
       * @param obj Object to test
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tEXCEPTION);
      }

      /**
       * Builds an empty exception.
       *
       * @return An emtpy t::Exception
       */
      public: static T_OBJECT* build();

      /**
       * Builds an exception with message <message>.
       *
       * @param message Error message
       * @return A t::Exception with a message
       */
      public: static T_OBJECT* build(T_OBJECT* message);

      /**
       * Builds a string from an exception <error>.
       *
       * @param error The exception from which to build a string
       * @return a t::String representing the exception
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* error);

      /*
       * Checks if an object is of type t::Exception.
       *
       * @param obj An object to be checked.
       * @return true if <obj> is of type t::Exception
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tEXCEPTION);
      }

      /**
       * Builds a string from exception <error> and prints it to the console.
       *
       * @param error An exception that will be converted to string so as to be printed
       */
      public: static void print(T_OBJECT* error);

      /**
       * Sets the message of exception <error> to <message>.
       *
       * @param error The exception to set the message to
       * @param message The message to use
       * @return The message (unchanged)
       */
      public: static T_OBJECT* set_message(T_OBJECT* error, T_OBJECT* message);

      /**
       * Sets the stack trace of exception <exception> to <stack_trace>.
       *
       * @param exception The exception to set the stack trace to
       * @param stack_trace The stack trace to use
       * @return The stack trace (unchanged)
       */
      public: static T_OBJECT* set_stack_trace(T_OBJECT* exception, T_OBJECT* stack_trace);
   };
}

#endif
