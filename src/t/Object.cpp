#include "t/Object.h"

namespace t
{
   VM_CLASS__NEW(cOBJECT, t::Object, t::UNDEFINED_TYPE, NULL);

   Object* gNULL = NULL;

   Object::Object()
   {
      this->klass = &cOBJECT;
      this->references = 0;
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
   Object::compare_to(Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);

      if (this == pObject)
      {
         return 0;
      }
      else if ((uint)this < (uint)pObject)
      {
         return -1;
      }
      else
      {
         return 1;
      }
   }

   bool
   Object::drop(Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);
      ASSERT_NOT_NULL(pObject->klass);

      #ifdef _SHOW_GC_
      INTERNAL(
            "<%s @%x> DEC_REF_COUNT (.from %ld, .to %ld)\n",
            t::cast_type_to_string(pObject->klass->type),
            (uint)pObject,
            pObject->references,
            pObject->references - 1
      );
      #endif

      #ifdef _DEBUG_
      if (pObject->references == 0)
      {
         FATAL(
               "<%s @%x> NEGATIVE_REFERENCE_COUNT\n",
               t::cast_type_to_string(pObject->klass->type),
               (uint)pObject
         );
      }
      #endif

      -- pObject->references;

      #ifdef QD__VM__KEEP_STATS
      ++ Stats.dwDrops;
      -- Stats.dwReferences;
      #endif

      if (pObject->references == 0)
      {
         #ifdef QD__VM__KEEP_STATS
         ++ Stats.dwFinalDrops;
         #endif

         if (pObject->klass->destroy_func != NULL)
         {
            pObject->klass->destroy_func((Value)pObject);
         }
         DELETE(pObject);
      }

      return true;
   }

   bool
   Object::pick(Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);
      ASSERT_NOT_NULL(pObject->klass);

      #ifdef _SHOW_GC_
      INTERNAL(
            "<%s @%x> INCR_REF_COUNT (.from %ld, .to %ld)\n",
            t::cast_type_to_string(pObject->klass->type),
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
               t::cast_type_to_string(pObject->klass->type),
               (uint)pObject
         );
      }
      #endif

      #ifdef QD__VM__KEEP_STATS
      if (pObject->references == 0)
      {
         ++ Stats.dwInitialPicks;
      }
      ++ Stats.dwPicks;
      ++ Stats.dwReferences;
      #endif

      ++ pObject->references;

      return true;
   }

   void
   Object::print(Value pObject)
   {
      printf(
            "<%s @%x>",
            t::cast_type_to_string(((Object*)pObject)->type),
            (uint)pObject
      );
   }

   void
   Object::print_line(Value pObject)
   {
      printf(
            "<%s @%x>\n",
            t::cast_type_to_string(((Object*)pObject)->klass->type),
            (uint)pObject
      );
   }
}
