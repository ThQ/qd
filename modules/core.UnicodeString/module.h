#ifndef MODULES_USTRING_H
#define MODULES_USTRING_H

include(`../../module.m4')dnl

#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/UString.h"

namespace modules { namespace system {

   class UString
   {
      public: static SVM_CLASS_METHOD(append)
      {
         svm::UString::append(argv[0], argv[1]);
         return svm::Null;
      }

      public: static SVM_METHOD(construct)
      {
         svm::Object* s = svm::UString::build();
         return s;
      }

      public: static SVM_CLASS_METHOD(find)
      {
         svm::Object* result = svm::UString::find(argv[0], argv[1], argv[2]);
         return result;
      }

      public: static SVM_CLASS_METHOD(lower)
      {
         ((svm::UString*)argv[0])->value.toLower();
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(multiply)
      {
         svm::UString::multiply(argv[0], argv[1]);
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(print)
      {
         svm::UString* s = (svm::UString*)argv[0];
         printf("\"");
         svm::UString::print_unicode_string(s->value);
         printf("\"\n");
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(strip)
      {
         svm::Object* result = svm::UString::strip(argv[0], argv[1], argv[2], argv[3]);
         return result;
      }

      public: static SVM_CLASS_METHOD(upper)
      {
         ((svm::UString*)argv[0])->value.toUpper();
         return svm::Null;
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::ustring_type);

         FUNCTION(`system.UString.__construct__', construct)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `append', append)
         PARAM(`self', svm::ustring_type)
         PARAM(`string', svm::ustring_type)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `find', find)
         PARAM(`self', svm::ustring_type)
         PARAM(`substring', svm::ustring_type)
         PARAM(`start_search_at', svm::int_type)
         RETURNS(svm::int_type)

         METHOD(svm::ustring_type, `lower', lower)
         PARAM(`self', svm::ustring_type)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `multiply', multiply)
         PARAM(`self', svm::ustring_type)
         PARAM(`times', svm::int_type)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `print', print)
         PARAM(`self', svm::ustring_type)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `strip', strip)
         PARAM(`self', svm::ustring_type)
         PARAM(`characters', svm::ustring_type)
         PARAM(`start_at', svm::int_type)
         PARAM(`end_at', svm::int_type)
         RETURNS(svm::ustring_type)

         METHOD(svm::ustring_type, `upper', upper)
         PARAM(`self', svm::ustring_type)
         RETURNS(svm::ustring_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::ustring_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::ustring_type = engine.classes.declare_class("system.UString", svm::object_type);
         SVM_ASSERT_CLASS(svm::ustring_type);
         SVM_PICK(svm::ustring_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::ustring_type);
      }
   };
} }

#endif
