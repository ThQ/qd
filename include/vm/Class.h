#ifndef T_CLASS
#define T_CLASS NS_TYPE::Class

#include <string>

#include "t/Object.h"
#include "t/String.h"

namespace t
{
   extern T_OBJECT* tCLASS_NOT_FOUND_EXCEPTION;
   extern T_OBJECT* tBAD_TYPE_EXCEPTION;

   /**
    * A base type for all internal classes.
    */
   class Class : public Object
   {
      public: T_OBJECT* parent_class; ///< A parent class.
      public: std::string name; ///< Name of the class.

      /**
       * Constructor.
       */
      public: Class();

      /**
       * Destructor.
       */
      public: ~Class();

      /**
       * Asserts that an object is of type @cls{t::Class}.
       *
       * @param obj An object to be checked.
       * @return true if @prm{obj} is of type @cls{t::Class}, false otherwise.
       * @todo Make this real !
       */
      public: inline static bool assert(T_OBJECT* obj)
      {
         return true;
      }

      /**
       * Builds an empty @cls{t::Class}.
       *
       * @return An empty @cls{t::Class} object.
       */
      public: static T_OBJECT* build();

      /**
       * Builds a class named @prm{name}.
       *
       * @param name The name of the class to create.
       * @return A @cls{t::Class} named @prm{name}.
       */
      public: static T_OBJECT* build(std::string name);

      /**
       * Builds a class named @prm{name}.
       *
       * @param name The name of the class to create.
       * @return A @cls{t::Class} named @prm{name}.
       */
      public: static T_OBJECT* build(const char* name);

      /**
       * Builds a class named @prm{name}, and whose parent class is @prm{parent_class}.
       *
       * @param name The name of the class to create.
       * @param parent_class The parent class of the class to create.
       * @return A pointer to a @cls{t::Class} newly created.
       */
      public: static T_OBJECT* build(const char* name, T_OBJECT* parent_class);

      /**
       * Builds a class named @prm{name}, and whose parent class is @prm{parent_class}.
       *
       * @param name The name of the class to create.
       * @param parent_class The parent class of the class to create.
       * @return A new @cls{t::Class} named @prm{name}, child of @prm{parent_class}.
       */
      public: static T_OBJECT* build(std::string name, T_OBJECT* parent_class);

      /**
       * Builds a class whose parent class is @prm{parent_class}.
       *
       * @param parent_class The parent class of the class to create.
       * @return a new @cls{t::Class} whose parent is @prm{parent_class}.
       */
      public: static T_OBJECT* build(T_OBJECT* parent_class);

      /**
       * Checks if an object is of type @cls{t::Class}.
       *
       * @param obj An object to be checked.
       * @return true if obj is of type @cls{t::Class}.
       * @todo Make this real !
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return true;
      }

      /**
       * Checks if @prm{cls} is a child of @prm{parent_class}.
       *
       * @param cls The class to be checked.
       * @param parent_class The parent parent class.
       * @return true if @prm{cls} is a child of @prm{parent_class}.
       */
      public: static bool is_child_of(T_OBJECT* cls, T_OBJECT* parent_class);

      /**
       * Sets the parent class.
       *
       * @param parent_class The class to be used as a parent.
       */
      public: void set_parent_class(Class* parent_class);

      /**
       * Sets the parent class.
       *
       * @param parent_class The class to be used as a parent.
       */
      public: void set_parent_class(T_OBJECT* parent_class)
      {
         Class::assert(parent_class);
         this->set_parent_class((Class*)parent_class);
      }
   };
}

#endif
