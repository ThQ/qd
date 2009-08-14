#ifndef T__OBJECT__H
#define T__OBJECT__H __FILE__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "vm/Class.h"
#include "assert.h"
#include "config.h"
#include "log.h"
#include "Memory.h"
#include "Stats.h"
#include "types.h"
#include "util.h"

#define T__OBJECT__SIZEOF_PTR (sizeof(t::Object*))

namespace t
{
   extern vm::Class cOBJECT;

   /**
    * @brief A reference type object.
    */
   class Object
   {
      public: const vm::Class*   klass;         ///< Object's class.
      public: UInt64             references;    ///< Number of references to this object.
      public: ushort             type;          ///< Object's type.

      /**
       * @brief Default constructor.
       */
      public: Object();

      /**
       * @brief Deletes a t::Object.
       *
       * @param pObject The t::Object to delete.
       */
      public: static void __delete__ (Value pObject);

      /**
       * @brief Creates a new t::Object.
       *
       * @return A pointer to the t::Object created.
       */
      public: static Value __new__ ();

      /**
       * @brief Prints the string representation of an object.
       *
       * @param o An object to print.
       */
      public: static void __print__ (Value o);

      /**
       * @brief Prints on a new line the string representation of an object.
       *
       * @param pObject An object to print.
       */
      public: static void __print_line__ (Value pObject);

      /**
       * @brief Asserts an object is of type [type]. Exits the application otherwise.
       *
       * @param type A type to assert.
       */
      public: inline void assert_type (ushort type)
      {
         #ifdef __ALLOW_SVM_ASSERTIONS__
         ASSERT_NOT_NULL(this->klass);

         if (this->klass->type != type)
         {
            FATAL(
                  "<Object @%ld> is of type <@%s>, not <@%s> as expected.",
                  (ulong)this,
                  t::get_type_name(this->klass->type),
                  t::get_type_name(type)
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
      public: static Object** build_array (int argc, ...);

      /**
       * @brief Compares two objects.
       *
       * @param pObject The object to compare to.
       * @return 0 if they are the same object, -1 if obj1 < obj2 and 1 otherwise
       */
      public: Short compare_to (Object* pObject);

      /**
       * @brief Checks if an object is of type [type].
       *
       * @param type The type to check.
       * @return true if [object] is of type [type].
       */
      public: bool check_type (ushort type)
      {
         bool result = true;
         ASSERT_NOT_NULL(this->klass);
         if (this->klass->type != type)
         {
            WARNING(
                  "<Object @%lu> is of type <@%s>, not <@%s> as expected.",
                  (ulong)this,
                  t::get_type_name(this->klass->type),
                  t::get_type_name(type)
            );
            result = false;
         }
         return result;
      }

      /**
       * @brief Dummy function for destroying an object.
       *
       * @param pObject The object to destroy.
       * @return true if everything went well.
       */
      public: inline static bool destroy (Value pObject)
      {
         return true;
      }

      /**
       * @brief Decreases the reference count of an object.
       *
       * @return true if everything went well.
       */
      public: inline bool drop ()
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
      public: static bool drop (Object* obj);

      /**
       * @brief Decreases the reference count of each object in an array.
       *
       * @param nCount How many objects in the array.
       * @param pObjects The array of objects to drop.
       * @return true if everything went well.
       */
      public: static bool drop (uchar nCount, Object** pObjects);

      /**
       * @brief Decreases the reference count of an object after having checking for
       * null references.
       *
       * @param obj An object to drop.
       * @return true if everything went well.
       */
      public: inline static void drop_safe (Object* obj)
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
      public: inline bool pick ()
      {
         return Object::pick(this);
      }

      /**
       * @brief Increases the reference count of an object.
       *
       * @param obj An object to pick.
       * @return true if everything went well.
       */
      public: static bool pick (Object* obj);

      /**
       * @brief Increases the reference count of an object.
       *
       * @param obj An object to pick.
       * @return true if everything went well.
       */
      public: inline static bool pick_safe (Object* obj)
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
      public: inline void print ()
      {
         ASSERT_NOT_NULL(this->klass);
         this->klass->print_func((Value)this);
      }
      /**
       * @brief Prints on a new line its string representation.
       */
      public: inline void print_line ()
      {
         ASSERT_NOT_NULL(this->klass);
         this->klass->print_line_func((Value)this);
      }
   };
}

#define T_OBJECT NS_TYPE::Object

#endif
