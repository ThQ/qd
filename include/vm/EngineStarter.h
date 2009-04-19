#ifndef VM_ENGINE_STARTER_H
#define VM_ENGINE_STARTER_H

#include "vm/Engine.h"
// @MODULES[INCLUDE]

namespace svm
{
   class EngineStarter
   {
      public: Engine engine;

      public: void setup();
      public: void tear_down();
   };
}

#endif
