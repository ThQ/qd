#include "util/Object.h"

namespace util
{
   void
   Object::assert_type(t::Object* object, t::Object* type)
   {
      #ifdef __ALLOW_SVM_ASSERTIONS__
      ASSERT(
            object != NULL,
            "util::Object::assert_type(@%lu, @%lu) : object <t::Object @%lu> must NOT be NULL.",
            (ULong)object,
            (ULong)type,
            (ULong)object
      );
      ASSERT(
            type != NULL,
            "util::Object::assert_type(@%lu, @%lu) : type <t::Object @%lu> must NOT be NULL.",
            (ULong)object,
            (ULong)type,
            (ULong)type
      );
      ASSERT(
            object->cls != NULL,
            "util::Object::assert_type(@%lu, @%lu) : object's class <t::Object @%lu> must NOT be NULL.",
            (ULong)object,
            (ULong)type,
            (ULong)object->cls
      );

      if (object->cls != type)
      {
         FATAL(
               "<Object @%lu> is of type <@%lu>, not <@%lu> as expected.",
               (ULong)object,
               //((t::Class*)object->cls)->name.c_str(),
               (ULong)object->cls,
               //((t::Class*)type)->name.c_str(),
               (ULong)type
         );
         abort();
      }
      #endif
   }

   bool
   Object::drop (t::Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);

      #ifdef _SHOW_GC_
      INTERNAL(
            "<%s @%x> DEC_REF_COUNT (.from %ld, .to %ld)\n",
            t::cast_type_to_string(pObject->type),
            (uint)pObject,
            pObject->references,
            pObject->references - 1
      );
      #endif

      --pObject->references;

      #ifdef _DEBUG_
      if (pObject->references < 0)
      {
         WARNING(
               "<%s @%x> NEGATIVE_REFERENCE_COUNT\n",
               t::cast_type_to_string(pObject->type),
               (uint)pObject
         );
      }
      #endif

      if (pObject->references <= 0)
      {
         DELETE(pObject);
      }

      ++ Stats.dwDrops;
      -- Stats.dwReferences;

      return true;
   }

   bool
   Object::pick (t::Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);

      #ifdef _SHOW_GC_
      INTERNAL(
            "<%s @%x> INCR_REF_COUNT (.from %ld, .to %ld)\n",
            t::cast_type_to_string(pObject->type),
            (uint)pObject,
            pObject->references,
            pObject->references + 1
      );
      #endif

      #ifdef _SHOW_GC_
      if (pObject->references < 0)
      {
         WARNING(
               "<%s @%x)> NEGATIVE_REFERENCE_COUNT\n",
               t::cast_type_to_string(pObject->type),
               (uint)pObject
         );
      }
      #endif
      ++ pObject->references;

      ++ Stats.dwPicks;
      ++ Stats.dwReferences;

      return true;
   }
}
