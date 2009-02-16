#ifndef MODULES_SYSTEM_MAP_H

include(`../../module.m4')

#define MODULES_SYSTEM_MAP_H
#define MODULE_SYSTEM_MAP

#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/Engine.h"
#include "svm/Map.h"
#include "svm/Object.h"

namespace modules { namespace system {

   class Map
   {
      public: static SVM_METHOD(construct)
      {
         return svm::Map::build();
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::map_type);

         FUNCTION(`system.Map.__construct__', construct)
         RETURNS(svm::map_type)
      }

      public: static void finalize()
      {
         ASSERT_NULL(svm::map_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::object_type);

         svm::map_type = engine.classes.declare_class("system.Map", svm::object_type);
         SVM_ASSERT_CLASS(svm::map_type);
         SVM_PICK(svm::map_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::map_type);
      }
   };

} }

#endif
