#ifndef T_VARIABLE
#define T_VARIABLE NS_TYPE::Variable

#include <string>

#include "t/Class.h"
#include "t/Object.h"
#include "t/String.h"
#include "util/Object.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define __SVM_ASSERT_VARIABLE(v) DEPRECATED(); if(v->cls != NS_TYPE::tVARIABLE){FATAL("Bad type given, expected system.Variable.\n\n");abort();}
#else
   #define __SVM_ASSERT_VARIABLE(v) DEPRECATED();
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define __SVM_CHECK_VARIABLE(v) DEPRECATED(); if(v->cls != NS_TYPE::tVARIABLE){WARNING("Bad type given, expected system.Variable.\n\n");}
#else
   #define __SVM_CHECK_VARIABLE(v) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* tVARIABLE;

   class Variable : public T_OBJECT
   {
      public: T_OBJECT* object_type;
      public: T_OBJECT* object;
      public: std::string name;

      public: Variable();
      public: ~Variable();

      /**
       * Asserts that an object is of type t::tVARIABLE.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return util::Object::assert_type(obj, NS_TYPE::tVARIABLE);
      }

      /**
       * Creates a t::Variable of type <type>.
       */
      public: static T_OBJECT* build(T_OBJECT* type);

      /**
       * Creates a t::Variable of type <type> and name <name>.
       */
      public: static T_OBJECT* build(T_OBJECT* type, std::string name);

      /*
       * Checks if an object is of type t::tVARIABLE.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Sets the object of a t::Variable.
       */
      public: static T_OBJECT* set(T_OBJECT* variable, T_OBJECT* obj);

      /**
       * Sets the object type a t::Variable can contain.
       */
      public: void set_object_type(T_OBJECT* type);
   };
}

#endif
