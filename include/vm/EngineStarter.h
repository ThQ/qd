#ifndef VM__ENGINE_STARTER__H
#define VM__ENGINE_STARTER__H

#include "vm/Engine.h"
// @MODULES[INCLUDE]

namespace vm
{
   /**
    * @brief An engine starter.
    */
   class EngineStarter
   {
      public: Engine engine; ///< An engine to start.

      /**
       * @brief Sets the engine up.
       */
      public: void setup();

      /**
       * @brief Tears the engine down.
       */
      public: void tear_down();
   };
}

#endif
