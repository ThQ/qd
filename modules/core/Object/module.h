#ifndef MODULES_SYSTEM_OBJECT_H
#define MODULES_SYSTEM_OBJECT_H

include(`../../module.m4')

#include "t/Bool.h"
#include "t/CoreFunction.h"
#include "t/Int.h"
#include "vm/Engine.h"

namespace modules { namespace system {

   class Object
   {
      public: static SVM_CLASS_METHOD(compare_to)
      {
         Short s = t::Object::compare_to(argv[0], argv[1]);
         return t::Int::build((Long)s);
      }

      public: static void declare_methods(vm::Engine& engine)
      {
         METHOD(t::tOBJECT, `compare_to', compare_to)
         PARAM(`self', t::tOBJECT)
         PARAM(`another_object', t::tOBJECT)
         RETURNS(t::tINT);
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::tOBJECT);
         ASSERT_NULL(t::tFUNCTION);
         ASSERT_NULL(t::tNULL);
         ASSERT_NULL(t::gNULL);
      }

      public: static void initialize(vm::Engine& engine)
      {
         t::tOBJECT = engine.classes.declare_class("system.Object");
         t::Class::assert(t::tOBJECT);
         t::Object::pick(t::tOBJECT);
         t::tOBJECT->is_abstract = true;

         t::tFUNCTION = engine.classes.declare_class("system.Function");
         t::Class::assert(t::tFUNCTION);
         t::Object::pick(t::tFUNCTION);

         t::tNULL = engine.classes.declare_class("system.Null", t::tOBJECT);
         t::Class::assert(t::tNULL);
         t::Object::pick(t::tNULL);
         t::tNULL->is_abstract = true;

         t::gNULL = new t::Object();
         t::gNULL->set_class(t::tNULL);
         t::Object::pick(t::gNULL);

         t::tHEAP_OBJECT = engine.classes.declare_class("system.HeapObject", t::tOBJECT);
         t::Class::assert(t::tHEAP_OBJECT);
         t::Object::pick(t::tHEAP_OBJECT);
      }

      public: static void tear_down(vm::Engine& engine)
      {
         t::Object::drop(t::tOBJECT);
         t::Object::drop(t::tFUNCTION);
         t::Object::drop(t::tNULL);
         t::Object::drop(t::gNULL);
         t::Object::drop(t::tHEAP_OBJECT);
      }
   };

} }

#endif
