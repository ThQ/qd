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

   class Exception : public T_OBJECT
   {
      public: T_OBJECT* message;
      public: T_OBJECT* stack_trace;

      public: Exception();

      /**
       * Asserts that an object is of type t::tEXCEPTION.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tEXCEPTION);
      }

      public: static T_OBJECT* build();
      public: static T_OBJECT* build(T_OBJECT* message);
      public: static T_OBJECT* cast_to_string(T_OBJECT* error);

      /*
       * Checks if an object is of type t::tEXCEPTION.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tEXCEPTION);
      }

      public: static void print(T_OBJECT* error);
      public: static T_OBJECT* set_message(T_OBJECT* error, T_OBJECT* message);
      public: static T_OBJECT* set_stack_trace(T_OBJECT* exception, T_OBJECT* stack_trace);
   };
}

#endif
