#include "t/Function.h"

namespace t
{
   T_OBJECT* tFUNCTION = NULL;
   T_OBJECT* tBAD_ARGUMENT_TYPE_EXCEPTION = NULL;

   Function::Function()
   {
      this->set_class(NS_TYPE::tFUNCTION);
      this->return_type = NULL;
      this->arguments = NULL;
      this->arguments_count = 0;
      //this->is_abstract = false;
      this->is_static = true;
      this->is_user = false;
   }

   Function::~Function()
   {
      // @TODO: Take care of deallocations
      /*
      T_OBJECT::drop_safe(this->return_type);
      for(UInt i = 0 ; i < this->arguments_count ; ++ i)
      {
         T_OBJECT::drop_safe(this->arguments[i]);
      }
      T_OBJECT::drop_safe(this->return_type);
      delete[] this->arguments;
      */
   }

   #ifdef _DEBUG_
   void
   Function::assert_validity()
   {
      for (ULong i = 0; i < this->arguments_count ; ++i)
      {
         T_VARIABLE::assert(this->arguments[i]);
         T_VARIABLE* var = (T_VARIABLE*)this->arguments[i];
         T_OBJECT::pick(var);

         T_OBJECT::drop(var);
      }
   }
   #endif

   String*
   Function::cast_to_string()
   {
      return new String();
   }

   void
   Function::print()
   {
      String* pFunctionAsStr = this->cast_to_string();
      pFunctionAsStr->print();
      pFunctionAsStr->drop();
   }

   void
   Function::set_arguments(UInt8 count, T_OBJECT** args)
   {
      ASSERT(this->arguments == NULL, "Arguments have already been set.");

      LOOP_FROM_TO(UInt8, i, 0, count)
      {
         ASSERT(this->arguments[i] != NULL, "Can't set arguments when an object is NULL.");
         this->arguments[i]->pick();
      }
   }

   void
   Function::set_arguments(UInt8 count, ...)
   {
      ASSERT(this->arguments == NULL, "Arguments have already been set.");

      this->arguments = new T_OBJECT*[count];
      this->arguments_count = count;

      va_list args;
      va_start(args, count);
      LOOP_FROM_TO(UInt8, i, 0, count)
      {
         this->arguments[i] = va_arg(args, T_OBJECT*);
         ASSERT(this->arguments[i] != NULL, "Can't set arguments when an object is NULL.");
         this->arguments[i]->pick();
      }
      va_end(args);

      #ifdef _DEBUG_
      /*
      for (int i = 0 ; i < this->arguments_count ; ++i)
      {
         Variable* var = (Variable*)this->arguments[i];
         Class* obj_type = (Class*)var->object_type;

         INTERNAL("<");
         String::print_unicode_string(&this->name);
         printf(">.arguments[%d] = Variable*(<name:",  i);
         String::print_unicode_string(&var->name);
         printf(">, <object_type:");
         String::print_unicode_string(&obj_type->name);
         printf(">)\n");
      }
      */
      #endif
   }

   void
   Function::set_return_type(T_OBJECT* type)
   {
      T_OBJECT::drop_safe(this->return_type);
      T_OBJECT::pick_safe(type);
      this->return_type = type;
   }
}
