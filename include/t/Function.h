#ifndef T_FUNCTION
#define T_FUNCTION t::Function

#define SVM_FUNCTION_NAME_LENGTH 256

#include <stdarg.h>
#include <string.h>

#include "t/Class.h"
#include "t/Exception.h"
#include "t/String.h"
#include "t/Variable.h"

namespace NS_TYPE
{
   extern T_OBJECT* tFUNCTION;
   extern T_OBJECT* tBAD_ARGUMENT_TYPE_EXCEPTION;

   class Function : public T_OBJECT
   {
      //public: const char* signature;
      public: std::string name;
      public: T_OBJECT* return_type;
      public: T_CLASS type;
      public: T_OBJECT** arguments;
      public: UInt arguments_count;
      public: bool is_static;
      public: bool is_user;

      public: Function();
      public: ~Function();

      /**
       * Asserts that an object is of type t::tFUNCTION.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tFUNCTION);
      }

      #ifdef _DEBUG_
      public: void assert_validity();
      #endif

      /**
       * Builds a string from a function <func>.
       */
      public: static T_OBJECT* cast_to_string(T_OBJECT* func);

      /*
       * Checks if an object is of type t::Function.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tFUNCTION);
      }

      /**
       * Builds a string from a function <func> and prints it to the console.
       */
      public: static void print(T_OBJECT* func);

      /**
       * Sets the arguments.
       */
      public: void set_arguments(UInt count, ...);

      /**
       * Sets the arguments.
       */
      public: void set_arguments(UInt count, T_OBJECT** args);

      /**
       * Sets the return type to <type>.
       */
      public: void set_return_type(T_OBJECT* type);
   };
}
#endif
