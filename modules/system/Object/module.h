#ifndef MODULES_SYSTEM_OBJECT_H
#define MODULES_SYSTEM_OBJECT_H

include(`../../module.m4')

#include "debug.h"
#include "svm/Bool.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/Int.h"
#include "types.h"

namespace modules { namespace system {

   class Object
   {
      public: static SVM_CLASS_METHOD(compare_to)
      {
         Short s = svm::Object::compare_to(argv[0], argv[1]);
         return svm::Int::build((Long)s);
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         METHOD(svm::object_type, `compare_to', compare_to)
         PARAM(`self', svm::object_type)
         PARAM(`another_object', svm::object_type)
         RETURNS(svm::int_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::object_type);
         ASSERT_NULL(svm::function_type);
         ASSERT_NULL(svm::null_type);
         ASSERT_NULL(svm::Null);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::object_type = engine.classes.declare_class("system.Object");
         SVM_ASSERT_CLASS(svm::object_type);
         SVM_PICK(svm::object_type);
         svm::object_type->is_abstract = true;

         svm::function_type = engine.classes.declare_class("system.Function");
         SVM_ASSERT_CLASS(svm::function_type);
         SVM_PICK(svm::function_type);

         svm::null_type = engine.classes.declare_class("system.Null", svm::object_type);
         SVM_ASSERT_CLASS(svm::null_type);
         SVM_PICK(svm::null_type);
         svm::null_type->is_abstract = true;

         svm::Null = new svm::Object();
         svm::Null->set_class(svm::null_type);
         SVM_PICK(svm::Null);

         svm::heap_object_type = engine.classes.declare_class("system.HeapObject", svm::object_type);
         SVM_ASSERT_CLASS(svm::heap_object_type);
         SVM_PICK(svm::heap_object_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::object_type);
         SVM_DROP(svm::function_type);
         SVM_DROP(svm::null_type);
         SVM_DROP(svm::Null);
         SVM_DROP(svm::heap_object_type);
      }
   };

} }

#endif
