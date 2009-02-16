#ifndef MODULES_SYSTEM_LIST_H

include(`../../module.m4')

#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/List.h"

#define MODULES_SYSTEM_LIST_H
#define MODULE_SYSTEM_LIST


#include "modules/system/List.h"

namespace modules { namespace system
{
   class List
   {
      public: static SVM_METHOD(construct)
      {
         svm::Object* l = svm::List::build();
         return l;
      }

      public: static SVM_CLASS_METHOD(get_item)
      {
         ASSERT(argc == 2, "system.List.get_item : 2 parameters. (Not %d)", argc);
         SVM_ASSERT_LIST(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result = svm::List::get_item(argv[0], ((svm::Int*)argv[1])->value);

         return result;
      }

      public: static SVM_CLASS_METHOD(pop)
      {
         ASSERT(argc == 2, "system.List.pop : 2 parameters. (Not %d)", argc);
         SVM_ASSERT_LIST(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result = svm::List::pop(argv[0], ((svm::Int*)argv[1])->value);

         return result;
      }

      public: static SVM_CLASS_METHOD(push)
      {
         ASSERT(argc == 2, "system.List.push : 2 parameters. (Not %d)\n", argc);
         SVM_ASSERT_LIST(argv[0]);
         SVM_ASSERT_NOT_NULL(argv[1]);

         svm::List::append(argv[0], argv[1]);

         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(set_item)
      {
         ASSERT(argc == 3, "system.List.set_item : 3 parameters. (Not %d)\n", argc);
         SVM_ASSERT_LIST(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result = svm::List::set_item(argv[0], ((svm::Int*)argv[1])->value, argv[2]);

         return result;
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::list_type);
         SVM_ASSERT_NOT_NULL(svm::int_type);

         FUNCTION(`system.List.__construct__', construct)
         PARAM(`self', svm::list_type)
         RETURNS(svm::list_type)

         METHOD(svm::list_type, `get_item', get_item)
         PARAM(`self', svm::list_type)
         PARAM(`index', svm::int_type)
         RETURNS(svm::object_type)

         METHOD(svm::list_type, `pop', pop)
         PARAM(`self', svm::list_type)
         PARAM(`num', svm::int_type)
         RETURNS(svm::object_type)

         METHOD(svm::list_type, `push', push)
         PARAM(`self', svm::list_type)
         PARAM(`obj', svm::object_type)
         RETURNS(svm::object_type)

         METHOD(svm::list_type, `set_item', set_item)
         PARAM(`self', svm::list_type)
         PARAM(`index', svm::int_type)
         PARAM(`obj', svm::object_type)
         RETURNS(svm::object_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::list_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::list_type = engine.classes.declare_class("system.List", svm::object_type);
         SVM_ASSERT_CLASS(svm::list_type);
         SVM_PICK(svm::list_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::list_type);
      }
   };

} }

#endif
