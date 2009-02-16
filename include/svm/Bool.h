#ifndef SVM_BOOL_H
#define SVM_BOOL_H

#include "svm/Object.h"
#include "svm/String.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_BOOL(o) SVM_ASSERT_NOT_NULL(o); if(o->cls != svm::bool_type){FATAL("Bad type given, expected <system.Bool>.\n");abort();}
#else
   #define SVM_ASSERT_BOOL(o)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_BOOL(o) SVM_CHECK_NOT_NULL(o); if(o->cls != svm::bool_type){WARNING("Bad type given, expected <system.Bool>.\n");}
#else
   #define SVM_CHECK_BOOL(o)
#endif

namespace svm
{
   extern Object* bool_type;
   extern Object* True;
   extern Object* False;

   class Bool : public Object
   {
      public: bool value;

      public: Bool();
      public: static Object* build(bool b);
      public: static Object* build(int i);
      public: static Object* cast_to_string(Object* b);
      public: static Object* copy(Object* b);
      public: static bool check(Object* b);
      public: static bool is_false(Object* b);
      public: static bool is_true(Object* b);
      public: static void print(Object* b);
      public: static void print_line(Object* b);
      public: static Object* reverse(Object* b);
   };
}

#endif
