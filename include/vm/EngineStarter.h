#ifndef SVM_ENGINE_STARTER_H
#define SVM_ENGINE_STARTER_H

#include "svm/Engine.h"
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
