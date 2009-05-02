#ifndef MODULES_FUNCTION_H

include(`../../module.m4')

#define MODULES_FUNCTION_H


#include "t/Class.h"
#include "t/CoreFunction.h"
#include "vm/Engine.h"

namespace modules { namespace system {

   class Function
   {
      public: static void declare_methods(vm::Engine& engine)
      {
         t::Class::assert(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
      }

      public: static void initialize(vm::Engine& engine)
      {
         t::tBAD_ARGUMENT_TYPE_EXCEPTION = engine.classes.declare_class("system.BadArgumentTypeException", t::tEXCEPTION);
         t::Class::assert(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
         t::Object::pick(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
      }

      public: static void tear_down(vm::Engine& engine)
      {
         t::Object::drop(t::tBAD_ARGUMENT_TYPE_EXCEPTION);
      }
   };

} }

#endif
