#ifndef SVM_FUNCTION_H
#define SVM_FUNCTION_H

#define SVM_FUNCTION_NAME_LENGTH 256

#include <stdarg.h>
#include <string.h>
#include <unicode/unistr.h>

#include "svm/Class.h"
#include "svm/Exception.h"
#include "svm/String.h"
#include "svm/Variable.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_FUNCTION(f) if(f->cls != svm::function_type){FATAL("<svm::Object*(@%ld).type(@%ld) != <svm::function_type(@%ld)>.\n", (long int)(f), (long int)f->cls, (long int)svm::function_type);abort();}
#else
   #define SVM_ASSERT_FUNCTION(f)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_FUNCTION(f) if(f->cls != svm::function_type){WARNING("Bad type given, expected system.Function.\n");}
#else
   #define SVM_CHECK_FUNCTION(f)
#endif

namespace svm
{
   extern Object* function_type;
   extern Object* bad_argument_type_exception_type;

   class Function : public Object
   {
      //public: const char* signature;
      public: std::string name;
      public: Object* return_type;
      public: Class type;
      public: Object** arguments;
      public: UInt arguments_count;
      public: bool is_static;
      public: bool is_user;

      public: Function();
      public: ~Function();
      #ifdef _DEBUG_
      public: void assert_validity();
      #endif
      public: static Object* cast_to_string(Object* func);
      public: static bool check(Object* func);
      public: static void print(Object* func);
      public: void set_arguments(int count, ...);
      public: void set_arguments(int count, Object** args);
      public: void set_return_type(Object* type);
   };
}
#endif
