#ifndef T__EXCEPTION__H
#define T__EXCEPTION__H __FILE__

#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"
#include "vm/Class.h"

namespace t
{
   extern vm::Class cEXCEPTION;

   /**
    * @brief An exception signaling an error in a program flow.
    *
    * An exception is stored in t::Block::exception of the block that threw it.
    * After each opcode call, vm::Engine checks if the block contains one,
    * if it's the case, it will look for an exception handler (starting in
    * the current block, and going up the call stack). If one is found, it's
    * ran, otherwise the exception is printed on the screen, and the script
    * stopped.
    */
   class Exception : public Object
   {
      public: String*   message;       ///< Error message.
      public: List*     stack_trace;   ///< A representation of the stack trace when the exception was thrown.

      /**
       * @brief Constructor.
       */
      public: Exception ();

      /**
       * @brief Constructs an exception with a message.
       *
       * @param pMessage The exception message.
       */
      public: Exception (String* pMessage);

      /**
       * @brief Constructs an exception with a message and a stack trace.
       *
       * @param pMessage The exception message.
       * @param pStackTrace The exception stack trace.
       */
      public: Exception (String* pMessage, List* pStackTrace);

      /**
       * @brief Asserts that an object is of type @cls{t::Exception}.
       *
       * @param pObject Object to test.
       */
      public: inline static void assert (Object* pObject)
      {
         return pObject->assert_type(t::EXCEPTION_TYPE);
      }

      /**
       * @brief Builds a string from an exception @prm{error}.
       *
       * @param pException The exception from which to build a string.
       * @return A @cls{t::String} representing the exception.
       * @todo Include the stack trace.
       */
      public: static String* cast_to_string (Exception* pException);

      /**
       * @brief Checks if an object is of type @cls{t::Exception}.
       *
       * @param pObject An object to be checked.
       * @return true if @prm{obj} is of type @cls{t::Exception}.
       */
      public: inline static bool check (Object* pObject)
      {
         return pObject->check_type(t::EXCEPTION_TYPE);
      }

      /**
       * @brief Builds a string from exception @prm{error} and prints it to the
       * console.
       *
       * @param pException An exception that will be converted to string so as to be printed
       */
      public: static void print (Exception* pException);

      /**
       * @brief Builds a string from exception @prm{error} and prints it to the
       * console on a new line.
       *
       * @param pException An exception that will be converted to string so as to be printed
       */
      public: static void print_line (Exception* pException);

      /**
       * @brief Sets the message of exception @prm{error} to @prm{message}.
       *
       * @param pMessage The message to use.
       */
      public: void set_message (String* pMessage);

      /**
       * @brief Sets the stack trace of exception @prm{exception} to @prm{stack_trace}.
       *
       * @param pStackTrace The stack trace to use
       */
      public: void set_stack_trace (List* pStackTrace);
   };
}

#endif
