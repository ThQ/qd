#ifndef MODULES_SYSTEM_EXCEPTION_H

include(`../../module.m4')

#define MODULES_SYSTEM_EXCEPTION_H
#define MODULE_SYSTEM_EXCEPTION

#include "t/Exception.h"
#include "t/CoreFunction.h"
#include "vm/Engine.h"

namespace modules { namespace system {

   class Exception
   {
      public: static SVM_METHOD(construct)
      {
         ASSERT(argc == 0, "system.Exception.__construct__(). %d parameters given.", argc);
         return t::Exception::build();
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(t::tEXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tRUNTIME_EXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tCLASS_NOT_FOUND_EXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tINDEX_OUT_OF_RANGE_EXCEPTION);

         FUNCTION(`system.Exception.__construct__', construct)
         RETURNS(t::tEXCEPTION)
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::tEXCEPTION);
         ASSERT_NULL(t::tRUNTIME_EXCEPTION);
         ASSERT_NULL(t::tCLASS_NOT_FOUND_EXCEPTION);
         ASSERT_NULL(t::tINDEX_OUT_OF_RANGE_EXCEPTION);
      }

      public: static void initialize(svm::Engine& engine)
      {
         t::tEXCEPTION = engine.classes.declare_class("system.Exception", svm::object_type);
         SVM_ASSERT_NOT_NULL(t::tEXCEPTION);
         t::Object::pick(t::tEXCEPTION);

         t::tRUNTIME_EXCEPTION = engine.classes.declare_class("system.RuntimeException", t::tEXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tRUNTIME_EXCEPTION);
         t::Object::pick(t::tRUNTIME_EXCEPTION);

         t::tCLASS_NOT_FOUND_EXCEPTION = engine.classes.declare_class("system.ClassNotFoundException", t::tEXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tCLASS_NOT_FOUND_EXCEPTION);
         t::Object::pick(t::tCLASS_NOT_FOUND_EXCEPTION);

         t::tINDEX_OUT_OF_RANGE_EXCEPTION = engine.classes.declare_class("system.IndexOutOfRangeException", t::tEXCEPTION);
         SVM_ASSERT_NOT_NULL(t::tINDEX_OUT_OF_RANGE_EXCEPTION);
         t::Object::pick(t::tINDEX_OUT_OF_RANGE_EXCEPTION);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         t::Object::drop(t::tINDEX_OUT_OF_RANGE_EXCEPTION);
         t::Object::drop(t::tRUNTIME_EXCEPTION);
         t::Object::drop(t::tCLASS_NOT_FOUND_EXCEPTION);
         t::Object::drop(t::tEXCEPTION);
      }
   };

} }

#endif
