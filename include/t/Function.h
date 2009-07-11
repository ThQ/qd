#ifndef T_FUNCTION
#define T_FUNCTION t::Function

#define SVM_FUNCTION_NAME_LENGTH 256

#include <stdarg.h>
#include <string.h>

#include "t/Class.h"
#include "t/Exception.h"
#include "t/String.h"
#include "t/Variable.h"

namespace t
{
   extern T_OBJECT* tFUNCTION;
   extern T_OBJECT* tBAD_ARGUMENT_TYPE_EXCEPTION;

   /**
    * @brief An internal function.
    */
   class Function : public Object
   {
      public: T_OBJECT* return_type;   ///< A pointer to a @cls{t::Class} representing the type of the returned object.
      public: T_OBJECT** arguments;    ///< An array of @cls{{t::Variable}} representing the parameters.
      public: UInt arguments_count;    ///< Number of arguments.
      public: bool is_static;          ///< Is a static function ?
      public: bool is_user;            ///< Is user created ?

      /**
       * @brief Default constructor.
       */
      public: Function();

      /**
       * @brief Destructor.
       */
      public: ~Function();

      /**
       * @brief Asserts that an object is of type t::tFUNCTION.
       *
       * @param obj An object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return T_OBJECT::assert_type(obj, NS_TYPE::tFUNCTION);
      }

      #ifdef _DEBUG_
      /**
       * @brief Asserts the validity.
       */
      public: void assert_validity();
      #endif

      /**
       * @brief Builds a string from a function @prm{func}.
       */
      public: String* cast_to_string();

      /**
       * @brief Checks if an object is of type @cls{t::Function}.
       *
       * @param obj An object to check.
       * @return true if @prm{obj} is of type @cls{t::Function}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tFUNCTION);
      }

      /**
       * @brief Builds a string from a function @prm{func} and prints it to the console.
       */
      public: void print();

      /**
       * @brief Sets the arguments.
       *
       * @param count How many arguments are passed.
       */
      public: void set_arguments(UInt8 count, ...);

      /**
       * @brief Sets the arguments.
       *
       * @param count How many arguments are passed.
       * @param args Arguments to set.
       */
      public: void set_arguments(UInt8 count, T_OBJECT** args);

      /**
       * @brief Sets the return type to @prm{type}.
       *
       * @param type Return type.
       */
      public: void set_return_type(T_OBJECT* type);
   };
}
#endif
