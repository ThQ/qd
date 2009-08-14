#include "vm/OpCode.h"

namespace vm
{
   OpCode::OpCode ()
   {
      this->argument_count = 0;
      this->argument_types = NULL;
      this->arguments = NULL;
      this->has_register_arguments = false;
      this->method = 0;
      this->ns = 0;
   }

   OpCode::OpCode (uchar nNamespace, uchar nMethod)
   {
      this->argument_count = 0;
      this->argument_types = NULL;
      this->arguments = NULL;
      this->has_register_arguments = false;
      this->method = nMethod;
      this->ns = nNamespace;
   }

   OpCode::~OpCode ()
   {
      if (this->arguments != NULL)
      {
         for (uint i = 0 ; i < this->argument_count ; ++i)
         {
            if (T__IS_OBJECT_TYPE(this->argument_types[i]))
            {
               ((t::Object*)this->arguments[i])->drop();
            }
         }
         Memory_FREE(this->argument_types);
         Memory_FREE(this->arguments);
      }
   }

   void
   OpCode::set_argument (uchar nIndex, uchar nType, t::Value Val)
   {
      if (T__IS_OBJECT_TYPE(nType))
      {
         ((t::Object*)Val)->pick();
         if (nType == t::REGISTER_VALUE_TYPE)
         {
            this->has_register_arguments = true;
         }
      }
      this->argument_types[nIndex] = nType;
      this->arguments[nIndex] = Val;
   }

   void
   OpCode::size_arguments (uchar nArgumentCount)
   {
      Memory_ALLOC(this->arguments, t::Value, nArgumentCount);
      Memory_ALLOC(this->argument_types, uchar, nArgumentCount);
      this->argument_count = nArgumentCount;
      for (uint i = 0 ; i < nArgumentCount ; ++i)
      {
         this->arguments[i] = NULL;
         this->argument_types[i] = 0;
      }
   }
}
