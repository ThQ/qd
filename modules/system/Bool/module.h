#ifndef MODULES_BOOL_H
#define MODULES_BOOL_H

include(`../../module.m4')

#include <stdio.h>
#include "t/Bool.h"
#include "t/CoreFunction.h"
#include "vm/Engine.h"


namespace modules { namespace system {

   class Bool
   {
      public: static SVM_CLASS_METHOD(print)
      {
         ASSERT(argc == 1, "system.Bool.print(system.Bool). %d arguments given", argc);
         t::Bool::assert(argv[0]);

         if (argv[0] == t::gFALSE) printf("False\n");
         else printf("True\n");

         return svm::Null;
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(t::tBOOL);
         t::Class::assert(t::tBOOL);

         METHOD(t::tBOOL, `print', print)
         PARAM(`self', t::tBOOL)
         RETURNS(t::tOBJECT)
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::gTRUE);
         ASSERT_NULL(t::gFALSE);
         ASSERT_NULL(t::tBOOL);
      }

      public: static void initialize(svm::Engine& engine)
      {
         t::tBOOL = engine.classes.declare_class("system.Bool", t::tOBJECT);
         SVM_ASSERT_NOT_NULL(t::tBOOL);
         t::Object::pick(t::tBOOL);

         t::gTRUE = t::Bool::build(1);
         SVM_ASSERT_NOT_NULL(t::gTRUE);
         t::Object::pick(t::gTRUE);

         t::gFALSE = t::Bool::build(0);
         SVM_ASSERT_NOT_NULL(t::gFALSE);
         t::Object::pick(t::gFALSE);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         t::Object::drop(t::gTRUE);
         t::Object::drop(t::gFALSE);
         t::Object::drop(t::tBOOL);
      }
   };

} }

#endif
