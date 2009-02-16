#ifndef MODULES_SYSTEM_FLOAT_H

include(`../../module.m4')

#define MODULES_SYSTEM_FLOAT_H
#define MODULE_SYSTEM_FLOAT

#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/Float.h"

namespace modules { namespace system {

   class Float
   {
      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::float_type);
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::float_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::float_type = engine.classes.declare_class("system.Float", svm::object_type);
         SVM_ASSERT_CLASS(svm::float_type);
         SVM_PICK(svm::float_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::float_type);
      }
   };

} }

#endif
