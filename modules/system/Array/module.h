#ifndef MODULES_SYSTEM_ARRAY_H
#define MODULES_SYSTEM_ARRAY_H

#include "svm/Array.h"

namespace modules { namespace system
{
   class Array
   {
      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::array_type);
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::array_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::array_type = engine.classes.declare_class("system.Array", svm::object_type);
         SVM_ASSERT_CLASS(svm::array_type);
         SVM_PICK(svm::array_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::array_type);
      }
   };
} }

#endif
