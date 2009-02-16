#ifndef SVM_NUMBER_H
#define SVM_NUMBER_H


#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "svm/Class.h"
#include "svm/List.h"
#include "svm/Object.h"
#include "svm/String.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_INT(i) if(!svm::Int::check(i)){FATAL("Bad type given, expected system.Int\n\n");abort();}
#else
   #define SVM_ASSERT_INT(i)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_INT(i) if(!svm::Int::check(i)){WARNING("Bad type given, expected system.Int\n\n");}
#else
   #define SVM_CHECK_INT(i)
#endif

namespace svm
{
   extern Object* int_type;

   class Int : Object
   {
      public: long int value;

      public: Int();
      public: static Object* add(Object* base, Object* to_add);
      public: static Object* add_to(Object* &base, Object* to_add);
      public: static Object* build();
      public: static Object* build(float value);
      public: static Object* build(long value);
      public: static Object* build(Object* obj);
      public: static Object* cast_to_string(Object* i);
      public: static Object* cast_to_string(Object* i, Object* base);
      public: static bool check(Object* obj);
      public: static Short compare_to(Object* i1, Object* i2);
      public: static void debug_id(Object* base);
      public: static Object* divide(Object* base, Object* divider);
      public: static Object* modulus(Object* i1, Object* i2);
      public: static Object* multiply(Int* base, Int* item);
      public: static Object* multiply_to(Object* &base, Object* i);
      public: static void print(Object* i);
      public: static void print_line(Object* i);
      public: static Object* range_to(Object* self, Object* to, Object* step);
      public: static Object* substract(Object* i1, Object* i2);
      public: static Object* subtract_to(Object* base, Object* n);
   };
}

#endif
