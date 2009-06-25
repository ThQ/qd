#ifndef VM_CLASS_H
#define VM_CLASS_H

#include <string>

#include "types.h"

namespace vm
{
   /**
    * A base type for all internal classes.
    */
   class Class
   {
      public: Class* parent_class;     ///< A parent class.
      public: ushort type;            ///< Type of the object.

      public: bool (*cast_to_string_func)(t::Value pObject);
      public: bool (*destroy_func)(t::Value pObject);
      public: void (*print_func)(t::Value pObject);
      public: void (*print_line_func)(t::Value pObject);

      /**
       * Constructor.
       */
      public: Class();

      /**
       * Constructs a class given its parent class.
       *
       * @param pParentClass The parent class.
       */
      public: Class(vm::Class* pParentClass);

      /**
       * Initializes a class.
       */
      protected: inline void _init()
      {
         this->type = 0;
         this->parent_class = NULL;

         this->cast_to_string_func = NULL;
         this->destroy_func = NULL;
         this->print_func = NULL;
         this->print_line_func = NULL;
      }

      /**
       * Checks if @prm{cls} is a child of @prm{parent_class}.
       *
       * @param cls The class to be checked.
       * @param parent_class The parent parent class.
       * @return true if @prm{cls} is a child of @prm{parent_class}.
       */
      public: bool is_child_of(vm::Class* pParentClass);
   };
}

#endif
