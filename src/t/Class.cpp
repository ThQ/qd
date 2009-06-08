#include "t/Class.h"

namespace NS_TYPE
{
   T_OBJECT* tCLASS_NOT_FOUND_EXCEPTION = NULL;
   T_OBJECT* tBAD_TYPE_EXCEPTION = NULL;

   Class::Class()
   {
      this->parent_class = NULL;
      this->name = "";
   }

   Class::~Class()
   {
      T_OBJECT::drop_safe(this->parent_class);
   }

   T_OBJECT*
   Class::build()
   {
      return (T_OBJECT*) new Class();
   }

   T_OBJECT*
   Class::build(std::string name)
   {
      Class* c = new Class();
      c->name = name;
      return (T_OBJECT*)c;
   }

   T_OBJECT*
   Class::build(T_OBJECT* parent_class)
   {
      Class::assert(parent_class);

      Class* c = new Class();
      c->set_parent_class(parent_class);
      return (T_OBJECT*)c;
   }

   T_OBJECT*
   Class::build(const char* name)
   {
      Class* c = new Class();
      c->name.assign(name);
      return (T_OBJECT*)c;
   }

   T_OBJECT*
   Class::build(const char* name, T_OBJECT* parent_class)
   {
      Class::assert(parent_class);

      Class* c = new Class();
      c->name.assign(name);
      c->set_parent_class(parent_class);
      return (T_OBJECT*)c;
   }

   T_OBJECT*
   Class::build(std::string name, T_OBJECT* parent_class)
   {
      Class::assert(parent_class);

      Class* c = new Class();
      c->name = name;
      c->set_parent_class(parent_class);
      return (T_OBJECT*)c;
   }

   bool
   Class::is_child_of(T_OBJECT* cls, T_OBJECT* parent_class)
   {
      Class::assert(cls);
      Class::assert(parent_class);

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
            else if(((Class*)cls)->parent_class == NULL)
            {
               break;
            }
            T_OBJECT::drop_safe(cls);
            cls = ((Class*)cls)->parent_class;
            T_OBJECT::pick(cls);
         }
         T_OBJECT::drop(cls);
      }

      return result;
   }

   void
   Class::set_parent_class(Class* parent_class)
   {
      T_OBJECT::drop_safe(this->parent_class);
      T_OBJECT::pick(parent_class);
      this->parent_class = (T_OBJECT*)parent_class;
   }
}

