#ifndef MODULES_SYSTEM_ARRAY_H
#define MODULES_SYSTEM_ARRAY_H

#include "t/Array.h"

namespace modules { namespace system
{
   class Array
   {
      public: static void declare_methods(t::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(t::tARRAY);
      }

      public: static void finalize()
      {
         ASSERT_NULL(t::tARRAY);
      }

      public: static void initialize(svm::Engine& engine)
      {
         t::tARRAY = engine.classes.declare_class("system.Array", t::tOBJECT);
         t::Class::assert(t::tARRAY);
         t::Object::pick(t::tARRAY);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         t::Object::drop(t::tARRAY);
      }
   };
} }

#endif
