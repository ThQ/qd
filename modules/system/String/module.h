#ifndef MODULES_STRING_H
#define MODULES_STRING_H

include(`../../module.m4')dnl

#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/String.h"
#include "svm/StringUtil.h"

namespace modules { namespace system {

   class String
   {
      public: static SVM_CLASS_METHOD(append)
      {
         svm::String::append(argv[0], argv[1]);
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(center_si)
      {
         return svm::String::center(argv[0], argv[1], svm::String::build(" "));
      }

      public: static SVM_CLASS_METHOD(center_sis)
      {
         return svm::String::center(argv[0], argv[1], argv[2]);
      }

      public: static SVM_CLASS_METHOD(compare_to)
      {
         Short i = svm::String::compare_to(argv[0], argv[1]);
         return svm::Int::build((Long)i);
      }

      public: static SVM_METHOD(construct)
      {
         svm::Object* s = svm::String::build();
         return s;
      }

      public: static SVM_CLASS_METHOD(find)
      {
         svm::Object* result = svm::String::find(argv[0], argv[1], argv[2]);
         return result;
      }

      public: static SVM_CLASS_METHOD(is_alphabetic)
      {
         return svm::String::is_alphabetic(argv[0]);
      }

      public: static SVM_CLASS_METHOD(is_digit)
      {
         return svm::String::is_digit(argv[0]);
      }

      public: static SVM_CLASS_METHOD(is_lowercase)
      {
         return svm::String::is_lowercase(argv[0]);
      }

      public: static SVM_CLASS_METHOD(is_space)
      {
         return svm::String::is_space(argv[0]);
      }

      public: static SVM_CLASS_METHOD(is_uppercase)
      {
         return svm::String::is_uppercase(argv[0]);
      }

      public: static SVM_CLASS_METHOD(lower)
      {
         return svm::String::lower(argv[0]);
      }

      public: static SVM_CLASS_METHOD(multiply)
      {
         svm::String::multiply(argv[0], argv[1]);
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(print)
      {
         svm::String::print(argv[0]);
         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(reverse_s)
      {
         return svm::String::reverse(argv[0]);
      }

      public: static SVM_CLASS_METHOD(strip_ssii)
      {
         svm::Object* result = svm::String::strip(argv[0], argv[1], argv[2], argv[3]);
         return result;
      }

      public: static SVM_CLASS_METHOD(upper)
      {
         return svm::String::upper(argv[0]);
      }

      public: static SVM_CLASS_METHOD(swap_case)
      {
         return svm::String::swap_case(argv[0]);
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::string_type);

         FUNCTION(`system.String.__construct__', construct)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `append', append)
         PARAM(`self', svm::string_type)
         PARAM(`string', svm::string_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `center', center_si)
         PARAM(`self', svm::string_type)
         PARAM(`length', svm::int_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `center', center_sis)
         PARAM(`self', svm::string_type)
         PARAM(`length', svm::int_type)
         PARAM(`filling', svm::string_type)
         RETURNS(svm::string_type);

         METHOD(svm::string_type, `compare_to', compare_to)
         PARAM(`self', svm::string_type)
         PARAM(`another_string', svm::string_type)
         RETURNS(svm::int_type);

         METHOD(svm::string_type, `find', find)
         PARAM(`self', svm::string_type)
         PARAM(`substring', svm::string_type)
         PARAM(`start_search_at', svm::int_type)
         RETURNS(svm::int_type)

         METHOD(svm::string_type, `is_alphabetic', is_alphabetic)
         PARAM(`self', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::string_type, `is_digit', is_digit)
         PARAM(`self', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::string_type, `is_lowercase', is_lowercase)
         PARAM(`self', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::string_type, `is_uppercase', is_uppercase)
         PARAM(`self', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::string_type, `lower_case', lower)
         PARAM(`self', svm::string_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `is_space', is_space)
         PARAM(`self', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::string_type, `multiply', multiply)
         PARAM(`self', svm::string_type)
         PARAM(`times', svm::int_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `print', print)
         PARAM(`self', svm::string_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `reverse', reverse_s)
         PARAM(`self', svm::string_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `strip', strip_ssii)
         PARAM(`self', svm::string_type)
         PARAM(`characters', svm::string_type)
         PARAM(`start_at', svm::int_type)
         PARAM(`end_at', svm::int_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `swap_case', swap_case)
         PARAM(`self', svm::string_type)
         RETURNS(svm::string_type)

         METHOD(svm::string_type, `upper_case', upper)
         PARAM(`self', svm::string_type)
         RETURNS(svm::string_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::string_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::string_type = engine.classes.declare_class("system.String", svm::object_type);
         SVM_ASSERT_CLASS(svm::string_type);
         SVM_PICK(svm::string_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::string_type);
      }
   };
} }

#endif
