#ifndef VM__CLASS__H
#define VM__CLASS__H __FILE__

#include <string>

#include "types.h"

#define VM_CLASS__NEW(class_object_name, c_class, type, parent_class) \
   vm::Class class_object_name(\
         type, \
         parent_class, \
         c_class::__new__ ,\
         c_class::__delete__ ,\
         c_class::__print__, \
         c_class::__print_line__ \
   );
namespace vm
{
   /**
    * @brief A base class for all internal classes.
    */
   class Class
   {
      public: Class* parent_class;                    ///< A parent class.
      public: ushort type;                            ///< Type of the object.

      public: t::InitializeFunction initialize_func;  ///< A functor to a function used to create an object of that class.
      public: t::DestroyFunction destroy_func;        ///< A functor to a function used to destroy an object of that class.
      public: t::PrintFunction print_func;            ///< A functor to a function used to print an object of that class.
      public: t::PrintLineFunction print_line_func;   ///< A functor to a function used to print on a new line an object of that class.

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
       * @param pParentClass A pointer to the parent class.
       */
      public: Class (uint nType, vm::Class* pParentClass);

      /**
       * @brief Constructs a class given its type, its parent ands its base methods.
       *
       * @param nType The class type.
       * @param pParentClass A pointer to the parent class.
       * @param fpInit A functor to a function used to initialize an object of that class.
       * @param fpDestroy A functor to a function used to destroy an object of that class.
       * @param fpPrint A functor to a function used to print an object of that class.
       * @param fpPrintLine A functor to a function used to print on a new line an object of that class.
       */
      public: Class (uint nType, vm::Class* pParentClass, t::InitializeFunction fpInit, t::DestroyFunction fpDestroy, t::PrintFunction fpPrint, t::PrintLineFunction fpPrintLine);

      /**
       * @brief Constructs a class given its parent class.
       *
       * @param pParentClass The parent class.
       */
      public: Class (vm::Class* pParentClass);

      /**
       * @brief Destructor.
       */
      public: ~Class ();

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
       * @param pParentClass The parent parent class.
       * @return true if @prm{cls} is a child of @prm{parent_class}.
       */
      public: bool is_child_of (vm::Class* pParentClass);
   };
}

#endif
