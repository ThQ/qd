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

   T_OBJECT*
   Function::cast_to_string(T_OBJECT* func)
   {
      Function::assert(func);
      /*

      Function* f = (Function*)func;
      T_OBJECT* s = String::build("");
      String::append(s, f->name);
      String::append(s, "(");

      for (UInt i = 0 ; i < f->arguments_count ; ++ i)
      {
         Variable* var = (Variable*)f->arguments[i];
         Class* cls = (Class*)var->object_type;
         if(i > 0)
         {
            String::append(s, ", ");
         }
         String::append(s, cls->name);
         String::append(s, " ");
         String::append(s, var->name);
      }

      String::append(s, ") : ");
      String::append(s, ((Class*)f->return_type)->name);
      */

      T_OBJECT* s = T_STRING::build("");
      return (T_OBJECT*)s;
   }

   void
   Function::print(T_OBJECT* func)
   {
      T_OBJECT* s = Function::cast_to_string(func);
      if (s != NS_TYPE::gNULL)
      {
         T_STRING::print(s);
         T_OBJECT::drop(s);
      }
      else
      {
         T_OBJECT::print(func);
      }
   }

   void
   Function::set_arguments(UInt count, T_OBJECT** args)
   {
      for (UInt i = 0 ; i < this->arguments_count ; ++i)
      {
         T_OBJECT::drop_safe(this->arguments[i]);
      }

      this->arguments = args;
      this->arguments_count = count;

      for (UInt i = 0 ; i < count ; ++i)
      {
         T_OBJECT::pick_safe(this->arguments[i]);
      }
   }

   void
   Function::set_arguments(UInt count, ...)
   {
      for (UInt i = 0 ; i < this->arguments_count ; ++i)
      {
         T_OBJECT::drop_safe(this->arguments[i]);
      }

      this->arguments = new T_OBJECT*[count];
      this->arguments_count = count;

      va_list args;
      va_start(args, count);
      for (UInt i = 0 ; i < count ; ++i)
      {
         this->arguments[i] = va_arg(args, T_OBJECT*);
         T_OBJECT::pick_safe(this->arguments[i]);
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
