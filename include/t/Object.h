#ifndef T_OBJECT_H
#define T_OBJECT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "config.h"
#include "debug.h"
#include "Memory.h"
#include "Stats.h"
#include "types.h"
#include "util.h"

#define SVM_ASSERT_REF_COUNT(object, ref_count) \
   DEPRECATED(); \
   if (((Object*)object)->references != ref_count) \
   { FATAL("<Object*(@%lu)>.references must be <%d>, not <%d>.", (ULong)object, ref_count, ((Object*)object)->references); abort(); }

#define SVM_OBJECT_FIELDS_STEP 5

namespace t
{
   /**
    * Objects for the VM.
    *
    * @todo Remove attr [cls].
    */
   class Object
   {
      public: bool (*fpDestroy)(Object* pObject);
      public: void (*fpPrint)(Object* pObject);
      public: void (*fpPrintLine)(Object* pObject);

      public: ushort type;          ///< Object's type.
      public: Object* cls;          ///< Object's class. USELESS NOW.
      public: Object** fields;      ///< Object's fields, to store attributes. A @cls{t::Variable} array.
      public: ULong field_count;    ///< Number of fields.
      public: ULong field_rooms;    ///< Size of [fields] array.
      public: ULong references;     ///< Number of references to this object.
      //public: int id;             ///< WTF ?
      //public: bool is_abstract;   ///< WTF ?

      public: Object();

      /*:*
       * Asserts an object is not NULL.
       *
       * @param object An object to check.
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
       * Asserts an object is of type [type]. Exits the application otherwise.
       *
       * @param object An object to check.
       * @param type A type to assert.
       */
      public: inline void assert_type(ushort type)
      {
         #ifdef __ALLOW_SVM_ASSERTIONS__
         if (this->type != type)
         {
            FATAL(
                  "<Object @%ld> is of type <@%d>, not <@%d> as expected.",
                  (ulong)this,
                  this->type,
                  type
            );
            abort();
         }
         #endif
      }

     /**
       * Asserts an object is of type [type]. Exits the application otherwise.
       *
       * @param object An object to check.
       * @param type A type to assert.
       * @deprecated
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
       *
       * @param argc How many objects.
       * @return An [Object] array of length [argc].
       */
      public: static Object** build_array(int argc, ...);

      /**
       * Compares two objects.
       *
       * @param obj1 Object 1.
       * @param obj2 Object 2.
       * @return 0 if they are the same object, -1 if obj1 < obj2 and 1 otherwise
       */
      public: static Short compare_to(Object* obj1, Object* obj2);

      /**
       * Checks if an object is of type [type].
       * @param object An object to check.
       * @param type The type to check.
       * @return true if [object] is of type [type].
       */
      public: bool check_type(ushort type)
      {
         bool result = true;
         #ifdef __ALLOW_SVM_ASSERTIONS__
         if (this->type != type)
         {
            WARNING(
                  "<Object @%lu> is of type <@%d>, not <@%d> as expected.",
                  (ulong)this,
                  this->type,
                  type
            );
            result = false;
         }
         #endif
         return result;
      }

      /**
       * Checks if an object is of type [type].
       * @param object An object to check.
       * @param type The type to check.
       * @return true if [object] is of type [type].
       * @deprecated
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
       *
       * @return true if everything went well.
       */
      public: inline bool drop()
      {
         return Object::drop((Object*)this);
      }

      /**
       * Decreases the reference count of an object.
       *
       * @param obj An object to drop.
       * @return true if everything went well.
       */
      public: static bool drop(Object* obj);

      /**
       * Decreases the reference count of an object after having checking for
       * null references.
       *
       * @param obj An object to drop.
       * @return true if everything went well.
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
       *
       * @param at The index of the field to get.
       * @return The object in field at [at].
       */
      public: Object* get_field(ULong at);

      /**
       * Checks if an object is null.
       *
       * @param obj An object to check.
       * @return true if [obj] is null.
       */
      public: static bool is_null(Object* obj);

      /**
       * Increases the reference count.
       *
       * @return true if everything went well.
       */
      public: inline bool pick()
      {
         return Object::pick(this);
      }

      /**
       * Increases the reference count of an object.
       *
       * @param obj An object to pick.
       * @return true if everything went well.
       */
      public: static bool pick(Object* obj);

      /**
       * Increases the reference count of an object.
       *
       * @param obj An object to pick.
       * @return true if everything went well.
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
       * Prints its string represantion in the console.
       */
      public: void print();

      /**
       * Prints the string representation of an object.
       *
       * @param o An object to print.
       */
      public: static void print(Object* o);

      /**
       * Prints on a new line its string representation.
       */
      public: void print_line();

      /**
       * Prints on a new line the string representation of an object.
       *
       * @param o An object to print.
       */
      public: static void print_line(Object* o);

      /**
       * Resizes field array.
       *
       * @param new_size The new size of the field array.
       */
      public: void resize_field_array(ULong new_size);

      /**
       * Resized field array up.
       */
      public: void resize_fields_up();

      /**
       * Sets the class of an object.
       *
       * @param type The new class.
       */
      public: void set_class(Object* type);

      /**
       * Sets an object's field.
       *
       * @param at The index of the field.
       * @param obj An object to set the field to.
       */
      public: void set_field(ULong at, Object* obj);
   };

   //extern Object* tOBJECT;
   extern Object* gNULL;
   //extern Object* tNULL;
}

#define T_OBJECT NS_TYPE::Object

#endif
