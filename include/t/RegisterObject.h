#ifndef T__REGISTER_OBJECT_H
#define T__REGISTER_OBJECT_H __FILE__

#include "t/Object.h"

namespace t
{
   extern vm::Class cREGISTER_OBJECT;

   /**
    * @brief A place holder for another value in opcode arguments.
    *
    * @todo Rename to RegisterValue.
    */
   class RegisterObject: public Object
   {
      public: uint   position;      ///< The position of the value in a given register.
      public: uchar  object_type;   ///< The object type (to determine in which register it's stored).

      /**
       * @brief Default constructor.
       */
      public: RegisterObject ();

      /**
       * @brief Constructs a RegisterObject given the type and position of the value to get.
       */
      public: RegisterObject (uchar nType, uint nPosition);
   };
}

#endif
