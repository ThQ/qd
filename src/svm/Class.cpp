#include "svm/Class.h"

namespace svm
{
   Object* class_not_found_exception_type = NULL;
   Object* bad_type_exception_type = NULL;

   Class::Class()
   {
      this->references = 0;
      this->parent_class = NULL;
   }

   Class::~Class()
   {
      INTERNAL("------------ ~Class()\n");
      SVM_DROP_SAFE(this->parent_class);
   }

   Object*
   Class::build()
   {
      return (Object*) new Class();
   }

   Object*
   Class::build(std::string name)
   {
      Class* c = new Class();
      c->name = name;
      return (Object*)c;
   }

   Object*
   Class::build(Object* parent_class)
   {
      SVM_ASSERT_CLASS(parent_class);

      Class* c = new Class();
      c->set_parent_class(parent_class);
      return (Object*)c;
   }

   Object*
   Class::build(const char* name)
   {
      Class* c = new Class();
      c->name.assign(name);
      return (Object*)c;
   }

   Object*
   Class::build(const char* name, Object* parent_class)
   {
      SVM_ASSERT_CLASS(parent_class);

      Class* c = new Class();
      c->name.assign(name);
      c->set_parent_class(parent_class);
      return (Object*)c;
   }

   Object*
   Class::build(std::string name, Object* parent_class)
   {
      SVM_ASSERT_CLASS(parent_class);

      Class* c = new Class();
      c->name = name;
      c->set_parent_class(parent_class);
      return (Object*)c;
   }

   bool
   Class::check(Object* obj)
   {
      //WARNING("bool Class::check(Object*) : Not implemented yet.\n");
      //return true; //obj->cls == svm::class_type;
      // TODO: How ?
      return true; //obj->cls == NULL;
   }

   bool
   Class::is_child_of(Object* cls, Object* parent_class)
   {
      SVM_ASSERT_CLASS(cls);
      SVM_ASSERT_CLASS(parent_class);

      bool result = false;
      if (cls == parent_class)
      {
         result = true;
      }
      else
      {
         while (cls != NULL)
         {
            if (cls == parent_class)
            {
               result = true;
               break;
            }
            else if(((svm::Class*)cls)->parent_class == NULL)
            {
               break;
            }
            SVM_DROP(cls);
            cls = ((svm::Class*)cls)->parent_class;
         }
         SVM_DROP(cls);
      }

      return result;
   }

   void
   Class::set_parent_class(Object* parent_class)
   {
      SVM_ASSERT_CLASS(parent_class);

      SVM_DROP_SAFE(this->parent_class);
      this->parent_class = parent_class;
      SVM_PICK(parent_class);
   }
}

