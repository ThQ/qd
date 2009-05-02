#ifndef MODULES_SYSTEM_MAP_H

include(`../../module.m4')

#define MODULES_SYSTEM_MAP_H
#define MODULE_SYSTEM_MAP

#include "t/Class.h"
#include "t/CoreFunction.h"
#include "t/Map.h"
#include "vm/Engine.h"

namespace modules
{
   namespace system
   {
      class Map
      {
         public: static SVM_METHOD(construct)
         {
            return t::Map::build();
         }

         public: static void declare_methods(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tMAP);

            FUNCTION(`system.Map.__construct__', construct)
            RETURNS(t::tMAP)
         }

         public: static void finalize()
         {
            ASSERT_NULL(t::tMAP);
         }

         public: static void initialize(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tOBJECT);

            t::tMAP = engine.classes.declare_class("system.Map", t::tOBJECT);
            t::Class::assert(t::tMAP);
            t::Object::pick(t::tMAP);
         }

         public: static void tear_down(vm::Engine& engine)
         {
            t::Object::drop(t::tMAP);
         }
      };
   }
}

#endif
