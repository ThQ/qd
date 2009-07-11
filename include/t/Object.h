#ifndef T_OBJECT_H
#define T_OBJECT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "vm/Class.h"
#include "config.h"
#include "debug.h"
#include "Memory.h"
#include "Stats.h"
#include "types.h"
#include "util.h"

#define SVM_OBJECT_FIELDS_STEP 5
#define T__OBJECT__SIZEOF_PTR sizeof(t::Object*)
namespace t
{
   extern vm::Class cOBJECT;

   /**
    * @brief A reference type object.
    */
   class Object
   {
      public: vm::Class*   klass;         ///< Object's class.
      public: UInt64       references;   ///< Number of references to this object.
      public: ushort       type;          ///< Object's type.

      public: Object();

      /**
       * @brief Asserts an object is of type [type]. Exits the application otherwise.
       *
       * @param type A type to assert.
       */
      public: inline void assert_type(ushort type)
      {
         #ifdef __ALLOW_SVM_ASSERTIONS__
         ASSERT_NOT_NULL(this->klass);

         if (this->klass->type != type)
         {
            FATAL(
                  "<Object @%ld> is of type <@%s>, not <@%s> as expected.",
                  (ulong)this,
                  t::cast_type_to_string(this->klass->type),
                  t::cast_type_to_string(type)
            );
            abort();
         }
         #endif
      }

      /**
       * @brief Builds an array of object of length argc.
       *
       * @param argc How many objects.
       * @return An [Object] array of length [argc].
       */
      public: static Object** build_array(int argc, ...);

      /**
       * @brief Compares two objects.
       *
       * @param pObject The object to compare to.
       * @return 0 if they are the same object, -1 if obj1 < obj2 and 1 otherwise
       */
      public: Short compare_to(Object* pObject);

      /**
       * @brief Checks if an object is of type [type].
       *
       * @param type The type to check.
       * @return true if [object] is of type [type].
       */
      public: bool check_type(ushort type)
      {
         bool result = true;
         #ifdef __ALLOW_SVM_ASSERTIONS__
         ASSERT_NOT_NULL(this->klass);
         if (this->klass->type != type)
         {
            WARNING(
                  "<Object @%lu> is of type <@%s>, not <@%s> as expected.",
                  (ulong)this,
                  t::cast_type_to_string(this->klass->type),
                  t::cast_type_to_string(type)
            );
            result = false;
         }
         #endif
         return result;
      }

      /**
       * @brief Dummy function for destroying an object.
       *
       * @param pObject The object to destroy.
       * @return true if everything went well.
       */
      public: inline static bool destroy(Value pObject)
      {
         return true;
      }

      /**
       * @brief Decreases the reference count of an object.
       *
       * @return true if everything went well.
       */
      public: inline bool drop()
      {
         ASSERT_NOT_NULL(this);
         ASSERT_NOT_NULL(this->klass);
         return Object::drop((Object*)this);
      }

      /**
       * @brief Decreases the reference count of an object.
       *
       * @param obj An object to drop.
       * @return true if everything went well.
       */
      public: static bool drop(Object* obj);

      /**
       * @brief Decreases the reference count of an object after having checking for
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
       * @brief Increases the reference count.
       *
       * @return true if everything went well.
       */
      public: inline bool pick()
      {
         return Object::pick(this);
      }

      /**
       * @brief Increases the reference count of an object.
       *
       * @param obj An object to pick.
       * @return true if everything went well.
       */
      public: static bool pick(Object* obj);

      /**
       * @brief Increases the reference count of an object.
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
       * @brief Prints its string represantion in the console.
       */
      public: inline void print()
      {
         ASSERT_NOT_NULL(this->klass);
         this->klass->print_func((Value)this);
      }

      /**
       * @brief Prints the string representation of an object.
       *
       * @param o An object to print.
       */
      public: static void print(Value o);

      /**
       * @brief Prints on a new line its string representation.
       */
      public: inline void print_line()
      {
         ASSERT_NOT_NULL(this->klass);
         this->klass->print_line_func((Value)this);
      }

      /**
       * @brief Prints on a new line the string representation of an object.
       *
       * @param pObject An object to print.
       */
      public: static void print_line(Value pObject);
   };

   //extern Object* tOBJECT;
   extern Object* gNULL;
   //extern Object* tNULL;
}

#define T_OBJECT NS_TYPE::Object

#endif
