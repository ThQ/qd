#ifndef MODULES_SYSTEM_EXCEPTION_H

include(`../../module.m4')

#define MODULES_SYSTEM_EXCEPTION_H
#define MODULE_SYSTEM_EXCEPTION

#include "debug.h"
#include "svm/Engine.h"
#include "svm/Exception.h"
#include "svm/CoreFunction.h"

namespace modules { namespace system {

   class Exception
   {
      public: static SVM_METHOD(construct)
      {
         ASSERT(argc == 0, "system.Exception.__construct__(). %d parameters given.", argc);
         return svm::Exception::build();
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::exception_type);
         SVM_ASSERT_NOT_NULL(svm::runtime_exception_type);
         SVM_ASSERT_NOT_NULL(svm::class_not_found_exception_type);
         SVM_ASSERT_NOT_NULL(svm::class_not_found_exception_type);

         FUNCTION(`system.Exception.__construct__', construct)
         RETURNS(svm::exception_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::exception_type);
         ASSERT_NULL(svm::runtime_exception_type);
         ASSERT_NULL(svm::class_not_found_exception_type);
         ASSERT_NULL(svm::index_out_of_range_exception_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::exception_type = engine.classes.declare_class("system.Exception", svm::object_type);
         SVM_ASSERT_NOT_NULL(svm::exception_type);
         SVM_PICK(svm::exception_type);

         svm::runtime_exception_type = engine.classes.declare_class("system.RuntimeException", svm::exception_type);
         SVM_ASSERT_NOT_NULL(svm::runtime_exception_type);
         SVM_PICK(svm::runtime_exception_type);

         svm::class_not_found_exception_type = engine.classes.declare_class("system.ClassNotFoundException", svm::exception_type);
         SVM_ASSERT_NOT_NULL(svm::class_not_found_exception_type);
         SVM_PICK(svm::class_not_found_exception_type);

         svm::index_out_of_range_exception_type = engine.classes.declare_class("system.IndexOutOfRangeException", svm::exception_type);
         SVM_ASSERT_NOT_NULL(svm::index_out_of_range_exception_type);
         SVM_PICK(svm::index_out_of_range_exception_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::index_out_of_range_exception_type);
         SVM_DROP(svm::runtime_exception_type);
         SVM_DROP(svm::class_not_found_exception_type);
         SVM_DROP(svm::exception_type);
      }
   };

} }

#endif
