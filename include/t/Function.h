#ifndef T_FUNCTION
#define T_FUNCTION t::Function

#define SVM_FUNCTION_NAME_LENGTH 256

#include <stdarg.h>
#include <string.h>

#include "t/Class.h"
#include "t/Exception.h"
#include "t/String.h"
#include "t/Variable.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define __SVM_ASSERT_FUNCTION(f) \
   if(f->cls != t::function_type) \
   { \
      FATAL( \
            "<svm::T_OBJECT*(@%ld).type(@%ld) != <svm::function_type(@%ld)>.\n", \
            (long int)(f), \
            (long int)f->cls, \
            (long int)t::function_type \
     ); \
     abort(); \
   }
#else
   #define __SVM_ASSERT_FUNCTION(f)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define __SVM_CHECK_FUNCTION(f) if(f->cls != t::function_type){WARNING("Bad type given, expected system.Function.\n");}
#else
   #define __SVM_CHECK_FUNCTION(f)
#endif

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
      public: static T_OBJECT* cast_to_string(T_OBJECT* func);

      /*
       * Checks if an object is of type t::Function.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tFUNCTION);
      }

      public: static void print(T_OBJECT* func);
      public: void set_arguments(UInt count, ...);
      public: void set_arguments(UInt count, T_OBJECT** args);
      public: void set_return_type(T_OBJECT* type);
   };
}
#endif
