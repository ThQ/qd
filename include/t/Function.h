#ifndef T__FUNCTION__H
#define T__FUNCTION__H __FILE__

#include <stdarg.h>

#include "t/Exception.h"
#include "t/String.h"
#include "vm/Class.h"

namespace t
{
   extern vm::Class cFUNCTION;

   /**
    * @brief An internal function.
    */
   class Function : public Object
   {
      public: uchar*       argument_types;      ///< An array of types representing the parameters.
      public: uchar        argument_count;      ///< Number of arguments.
      public: bool         is_user;             ///< Is user created ?
      public: vm::Class*   return_class;        ///< A pointer to a @cls{vm::Class} representing the class of the returned object.
      public: ushort       return_type;         ///< The type of the return object.

      /**
       * @brief Default constructor.
       */
      public: Function ();

      /**
       * @brief Constructs a function with its return type.
       *
       * @param nReturnType Function return type.
       */
      public: Function (ushort nReturnType);

      /**
       * @brief Constructs a function with its return type and class.
       *
       * @param nReturnType Function return type.
       * @param pReturnClass Function return class.
       */
      public: Function (ushort nReturnType, vm::Class* pReturnClass);

      /**
       * @brief Destructor.
       */
      public: ~Function ();

      /**
       * @brief Asserts that an object a function.
       *
       * @param pObject An object to check.
       */
      public: inline static void assert (Object* pObject)
      {
         return pObject->assert_type(t::FUNCTION_TYPE);
      }

      /**
       * @brief Checks if an object is a function.
       *
       * @param pObject An object to check.
       * @return true if it's a function.
       */
      public: inline static bool check (Object* pObject)
      {
         return pObject->check_type(t::FUNCTION_TYPE);
      }

      /**
       * @brief Sets the arguments.
       *
       * @param nCount How many arguments are passed.
       * @param pArgs Arguments to set.
       */
      public: void define_arguments (uchar nCount, uchar* pArgs);

      /**
       * @brief Sets the return type.
       *
       * @param nType Return type.
       */
      public: inline void set_return_type (ushort nType)
      {
         this->set_return_type(nType, NULL);
      }

      /**
       * @brief Sets the return type.
       *
       * @param nType Return type.
       * @param pClass Return class.
       */
      public: void set_return_type (ushort nType, vm::Class* pClass);
   };
}
#endif
