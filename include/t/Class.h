#ifndef T_CLASS
#define T_CLASS NS_TYPE::Class

#include <string>

#include "t/Object.h"
#include "t/String.h"

namespace NS_TYPE
{
   extern T_OBJECT* tCLASS_NOT_FOUND_EXCEPTION;
   extern T_OBJECT* tBAD_TYPE_EXCEPTION;

   /**
    * A base type for all internal classes.
    */
   class Class : public T_OBJECT
   {
      public: T_OBJECT* parent_class;
      public: std::string name;

      /**
       * Constructor.
       */
      public: Class();

      /**
       * Destructor.
       */
      public: ~Class();

      /**
       * Asserts that an object is of type t::Class.
       *
       * @param obj An object to be checked.
       * @return true if [obj] is of type [t::Class], false otherwise.
       * @todo Make this real !
       */
      public: inline static bool assert(T_OBJECT* obj)
      {
         return true;
      }

      /**
       * Builds an empty Class.
       *
       * @return An empty t::Class object.
       */
      public: static T_OBJECT* build();

      /**
       * Builds a class named <name>.
       *
       * @param name The name of the class to create.
       * @return A t::Class named [name].
       */
      public: static T_OBJECT* build(std::string name);

      /**
       * Builds a class named <name>.
       *
       * @param name The name of the class to create.
       * @return A t::Class named [name].
       */
      public: static T_OBJECT* build(const char* name);

      /**
       * Builds a class named <name>, and whose parent class is <parent_class>.
       *
       * @param name The name of the class to create.
       * @param parent_class The parent class of the class to create.
       * @return A new t::Class named [name], child of [parent_class].]
       */
      public: static T_OBJECT* build(const char* name, T_OBJECT* parent_class);

      /**
       * Builds a class named <name>, and whose parent class is <parent_class>.
       *
       * @param name The name of the class to create.
       * @param parent_class The parent class of the class to create.
       * @return A new t::Class named [name], child of [parent_class].
       */
      public: static T_OBJECT* build(std::string name, T_OBJECT* parent_class);

      /**
       * Builds a class whose parent class is <parent_class>.
       *
       * @param parent_class The parent class of the class to create.
       * @return a new t::Class whose parent is [parent_class].
       */
      public: static T_OBJECT* build(T_OBJECT* parent_class);

      /**
       * Checks if an object is of type t::Class.
       *
       * @param obj An object to be checked.
       * @return true if obj is of type t::Class.
       * @todo Make this real !
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return true;
      }

      /**
       * Checks if [cls] is a child of [parent_class].
       *
       * @param cls The class to be checked.
       * @param parent_class The parent parent class.
       * @return true if [cls] is a child of [parent_class].
       */
      public: static bool is_child_of(T_OBJECT* cls, T_OBJECT* parent_class);

      /**
       * Sets the parent class.
       *
       * @param parent_class The class to be used as a parent.
       */
      public: void set_parent_class(T_OBJECT* parent_class);
   };
}

#endif
