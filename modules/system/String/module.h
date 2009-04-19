#ifndef MODULES_STRING_H
#define MODULES_STRING_H

include(`../../module.m4')dnl

#include "t/CoreFunction.h"
#include "t/String.h"
#include "util/String.h"
#include "vm/Engine.h"

namespace modules
{
   namespace system
   {
      class String
      {
         public: static SVM_CLASS_METHOD(append)
         {
            t::String::append(argv[0], argv[1]);
            return t::gNULL;
         }

         public: static SVM_CLASS_METHOD(center_si)
         {
            return t::String::center(argv[0], argv[1], t::String::build(" "));
         }

         public: static SVM_CLASS_METHOD(center_sis)
         {
            return t::String::center(argv[0], argv[1], argv[2]);
         }

         public: static SVM_CLASS_METHOD(compare_to)
         {
            Short i = t::String::compare_to(argv[0], argv[1]);
            return t::Int::build((Long)i);
         }

         public: static SVM_METHOD(construct)
         {
            t::Object* s = t::String::build();
            return s;
         }

         public: static SVM_CLASS_METHOD(find)
         {
            t::Object* result = t::String::find(argv[0], argv[1], argv[2]);
            return result;
         }

         public: static SVM_CLASS_METHOD(is_alphabetic)
         {
            return t::String::is_alphabetic(argv[0]);
         }

         public: static SVM_CLASS_METHOD(is_digit)
         {
            return t::String::is_digit(argv[0]);
         }

         public: static SVM_CLASS_METHOD(is_lowercase)
         {
            return t::String::is_lowercase(argv[0]);
         }

         public: static SVM_CLASS_METHOD(is_space)
         {
            return t::String::is_space(argv[0]);
         }

         public: static SVM_CLASS_METHOD(is_uppercase)
         {
            return t::String::is_uppercase(argv[0]);
         }

         public: static SVM_CLASS_METHOD(lower)
         {
            return t::String::lower(argv[0]);
         }

         public: static SVM_CLASS_METHOD(multiply)
         {
            t::String::multiply(argv[0], argv[1]);
            return t::gNULL;
         }

         public: static SVM_CLASS_METHOD(print)
         {
            t::String::print(argv[0]);
            return t::gNULL;
         }

         public: static SVM_CLASS_METHOD(reverse_s)
         {
            return t::String::reverse(argv[0]);
         }

         public: static SVM_CLASS_METHOD(strip_ssii)
         {
            t::Object* result = t::String::strip(argv[0], argv[1], argv[2], argv[3]);
            return result;
         }

         public: static SVM_CLASS_METHOD(upper)
         {
            return t::String::upper(argv[0]);
         }

         public: static SVM_CLASS_METHOD(swap_case)
         {
            return t::String::swap_case(argv[0]);
         }

         public: static void declare_methods(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tSTRING);

            FUNCTION(`system.String.__construct__', construct)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `append', append)
            PARAM(`self', t::tSTRING)
            PARAM(`string', t::tSTRING)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `center', center_si)
            PARAM(`self', t::tSTRING)
            PARAM(`length', t::tINT)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `center', center_sis)
            PARAM(`self', t::tSTRING)
            PARAM(`length', t::tINT)
            PARAM(`filling', t::tSTRING)
            RETURNS(t::tSTRING);

            METHOD(t::tSTRING, `compare_to', compare_to)
            PARAM(`self', t::tSTRING)
            PARAM(`another_string', t::tSTRING)
            RETURNS(t::tINT);

            METHOD(t::tSTRING, `find', find)
            PARAM(`self', t::tSTRING)
            PARAM(`substring', t::tSTRING)
            PARAM(`start_search_at', t::tINT)
            RETURNS(t::tINT)

            METHOD(t::tSTRING, `is_alphabetic', is_alphabetic)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tBOOL)

            METHOD(t::tSTRING, `is_digit', is_digit)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tBOOL)

            METHOD(t::tSTRING, `is_lowercase', is_lowercase)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tBOOL)

            METHOD(t::tSTRING, `is_uppercase', is_uppercase)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tBOOL)

            METHOD(t::tSTRING, `lower_case', lower)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `is_space', is_space)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tBOOL)

            METHOD(t::tSTRING, `multiply', multiply)
            PARAM(`self', t::tSTRING)
            PARAM(`times', t::tINT)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `print', print)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `reverse', reverse_s)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `strip', strip_ssii)
            PARAM(`self', t::tSTRING)
            PARAM(`characters', t::tSTRING)
            PARAM(`start_at', t::tINT)
            PARAM(`end_at', t::tINT)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `swap_case', swap_case)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tSTRING)

            METHOD(t::tSTRING, `upper_case', upper)
            PARAM(`self', t::tSTRING)
            RETURNS(t::tSTRING)
         }

         public: static void finalize()
         {
            ASSERT_NULL(t::tSTRING);
         }

         public: static void initialize(vm::Engine& engine)
         {
            t::tSTRING = engine.classes.declare_class("system.String", t::tOBJECT);
            t::Class::assert(t::tSTRING);
            t::Object::pick(t::tSTRING);
         }

         public: static void tear_down(vm::Engine& engine)
         {
            t::Object::drop(t::tSTRING);
         }
      };
   }
}

#endif
