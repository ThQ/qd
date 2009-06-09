#include "t/Object.h"

namespace t
{
   Object* tOBJECT = NULL;
   Object* tNULL = NULL;
   Object* gNULL = NULL;

   Object::Object()
   {
      this->cls = NULL;
      //this->is_abstract = false;
      this->references = 0;
      this->fields = 0;
      this->field_count = 0;
      this->field_rooms = 0;
   }

   Object**
   Object::build_array(int argc, ...)
   {
      va_list argv;
      va_start(argv, argc);
      Object** array = (Object**)MALLOC(sizeof(Object**) * argc);
      for (int i = 0 ; i < argc ; ++i)
      {
         array[i] = va_arg(argv, Object*);
      }
      return array;
   }

   Short
   Object::compare_to(Object* o1, Object* o2)
   {
      if (o1 == o2)
      {
         return 0;
      }
      else if ((ULong)o1 < (ULong)o2)
      {
         return -1;
      }
      else
      {
         return 1;
      }
   }

   /*
    * Decreases the reference count of a t::Object*.
    */
   bool
   Object::drop(Object* o)
   {
      Object::assert_not_null(o);
      --o->references;

      #ifdef _SHOW_GC_
      if (o == NS_TYPE::tOBJECT)
      {
         printf(" [svm::object_type@%lu] ", (ULong)NS_TYPE::tOBECT);
      }
      #endif

      #ifdef _DEBUG_
      if (o->references < 0)
      {
         WARNING("Object::drop | <svm::Object(@%lu)> has a negative reference count.\n", (ULong)o);
      }
      #endif

      if (o->references <= 0)
      {
         DELETE(o);
         #ifdef _SHOW_GC_
         printf(" (to death MOUHAHAHA)");
         #endif
      }

      return true;
   }

   Object*
   Object::get_field(ULong at)
   {
      ASSERT(
            at < this->field_count,
            "Cannot get field at %lu, Object @%lu only has %lu fields.\n",
            at,
            (ULong)this,
            this->field_count
      );
      Object* result = this->fields[at];
      #ifdef _DEBUG_
      if (result == NULL)
      {
         FATAL("Field at %lu for Object @%lu is C's NULL.", at, (ULong)this);
         abort();
      }
      #endif
      return result;
   }

   bool
   Object::pick(Object* o)
   {
      Object::assert_not_null(o);

      #ifdef _SHOW_GC_
      if (o == NS_TYPE::tOBJECT)
      {
         printf(" [svm::object_type@%lu] ", (ULong)NS_TYPE::tOBJECT);
      }
      if (o->references < 0)
      {
         WARNING(
               "<svm::Object(@%lu)> has a negative reference count.\n",
               (ULong)o
         );
      }
      #endif
      ++ o->references;

      return true;
   }

   void
   Object::print(Object* o)
   {
      printf("<system.Object:%lu>", (ULong)o);
   }

   void
   Object::print_line(Object* o)
   {
      printf("<system.Object:%lu>\n", (ULong)o);
   }

   void
   Object::resize_field_array(ULong new_size)
   {
      if (new_size > this->field_rooms)
      {
         // TODO : this->field_count = 0 at the beginning
         this->fields = (Object**)REALLOC(this->fields, sizeof(Object*) * new_size);

         // So as to avoid SVM_DROP to work
         for (ULong i = this->field_rooms ; i < new_size ; ++i)
         {
            this->fields[i] = NULL;
         }
         this->field_count = new_size;
         this->field_rooms = new_size;
         ASSERT_REALLOC(this->fields);
      }
      else if(new_size < this->field_count)
      {
         for (ULong i = new_size ; i < this->field_count ; ++i)
         {
            Object::drop_safe(this->fields[i]);
         }
         // @TODO : this->field_count = 0 at the beginning
         this->field_count = new_size;
         this->field_rooms = new_size;
         this->fields = (Object**)REALLOC(this->fields, sizeof(Object*) * new_size);
         ASSERT_REALLOC(this->fields);
      }
   }

   void
   Object::resize_fields_up()
   {
      ++ this->field_rooms += SVM_OBJECT_FIELDS_STEP;
      this->fields = (Object**)REALLOC(this->fields, sizeof(Object*) * this->field_rooms);
   }

   void
   Object::set_class(Object* type)
   {
      T_OBJECT::assert_not_null(type);

      Object::drop_safe(this->cls);
      this->cls = type;
      Object::pick_safe(type);
   }

   void
   Object::set_field(ULong at, Object* obj)
   {
      ASSERT(
         at < this->field_count,
         "Object::set_field(ULong, Object*) : Field at %lu should be accessible.\n",
         at
      );
      Object::drop_safe(this->fields[at]);
      this->fields[at] = obj;
      Object::pick_safe(obj);
   }

}
