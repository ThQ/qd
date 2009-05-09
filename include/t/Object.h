#ifndef T_OBJECT_H
#define T_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "config.h"
#include "debug.h"
#include "memory.h"
#include "types.h"


#define SVM_PICK(o) \
   DEPRECATED(); \
   ASSERT_NOT_NULL(o); \
   GC("Picking <T_OBJECT(@%lu)>...", (ULong)(o)); \
   T_OBJECT::pick(o);\
   GC_APD(" OK"); \
   if(o != NULL){GC_APD(" [references_now=%d]", (o)->references);} \
   GC_APD("\n");

#define SVM_PICK_SAFE(o) DEPRECATED(); if ((o) != NULL) {SVM_PICK((o));}

#define SVM_DROP(o) \
   DEPRECATED(); \
   ASSERT_NOT_NULL(o); \
   GC("Dropping <T_OBJECT(@%lu)>...", (ULong)(o)); \
   T_OBJECT::drop(o); \
   GC_APD(" OK"); \
   if(o != NULL){GC_APD(" [references_now=%d]", (o)->references);} \
   GC_APD("\n");

#define SVM_DROP_SAFE(o) DEPRECATED(); if ((o) != NULL) {SVM_DROP(o);}

#define SVM_ASSERT_REF_COUNT(object, ref_count) \
   if (((Object*)object)->references != ref_count) \
   { FATAL("<Object*(@%lu)>.references must be <%d>, not <%d>.", (ULong)object, ref_count, ((Object*)object)->references); abort(); }


#define SVM_OBJECT_FIELDS_STEP 5

namespace NS_TYPE
{
   class Object
   {
      public: Object* cls;
      public: Object** fields;
      public: ULong field_count;
      public: ULong field_rooms;
      public: int references;
      public: int id;
      public: bool is_abstract;

      public: Object();

      /**
       * Asserts an object is not NULL.
       */
      public: inline static void assert_not_null(Object* object)
      {
         if(object == NULL)
         {
            FATAL("<Object @%lu> is NULL.", (ULong)object);
            abort();
         }
      }

      /**
       * Asserts  an object is of type <type>.
       * Exits the application if not.
       */
      public: inline static void assert_type(Object* object, Object* type)
      {
         #ifdef __ALLOW_SVM_ASSERTIONS__
         if (object->cls != type)
         {
            FATAL(
                  "<Object @%lu> is of type <@%lu>, not <@%lu> as expected.",
                  (ULong)object,
                  (ULong)object->cls,
                  (ULong)type
            );
            abort();
         }
         #endif
      }

      /**
       * Builds an array of object of length argc.
       */
      public: static Object** build_array(int argc, ...);

      /**
       * Compares two objects.
       * \return 0 if they are the same object, -1 if obj1 < obj2 and 1 otherwise
       */
      public: static Short compare_to(Object* obj1, Object* obj2);

      /**
       * Checks if an object is of type <type>.
       * \return True if <object> is of type <type>
       */
      public: static bool check_type(Object* object, Object* type)
      {
         bool result = true;
         #ifdef __ALLOW_SVM_ASSERTIONS__
         if (object->cls != type)
         {
            WARNING(
                  "<Object @%lu> is of type <@%lu>, not <@%lu> as expected.",
                  (ULong)object,
                  (ULong)object->cls,
                  (ULong)type
            );
            result = false;
         }
         #endif
         return result;
      }

      /**
       * Decreases the reference count of an object.
       */
      public: static bool drop(Object* obj);

      /**
       * Decreases the reference count of an object after having checking for
       * null references.
       */
      public: inline static void drop_safe(Object* obj)
      {
         if (obj != NULL)
         {
            Object::drop(obj);
         }
      }

      /**
       * Gets the value of an object field.
       */
      public: Object* get_field(ULong at);

      public: static bool is_null(Object* obj);

      /**
       * Increases the reference count of an object.
       */
      public: static bool pick(Object* obj);

      /**
       * Increases the reference count of an object.
       */
      public: inline static bool pick_safe(Object* obj)
      {
         bool result = false;
         if (obj != NULL)
         {
            Object::pick(obj);
            result = true;
         }
         return result;
      }

      /**
       * Prints the string representation of an object.
       */
      public: static void print(Object* o);

      /**
       * Prints on a new line the string representation of an object.
       */
      public: static void print_line(Object* o);
      public: void resize_field_array(ULong new_size);
      public: void resize_fields_up();
      public: void set_class(Object* type);

      /**
       * Sets an object's field.
       */
      public: void set_field(ULong at, Object* obj);
   };

   extern Object* tOBJECT;
   extern Object* gNULL;
   extern Object* tNULL;
}

#define T_OBJECT NS_TYPE::Object

#endif
