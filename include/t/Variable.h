#ifndef T_VARIABLE
#define T_VARIABLE NS_TYPE::Variable

#include <string>

#include "t/Class.h"
#include "t/Object.h"
#include "t/String.h"
#include "util/Object.h"

namespace t
{
   extern T_OBJECT* tVARIABLE;

   /**
    * A variable is a container for objects of a given type.
    */
   class Variable : public Object
   {
      public: T_OBJECT* object_type;   ///< Class of objects allowed in this variable.
      public: T_OBJECT* object;        ///< Object stored in this variable.
      public: std::string name;        ///< Name of this variable.

      /**
       * Constructor.
       */
      public: Variable();

      /**
       * Destructor.
       */
      public: ~Variable();

      /**
       * Asserts that an object is of type @cls{t::Variable}.
       *
       * @param obj An object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return util::Object::assert_type(obj, NS_TYPE::tVARIABLE);
      }

      /**
       * Creates a t::Variable of type @prm{type}.
       *
       * @param type The type of the value.
       * @return A new @cls{t::Variable}.
       */
      public: static T_OBJECT* build(T_OBJECT* type);

      /**
       * Creates a @cls{t::Variable} of type @prm{type} and name @prm{name}.
       *
       * @param type The type of the value.
       * @param name The name of the variable.
       * @return A new @cls{t::Variable}.
       */
      public: static T_OBJECT* build(T_OBJECT* type, std::string name);

      /**
       * Checks if an object is of type t::tVARIABLE.
       *
       * @param obj An object to check.
       * @return true if @prm{obj} is of type @cls{t::Variable}.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Sets the object of a @cls{t::Variable}.
       *
       * @param variable The variable to set.
       * @param obj The object to assign.
       * @return @prm{obj} unchanged.
       */
      public: static T_OBJECT* set(T_OBJECT* variable, T_OBJECT* obj);

      /**
       * Sets the object type a @cls{t::Variable} can contain.
       *
       * @param type The type of the variable.
       */
      public: void set_object_type(T_OBJECT* type);
   };
}

#endif
