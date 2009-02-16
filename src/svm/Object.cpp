#include "svm/Object.h"

namespace svm
{
   Object* object_type = NULL;
   Object* null_type = NULL;
   Object* Null = NULL;

   Object::Object()
   {
      this->cls = NULL;
      this->is_abstract = false;
      this->references = 0;
      this->fields = 0;
      this->field_count = 0;
      this->field_rooms = 0;

      //WARNING("Stupid\n");
      //this->resize_field_array(10);
   }

   /*
    * Creates an svm::Object*[argc] filled with arguments.
    */
   Object**
   Object::build_array(int argc, ...)
   {
      va_list argv;
      va_start(argv, argc);
      Object** array = (Object**)malloc(sizeof(Object**) * argc);
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
    * Decreases the reference count of an svm::Object*.
    */
   bool
   Object::drop(Object* o)
   {
      ASSERT_NOT_NULL(o);
      --o->references;

      #ifdef _SHOW_GC_
      if (o == svm::object_type)
      {
         printf(" [svm::object_type@%lu] ", (long unsigned)svm::object_type);
      }
      if (o->references < 0)
      {
         WARNING("<svm::Object(@%lu)> has a negative reference count.\n", (long unsigned)o);
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
      ASSERT(at < this->field_count, "The field @%lu should be accessible.\n", at);
      Object* result = this->fields[at];
      if (result == NULL)
      {
         result = svm::Null;
      }
      return result;
   }

   /*
    * Increases the reference count of an svm::Object*.
    */
   bool
   Object::pick(Object* o)
   {
      ASSERT_NOT_NULL(o);

      #ifdef _SHOW_GC_
      if (o == svm::object_type)
      {
         printf(" [svm::object_type@%lu] ", (long unsigned)svm::object_type);
      }
      if (o->references < 0)
      {
         WARNING("<svm::Object(@%lu)> has a negative reference count.\n", (long unsigned)o);
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
            SVM_DROP_SAFE(this->fields[i]);
         }
         // TODO : this->field_count = 0 at the beginning
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

   /*
    * Sets an object class.
    */
   void
   Object::set_class(Object* type)
   {
      SVM_PICK_SAFE(type);
      SVM_DROP_SAFE(this->cls);
      this->cls = type;
   }

   void
   Object::set_field(ULong at, Object* obj)
   {
      ASSERT(at < this->field_count, "svm::Object::set_field(ULong, Object*) : Field at %lu should be accessible.\n", at);
      SVM_DROP_SAFE(this->fields[at]);
      this->fields[at] = obj;
      SVM_PICK_SAFE(obj);
   }

}
