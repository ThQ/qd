#ifndef MODULES_INT_H


include(`../../module.m4')

#define MODULES_INT_H

#include <stdio.h>

#include "debug.h"
#include "svm/Bool.h"
#include "svm/Class.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/Int.h"
#include "svm/String.h"
#include "svm/Variable.h"

namespace modules { namespace system {

   class Int
   {
      public: static SVM_CLASS_METHOD(add)
      {
         svm::Int::add_to(argv[0], argv[1]);
         return argv[0];
      }

      public: static SVM_CLASS_METHOD(compare_to)
      {
         Short i = svm::Int::compare_to(argv[0], argv[1]);
         return svm::Int::build((Long)i);
      }

      public: static SVM_CLASS_METHOD(decrement)
      {
         return self;
      }

      public: static SVM_CLASS_METHOD(divide)
      {
         return self;
      }

      public: static SVM_CLASS_METHOD(equals)
      {
         SVM_ASSERT_INT(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result;

         if (((svm::Int*)argv[0])->value == ((svm::Int*)argv[1])->value)
         {
            result = (svm::Object*)svm::True;
         }
         else
         {
            result = (svm::Object*)svm::False;
         }
         return result;
      }


      public: static SVM_CLASS_METHOD(is_greater)
      {
         SVM_ASSERT_INT(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result;

         if (((svm::Int*)argv[0])->value > ((svm::Int*)argv[1])->value)
         {
            result = (svm::Object*)svm::True;
         }
         else
         {
            result = (svm::Object*)svm::False;
         }
         return result;

      }

      public: static SVM_CLASS_METHOD(is_greater_or_equal)
      {
         ASSERT(argc == 2, "Bad argument count.");
         SVM_ASSERT_INT(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Object* result;

         if (((svm::Int*)argv[0])->value >= ((svm::Int*)argv[1])->value)
         {
            result = (svm::Object*)svm::True;
         }
         else
         {
            result = (svm::Object*)svm::False;
         }
         return result;

      }

      public: static SVM_CLASS_METHOD(multiply)
      {
         svm::Int::multiply_to(argv[0], argv[1]);

         return argv[0];
      }

      public: static SVM_CLASS_METHOD(print)
      {
         ASSERT(argc == 1, "Bad argument count.");
         SVM_ASSERT_INT(argv[0]);

         svm::Int::print(argv[0]);

         return svm::Null;
      }

      public: static SVM_CLASS_METHOD(subtract)
      {
         ASSERT(argc == 2, "-=(system.Int, system.Int). %d parameters given.", argc);
         SVM_ASSERT_INT(argv[0]);
         SVM_ASSERT_INT(argv[1]);

         svm::Int::subtract_to(argv[0], argv[1]);

         return argv[0];
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::int_type);

         METHOD(svm::int_type, `*=', multiply)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::int_type)

         METHOD(svm::int_type, `+=', add)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::int_type)

         METHOD(svm::int_type, `compare_to', compare_to)
         PARAM(`self', svm::int_type)
         PARAM(`another_int', svm::int_type)
         RETURNS(svm::int_type)

         METHOD(svm::int_type, `equals', equals)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::bool_type)

         METHOD(svm::int_type, `>=', is_greater_or_equal)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::bool_type)

         METHOD(svm::int_type, `>', is_greater)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::bool_type)

         METHOD(svm::int_type, `print', print)
         PARAM(`self', svm::int_type)
         RETURNS(svm::object_type)

         METHOD(svm::int_type, `-=', subtract)
         PARAM(`self', svm::int_type)
         PARAM(`i', svm::int_type)
         RETURNS(svm::int_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::int_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::int_type = engine.classes.declare_class("system.Int", svm::object_type);
         SVM_ASSERT_CLASS(svm::int_type);
         SVM_PICK(svm::int_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::int_type);
      }
   };

} }

#endif
