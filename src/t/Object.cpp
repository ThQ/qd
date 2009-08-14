#include "t/Object.h"

namespace t
{
   VM_CLASS__NEW(cOBJECT, t::Object, t::UNDEFINED_TYPE, NULL);

   Object::Object ()
   {
      this->klass = &cOBJECT;
      this->references = 0;
   }

   void
   Object::__delete__ (Value pObject)
   {

   }

   Value
   Object::__new__ ()
   {
      NEW(pResult, t::Object);
      return pResult;
   }

   void
   Object::__print__ (Value pObject)
   {
      printf(
            "<%s:0x%x>",
            t::get_type_name(((Object*)pObject)->type),
            (uint)pObject
      );
   }

   void
   Object::__print_line__ (Value pObject)
   {
      printf(
            "<%s:0x%x>\n",
            t::get_type_name(((Object*)pObject)->klass->type),
            (uint)pObject
      );
   }

   Object**
   Object::build_array (int argc, ...)
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
   Object::compare_to (Object* pObject)
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
   Object::drop (Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);
      ASSERT_NOT_NULL(pObject->klass);

      LOG_REFCOUNT(
            "<%s:0x%x> DEC_REF_COUNT (.type %u, .klass_at 0x%x, .from %lu, .to %lu)\n",
            t::get_type_name(pObject->type),
            (uint)pObject,
            pObject->type,
            (uint)pObject->klass,
            (ulong)pObject->references,
            (ulong)pObject->references - 1
      );

      #ifdef _DEBUG_
      if (pObject->references == 0)
      {
         FATAL(
               "<%s:0x%x> NEGATIVE_REFERENCE_COUNT\n",
               t::get_type_name(pObject->type),
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
         pObject = NULL;
      }

      return true;
   }

   bool
   Object::drop (uchar nCount, Object** pObjects)
   {
      for (uchar i = 0 ; i < nCount ; ++i)
      {
         Object::drop(pObjects[i]);
      }
      return true;
   }


   bool
   Object::pick (Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);
      ASSERT_NOT_NULL(pObject->klass);

      LOG_REFCOUNT(
            "<%s:0x%x> INCR_REF_COUNT (.type %u, .klass 0x%x, .from %lu, .to %lu)\n",
            t::get_type_name(pObject->klass->type),
            (uint)pObject,
            pObject->type,
            (uint)pObject->klass,
            (ulong)pObject->references,
            (ulong)pObject->references + 1
      );

      #ifdef _SHOW_GC_
      if (pObject->references < 0)
      {
         FATAL(
               "<%s:0x%x)> NEGATIVE_REFERENCE_COUNT\n",
               t::get_type_name(pObject->klass->type),
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
}
