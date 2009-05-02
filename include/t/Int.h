#ifndef T_INT
#define T_INT t::Int
#define T_INTEGER T_INT

#include <stdio.h>
#include <stdlib.h>

#include "t/Class.h"
#include "t/List.h"
#include "t/Object.h"
#include "t/String.h"


#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_INT(i) \
   DEPRECATED(); \
   if(!T_INT::check(i)) \
   { \
      FATAL("Bad type given, expected system.Int\n\n"); \
      abort(); \
   }
#else
   #define SVM_ASSERT_INT(i) DEPRECATED();
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_INT(i) \
   DEPRECATED(); \
   if(!T_INT::check(i)) \
   { \
      WARNING("Bad type given, expected system.Int\n\n"); \
   }
#else
   #define SVM_CHECK_INT(i) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* tINT;

   class Int : Object
   {
      public: long int value;

      public: Int();
      public: static T_OBJECT* add(T_OBJECT* base, T_OBJECT* to_add);
      public: static T_OBJECT* add_to(T_OBJECT* &base, T_OBJECT* to_add);

      /**
       * Asserts that an object is of type t::Int
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         T_OBJECT::assert_type(obj, NS_TYPE::int_type);
      }

      public: static T_OBJECT* build();
      public: static T_OBJECT* build(float value);
      public: static T_OBJECT* build(long value);
      public: static T_OBJECT* build(T_OBJECT* obj);
      public: static T_OBJECT* cast_to_string(T_OBJECT* i);
      public: static T_OBJECT* cast_to_string(T_OBJECT* i, T_OBJECT* base);

      /*
       * Checks if an object is of type t::Int.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::int_type);
      }

      public: static Short compare_to(T_OBJECT* i1, T_OBJECT* i2);
      public: static void debug_id(T_OBJECT* base);
      public: static T_OBJECT* divide(T_OBJECT* base, T_OBJECT* divider);
      public: static T_OBJECT* modulus(T_OBJECT* i1, T_OBJECT* i2);
      public: static T_OBJECT* multiply(T_INT* base, T_INT* item);
      public: static T_OBJECT* multiply_to(T_OBJECT* &base, T_OBJECT* i);
      public: static void print(T_OBJECT* i);
      public: static void print_line(T_OBJECT* i);
      public: static T_OBJECT* range_to(T_OBJECT* self, T_OBJECT* to, T_OBJECT* step);
      public: static T_OBJECT* substract(T_OBJECT* i1, T_OBJECT* i2);
      public: static T_OBJECT* subtract_to(T_OBJECT* base, T_OBJECT* n);
   };
}

#endif
