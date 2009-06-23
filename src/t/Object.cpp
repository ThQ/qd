#include "t/Object.h"

namespace t
{
   //Object* tOBJECT = NULL;
   //Object* tNULL = NULL;
   Object* gNULL = NULL;

   Object::Object()
   {
      this->fpPrint = t::Object::print;
      this->fpPrintLine = t::Object::print_line;
      this->fpDestroy = NULL;

      this->type = t::UNDEFINED_TYPE;
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
      Object** array = (Object**) Memory::malloc(sizeof(Object**) * argc);
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

   bool
   Object::drop(Object* o)
   {
      ASSERT_NOT_NULL(o);
      ASSERT_NOT_NULL(o->fpDestroy);

      #ifdef _SHOW_GC_
      INTERNAL("<%s @%x> DEC_REF_COUNT (.from %ld, .to %ld)\n", t::cast_type_to_string(o->type), (uint)o, o->references, o->references - 1);
      #endif

      -- o->references;

      #ifdef _DEBUG_
      if (o->references < 0)
      {
         WARNING("<%s @%x> NEGATIVE_REFERENCE_COUNT\n", t::cast_type_to_string(o->type), (uint)o);
      }
      #endif

      if (o->references == 0)
      {
         o->fpDestroy(o);
         DELETE(o);
      }

      ++ Stats.dwDrops;
      -- Stats.dwReferences;

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
      ASSERT_NOT_NULL(o);

      #ifdef _SHOW_GC_
      INTERNAL(
            "<%s @%x> INCR_REF_COUNT (.from %ld, .to %ld)\n",
            t::cast_type_to_string(o->type),
            (uint)o, o->references,
            o->references + 1
      );
      #endif

      #ifdef _SHOW_GC_
      if (o->references < 0)
      {
         WARNING(
               "<%s @%x)> NEGATIVE_REFERENCE_COUNT\n",
               t::cast_type_to_string(o->type),
               (uint)o
         );
      }
      #endif
      ++ o->references;

      ++ Stats.dwPicks;
      ++ Stats.dwReferences;

      return true;
   }

   void
   Object::print(Object* o)
   {
      printf("<%s @%x>", t::cast_type_to_string(o->type), (uint)o);
   }

   void
   Object::print_line(Object* o)
   {
      printf("<%s @%x>\n", t::cast_type_to_string(o->type), (uint)o);
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
      ASSERT_NOT_NULL(type);

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
