#include "svm/Function.h"

namespace svm
{
   Object* function_type = NULL;
   Object* bad_argument_type_exception_type = NULL;

   Function::Function()
   {
      this->set_class(svm::function_type);
      this->references = 0;
      this->return_type = NULL;
      this->arguments = NULL;
      this->arguments_count = 0;
      this->is_abstract = false;
      this->is_static = true;
      this->is_user = false;
      //this->name = "";
   }

   Function::~Function()
   {
      /*
      SVM_DROP_SAFE(this->return_type);
      for(UInt i = 0 ; i < this->arguments_count ; ++ i)
      {
         SVM_DROP_SAFE(this->arguments[i]);
      }
      SVM_DROP_SAFE(this->return_type);
      delete[] this->arguments;
      */
   }

   #ifdef _DEBUG_
   void
   Function::assert_validity()
   {
      for (unsigned long i = 0; i < this->arguments_count ; ++i)
      {
         SVM_ASSERT_VARIABLE(this->arguments[i]);
         svm::Variable* var = (svm::Variable*)this->arguments[i];
         SVM_PICK(var);

         SVM_DROP(var);
      }
   }
   #endif

   Object*
   Function::cast_to_string(Object* func)
   {
      SVM_ASSERT_FUNCTION(func);
      /*

      Function* f = (Function*)func;
      Object* s = String::build("");
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

      Object* s = String::build("");
      return (Object*)s;
   }

   bool
   Function::check(Object* f)
   {
      return f->cls == svm::function_type;
   }

   void
   Function::print(Object* func)
   {
      Object* s = Function::cast_to_string(func);
      if (s != svm::Null)
      {
         String::print(s);
         SVM_DROP(s);
      }
      else
      {
         Object::print(func);
      }
   }

   void
   Function::set_arguments(int count, Object** args)
   {
      for (UInt i = 0 ; i < this->arguments_count ; ++i)
      {
         SVM_DROP_SAFE(this->arguments[i]);
      }

      this->arguments = args;
      this->arguments_count = count;

      for (int i = 0 ; i < count ; ++i)
      {
         SVM_PICK_SAFE(this->arguments[i]);
      }
   }

   void
   Function::set_arguments(int count, ...)
   {
      for (UInt i = 0 ; i < this->arguments_count ; ++i)
      {
         SVM_DROP_SAFE(this->arguments[i]);
      }

      this->arguments = new Object*[count]; //(Object**)realloc(this->arguments, sizeof(Object*) * count);
      this->arguments_count = count;

      va_list args;
      va_start(args, count);
      for (int i = 0 ; i < count ; ++i)
      {
         this->arguments[i] = va_arg(args, Object*);
         SVM_PICK_SAFE(this->arguments[i]);
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
   Function::set_return_type(Object* type)
   {
      SVM_DROP_SAFE(this->return_type);
      SVM_PICK_SAFE(type);
      this->return_type = type;
   }
}
