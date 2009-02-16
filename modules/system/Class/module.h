#ifndef MODULES_SYSTEM_CLASS_H
#define MODULES_SYSTEM_CLASS_H

#include "svm/Class.h"

namespace modules { namespace system
{
   class Class
   {
      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::bad_type_exception_type);
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::bad_type_exception_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::bad_type_exception_type = engine.classes.declare_class("system.BadTypeException", svm::object_type);
         SVM_ASSERT_CLASS(svm::bad_type_exception_type);
         SVM_PICK(svm::bad_type_exception_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::bad_type_exception_type);
      }
   };
} }

#endif
