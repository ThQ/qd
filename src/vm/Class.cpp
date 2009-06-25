#include "vm/Class.h"

namespace vm
{
   Class::Class()
   {
      this->_init();
      this->parent_class = NULL;
   }

   Class::Class(vm::Class* pParentClass)
   {
      this->_init();
      this->parent_class = pParentClass;
   }

   bool
   Class::is_child_of(vm::Class* pParentClass)
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

