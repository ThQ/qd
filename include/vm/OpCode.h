#ifndef VM__OPCODE__H
#define VM__OPCODE__H __FILE__


#include <stdarg.h>

#include "t/Object.h"
#include "t/RegisterObject.h"
#include "Memory.h"
#include "types.h"


#define VM__OPCODE__MAX_ARGUMENTS 8
#define VM__OPCODE__GET_ARG(nPos, Type, VarName) Type VarName = (Type)pArguments[nPos];


namespace vm
{
   /**
    * @brief The tinyest executable unit.
    *
    * It is identified by a namespace and a name, and takes arguments.
    */
   class OpCode
   {
      public: uchar        argument_count;            ///< Number of arguments.
      public: uchar*       argument_types;            ///< The type of the arguments.
      protected: t::Value* arguments;                 ///< An array of @cls{t::Value}s.
      public: uchar        method;                    ///< Opcode method.
      public: uchar        ns;                        ///< Opcode namespace.
      public: bool         has_register_arguments;    ///< Whether some arguments must be retrieved from registers.

      /**
       * @brief Default constructor.
       */
      public: OpCode ();

      /**
       * @brief Constructs an opcode given its namespace and method.
       *
       * @param nNamespace Opcode namespace.
       * @param nMethod Opcode method.
       */
      public: OpCode (uchar nNamespace, uchar nMethod);

      /**
       * @brief Destructor.
       */
      public: ~OpCode ();

      public: inline uchar count_arguments ()
      {
         return this->argument_count;
      }

      public: inline t::Value get_argument (uchar nIndex)
      {
         return this->arguments[nIndex];
      }

      public: inline t::Value* get_arguments ()
      {
         return this->arguments;
      }

      /**
       * @brief Sets an argument type and value.
       *
       * @param nIndex Index of the argument to set.
       * @param nType Type of the argument.
       * @param Val Value of the argument.
       * @todo Make some asserts.
       */
      public: void set_argument (uchar nIndex, uchar nType, t::Value Val);

      /**
       * @brief Sizes the argument array.
       *
       * @param nArgumentCount How many arguments.
       */
      public: void size_arguments (uchar nArgumentCount);
   };
}

#endif
