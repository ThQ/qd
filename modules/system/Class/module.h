#ifndef MODULES_SYSTEM_CLASS_H
#define MODULES_SYSTEM_CLASS_H

#include "t/Class.h"

namespace modules
{
   namespace system
   {
      class Class
      {
         public: static void declare_methods(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tBAD_TYPE_EXCEPTION);
         }

         public: static void finalize()
         {
            ASSERT_NULL(t::tBAD_TYPE_EXCEPTION);
         }

         public: static void initialize(vm::Engine& engine)
         {
            t::tBAD_TYPE_EXCEPTION = engine.classes.declare_class("system.BadTypeException", t::tOBJECT);
            t::Class::assert(t::tBAD_TYPE_EXCEPTION);
            t::Object::pick(t::tBAD_TYPE_EXCEPTION);
         }

         public: static void tear_down(vm::Engine& engine)
         {
            t::Object::drop(t::tBAD_TYPE_EXCEPTION);
         }
      };
   }
}

#endif
