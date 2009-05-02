#ifndef MODULES_SYSTEM_FLOAT_H

include(`../../module.m4')

#define MODULES_SYSTEM_FLOAT_H
#define MODULE_SYSTEM_FLOAT

#include "t/CoreFunction.h"
#include "t/Float.h"
#include "vm/Engine.h"

namespace modules
{
   namespace system
   {
      class Float
      {
         public: static void declare_methods(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tFLOAT);
         }

         public: static void finalize()
         {
            ASSERT_NULL(t::tFLOAT);
         }

         public: static void initialize(vm::Engine& engine)
         {
            t::tFLOAT = engine.classes.declare_class("system.Float", t::tOBJECT);
            t::Class::assert(t::tFLOAT);
            t::Object::pick(t::tFLOAT);
         }

         public: static void tear_down(vm::Engine& engine)
         {
            t::Object::drop(t::tFLOAT);
         }
      };

   }
}

#endif
