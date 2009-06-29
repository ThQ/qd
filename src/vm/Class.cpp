#include "vm/Class.h"

namespace vm
{
   Class::Class ()
   {
      this->_init();
      this->parent_class = NULL;
   }

   Class::Class (uint nType)
   {
      this->_init();
      this->type = nType;
   }

   Class::Class (uint nType, vm::Class* pParentClass)
   {
      this->_init();
      this->type = nType;
      this->parent_class = pParentClass;
   }

   Class::Class (
         uint nType,
         vm::Class* pParentClass,
         t::DestroyFunction destroy_func,
         t::PrintFunction print_func,
         t::PrintLineFunction print_line_func
   )
   {
      this->_init();
      this->type = nType;
      this->parent_class = pParentClass;
      this->destroy_func = destroy_func;
      this->print_func = print_func;
      this->print_line_func = print_line_func;
   }

   Class::Class (vm::Class* pParentClass)
   {
      this->_init();
      this->parent_class = pParentClass;
   }

   bool
   Class::is_child_of (vm::Class* pParentClass)
   {
      ASSERT_NOT_NULL(pParentClass);

      bool bResult = false;
      if (this == pParentClass)
      {
         bResult = true;
      }
      else
      {
         while (pParentClass != NULL)
         {
            if (this == pParentClass)
            {
               bResult = true;
               break;
            }
            pParentClass = pParentClass->parent_class;
         }
      }

      return bResult;
   }
}

