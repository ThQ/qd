#include "t/Function.h"

namespace t
{
   VM_CLASS__NEW(cFUNCTION, t::Object, t::FUNCTION_TYPE, &cOBJECT);

   Function::Function()
   {
      this->type = t::FUNCTION_TYPE;
      this->klass = &t::cFUNCTION;
      this->return_type = t::UNDEFINED_TYPE;
      this->return_class = NULL;
      this->argument_types = NULL;
      this->argument_count = 0;
      this->is_user = false;
   }

   Function::Function(ushort nReturnType)
   {
      this->argument_types = NULL;
      this->argument_count = 0;
      this->klass = &t::cFUNCTION;
      this->return_type = nReturnType;
      this->return_class = NULL;
      this->type = t::FUNCTION_TYPE;
   }

   Function::Function(ushort nReturnType, vm::Class* pReturnClass)
   {
      this->argument_types = NULL;
      this->argument_count = 0;
      this->klass = &t::cFUNCTION;
      this->return_type = nReturnType;
      this->return_class = pReturnClass;
      this->type = t::FUNCTION_TYPE;
   }

   Function::~Function()
   {
   }

   void
   Function::define_arguments(uchar nCount, uchar* pArgs)
   {
      ASSERT(this->argument_types == NULL, "Arguments have already been set.");

      this->argument_types = pArgs;
      this->argument_count = nCount;
   }

   void
   Function::set_return_type(ushort nType, vm::Class* pClass)
   {
      this->return_type = nType;
      this->return_class = pClass;
   }
}
