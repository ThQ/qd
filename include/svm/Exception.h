#ifndef SVM_ERROR_H
#define SVM_ERROR_H

#include "debug.h"
#include "svm/Int.h"
#include "svm/List.h"
#include "svm/Object.h"
#include "svm/String.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_EXCEPTION(e) if(e->cls != svm::exception_type){FATAL("Bad type given, expected system.Exception.\n\n");abort();}
#else
   #define SVM_ASSERT_EXCEPTION(e)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_EXCEPTION(i) if(e->cls != svm::exception_type){WARNING("Bad type given, expected system.Exception.\n\n");}
#else
   #define SVM_CHECK_EXCEPTION(i)
#endif



namespace svm
{
   extern Object* exception_type;
   extern Object* runtime_exception_type;
   extern Object* index_out_of_range_exception_type;

   class Exception : public Object
   {
      public: Object* message;
      public: Object* stack_trace;

      public: Exception();
      public: static Object* build();
      public: static Object* build(Object* message);
      public: static Object* cast_to_string(Object* error);
      public: static bool check(Object* error);
      public: static void print(Object* error);
      public: static Object* set_message(Object* error, Object* message);
      public: static Object* set_stack_trace(Object* exception, Object* stack_trace);
   };
}

#endif
