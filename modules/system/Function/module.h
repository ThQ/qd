#ifndef MODULES_FUNCTION_H

include(`../../module.m4')

#define MODULES_FUNCTION_H


#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"

namespace modules { namespace system {

   class Function
   {
      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_CLASS(svm::bad_argument_type_exception_type);
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::bad_argument_type_exception_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::bad_argument_type_exception_type = engine.classes.declare_class("system.BadArgumentTypeException", svm::exception_type);
         SVM_ASSERT_CLASS(svm::bad_argument_type_exception_type);
         SVM_PICK(svm::bad_argument_type_exception_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::bad_argument_type_exception_type);
      }
   };

} }

#endif
