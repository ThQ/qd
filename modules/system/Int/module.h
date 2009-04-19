#ifndef MODULES_INT_H


include(`../../module.m4')

#define MODULES_INT_H

#include <stdio.h>

#include "t/Bool.h"
#include "t/Class.h"
#include "t/CoreFunction.h"
#include "t/Int.h"
#include "t/String.h"
#include "t/Variable.h"
#include "vm/Engine.h"

namespace modules { namespace system {

   class Int
   {
      public: static SVM_CLASS_METHOD(add)
      {
         t::Int::add_to(argv[0], argv[1]);
         return argv[0];
      }

      public: static SVM_CLASS_METHOD(compare_to)
      {
         Short i = t::Int::compare_to(argv[0], argv[1]);
         return t::Int::build((Long)i);
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
         t::Int::assert(argv[0]);
         t::Int::assert(argv[1]);

         t::Object* result;

         bool equals = ((t::Int*)argv[0])->value == ((t::Int*)argv[1])->value;
         return equals ? t::gTRUE : t::gFALSE;
      }


      public: static SVM_CLASS_METHOD(is_greater)
      {
         t::Int::assert(argv[0]);
         t::Int::assert(argv[1]);

         t::Object* result;

         if (((t::Int*)argv[0])->value > ((t::Int*)argv[1])->value)
         {
            result = (t::Object*)t::gTRUE;
         }
         else
         {
            result = (t::Object*)t::gFALSE;
         }
         return result;

      }

      public: static SVM_CLASS_METHOD(is_greater_or_equal)
      {
         ASSERT(argc == 2, "Bad argument count.");
         t::Int::assert(argv[0]);
         t::Int::assert(argv[1]);

         t::Object* result;

         if (((t::Int*)argv[0])->value >= ((t::Int*)argv[1])->value)
         {
            result = (t::Object*)t::gTRUE;
         }
         else
         {
            result = (t::Object*)t::gFALSE;
         }
         return result;

      }

      public: static SVM_CLASS_METHOD(multiply)
      {
         t::Int::multiply_to(argv[0], argv[1]);

         return argv[0];
      }

      public: static SVM_CLASS_METHOD(print)
      {
         ASSERT(argc == 1, "Bad argument count.");
         t::Int::assert(argv[0]);

         t::Int::print(argv[0]);

         return t::gNULL;
      }

      public: static SVM_CLASS_METHOD(subtract)
      {
         ASSERT(argc == 2, "-=(system.Int, system.Int). %d parameters given.", argc);
         t::Int::assert(argv[0]);
         t::Int::assert(argv[1]);

         t::Int::subtract_to(argv[0], argv[1]);

         return argv[0];
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(t::tINT);

         METHOD(t::tINT, `*=', multiply)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tINT)

         METHOD(t::tINT, `+=', add)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tINT)

         METHOD(t::tINT, `compare_to', compare_to)
         PARAM(`self', t::tINT)
         PARAM(`another_int', t::tINT)
         RETURNS(t::tINT)

         METHOD(t::tINT, `equals', equals)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tBOOL)

         METHOD(t::tINT, `>=', is_greater_or_equal)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tBOOL)

         METHOD(t::tINT, `>', is_greater)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tBOOL)

         METHOD(t::tINT, `print', print)
         PARAM(`self', t::tINT)
         RETURNS(t::tOBJECT)

         METHOD(t::tINT, `-=', subtract)
         PARAM(`self', t::tINT)
         PARAM(`i', t::tINT)
         RETURNS(t::tINT)
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::tINT);
      }

      public: static void initialize(svm::Engine& engine)
      {
         t::tINT = engine.classes.declare_class("system.Int", t::tOBJECT);
         t::Class::assert(t::tINT);
         t::Object::pick(t::tINT);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         t::Object::drop(t::tINT);
      }
   };

} }

#endif
