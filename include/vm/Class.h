#ifndef VM_CLASS_H
#define VM_CLASS_H

#include <string>

#include "types.h"

#define VM_CLASS__NEW(class_object_name, c_class, type, parent_class) \
   vm::Class class_object_name(\
         type, \
         parent_class, \
         c_class::destroy, \
         c_class::print, \
         c_class::print_line \
   );
namespace vm
{
   /**
    * @brief A base type for all internal classes.
    */
   class Class
   {
      public: Class* parent_class;     ///< A parent class.
      public: ushort type;            ///< Type of the object.

      public: t::DestroyFunction destroy_func;
      public: t::PrintFunction print_func;
      public: t::PrintLineFunction print_line_func;

      /**
       * @brief Constructor.
       */
      public: Class ();

      /**
       * @brief Constructs a class given its type.
       *
       * @param nType The class type.
       */
      public: Class (uint nType);

      /**
       * @brief Constructs a class given its type and its parent.
       *
       * @param nType The class type.
       */
      public: Class (uint nType, vm::Class* pParentClass);

      /**
       * @brief Constructs a class given its type, its parent ands its base methods.
       *
       * @param nType The class type.
       */
      public: Class (uint nType, vm::Class* pParentClass, t::DestroyFunction, t::PrintFunction, t::PrintLineFunction);

      /**
       * @brief Constructs a class given its parent class.
       *
       * @param pParentClass The parent class.
       */
      public: Class (vm::Class* pParentClass);

      /**
       * @brief Initializes a class.
       */
      protected: inline void _init ()
      {
         this->type = 0;
         this->parent_class = NULL;

         this->destroy_func = NULL;
         this->print_func = NULL;
         this->print_line_func = NULL;
      }

      /**
       * @brief Checks if @prm{cls} is a child of @prm{parent_class}.
       *
       * @param cls The class to be checked.
       * @param parent_class The parent parent class.
       * @return true if @prm{cls} is a child of @prm{parent_class}.
       */
      public: bool is_child_of (vm::Class* pParentClass);
   };
}

#endif
