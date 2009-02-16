#ifndef MODULES_BOOL_H
#define MODULES_BOOL_H

include(`../../module.m4')

#include <stdio.h>
#include "debug.h"
#include "svm/Bool.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"


namespace modules { namespace system {

   class Bool
   {
      public: static SVM_CLASS_METHOD(print)
      {
         ASSERT(argc == 1, "system.Bool.print(system.Bool). %d arguments given", argc);
         SVM_ASSERT_BOOL(argv[0]);

         if (argv[0] == svm::False) printf("False\n");
         else printf("True\n");

         return svm::Null;
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::bool_type);
         SVM_ASSERT_CLASS(svm::bool_type);

         METHOD(svm::bool_type, `print', print)
         PARAM(`self', svm::bool_type)
         RETURNS(svm::object_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::True);
         ASSERT_NULL(svm::False);
         ASSERT_NULL(svm::bool_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::bool_type = engine.classes.declare_class("system.Bool", svm::object_type);
         SVM_ASSERT_NOT_NULL(svm::bool_type);
         SVM_PICK(svm::bool_type);

         svm::True = svm::Bool::build(1);
         SVM_ASSERT_NOT_NULL(svm::True);
         SVM_PICK(svm::True);

         svm::False = svm::Bool::build(0);
         SVM_ASSERT_NOT_NULL(svm::False);
         SVM_PICK(svm::False);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::True);
         SVM_DROP(svm::False);
         SVM_DROP(svm::bool_type);
      }
   };

} }

#endif
