#ifndef T_VARIABLE
#define T_VARIABLE NS_TYPE::Variable

#include <string>

#include "t/Class.h"
#include "t/Object.h"
#include "t/String.h"
#include "util/Object.h"

namespace NS_TYPE
{
   extern T_OBJECT* tVARIABLE;

   /**
    * A variable is a container for objects of a given type.
    */
   class Variable : public T_OBJECT
   {
      public: T_OBJECT* object_type;
      public: T_OBJECT* object;
      public: std::string name;

      /**
       * Constructor.
       */
      public: Variable();

      /**
       * Destructor.
       */
      public: ~Variable();

      /**
       * Asserts that an object is of type [t::Variable].
       *
       * @param obj An object to check.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         return util::Object::assert_type(obj, NS_TYPE::tVARIABLE);
      }

      /**
       * Creates a t::Variable of type [type].
       *
       * @param type The type of the value.
       * @return A new t::Variable.
       */
      public: static T_OBJECT* build(T_OBJECT* type);

      /**
       * Creates a t::Variable of type [type] and name [name].
       *
       * @param type The type of the value.
       * @param name The name of the variable.
       * @return A new t::Variable.
       */
      public: static T_OBJECT* build(T_OBJECT* type, std::string name);

      /*
       * Checks if an object is of type t::tVARIABLE.
       *
       * @param obj An object to check.
       * @return true if [obj] is of type [t::Variable].
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tBOOL);
      }

      /**
       * Sets the object of a t::Variable.
       *
       * @param variable The variable to set.
       * @param obj The object to assign.
       * @return [obj] unchanged.
       */
      public: static T_OBJECT* set(T_OBJECT* variable, T_OBJECT* obj);

      /**
       * Sets the object type a t::Variable can contain.
       *
       * @param type The type of the variable.
       */
      public: void set_object_type(T_OBJECT* type);
   };
}

#endif
