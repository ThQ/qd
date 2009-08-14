#include "vm/RegisterPool.h"

namespace vm
{
   RegisterPool::RegisterPool ()
   {
      this->int_register_start_at = 0;
      this->int_register_length = 0;
      this->length = 0;
      this->long_register_start_at = 0;
      this->long_register_length = 0;
      this->object_register_start_at = 0;
      this->object_register_length = 0;
      this->values = NULL;
   }

   RegisterPool::~RegisterPool ()
   {
      if (this->values != NULL)
      {
         // Dropping objects
         uint nObjectRegisterEndAt = this->object_register_start_at + this->object_register_length;
         for (uint i = this->object_register_start_at ; i < nObjectRegisterEndAt ; ++i)
         {
            if (this->values[i] != NULL)
            {
               ((t::Object*)this->values[i])->drop();
               this->values[i] = NULL;
            }
         }

         Memory_FREE(this->values);
      }
   }

   void
   RegisterPool::destroy ()
   {
      
   }

   int
   RegisterPool::get_int (uint nIndex)
   {
      return (int)this->values[this->int_register_start_at + nIndex];
   }

   long
   RegisterPool::get_long (uint nIndex)
   {
      return (long)this->values[this->long_register_start_at + nIndex];
   }

   t::Object*
   RegisterPool::get_object (uint nIndex)
   {
      return (t::Object*)this->values[this->object_register_start_at + nIndex];
   }

   void
   RegisterPool::print ()
   {
      uint i = 0;
      uint j = 0;

      i = this->int_register_start_at;
      printf ("  [Int (%u)]\n", this->int_register_length);
      if (this->int_register_length > 0)
      {
         printf(" >-------------------\n");
         j = 0;
         while ( i < this->int_register_start_at + this->int_register_length )
         {
            printf("  (%u,%u) %d\n", i, j, (int)this->values[i]);
            ++ i;
            ++ j;
         }
      }

      printf("\n  [Long (%u)]\n", this->long_register_length);
      if (this->long_register_length > 0)
      {
         printf(" >-------------------\n");
         j = 0;
         while (i < this->long_register_start_at + this->long_register_length )
         {
            printf("  (%u,%u) %ld\n", i, j, (long)this->values[i]);
            ++ i;
            ++ j;
         }
      }

      printf("\n  [Object (%u)]\n", this->object_register_length);
      if (this->object_register_length > 0)
      {
         printf(" >-------------------\n");
         j = 0;
         while (i < this->object_register_start_at + this->object_register_length )
         {
            if (this->values[i] == NULL)
            {
               printf("  (%u,%u) Null\n", i, j);
            }
            else
            {
               printf(
                     "  (%u,%u) <%s:0x%x>\n",
                     i,
                     j,
                     t::get_type_name(((t::Object*)this->values[i])->type),
                     (uint)this->values[i]
                     );
            }
            ++ i;
            ++ j;
         }
      }
   }

   void
   RegisterPool::set_object (uint nIndex, t::Object* pObject)
   {
      ASSERT_NOT_NULL(pObject);
      ASSERT(
            nIndex < this->object_register_length,
            "OBJECT_REGISTER_DOES_NOT_EXIST (.at %u, .max %u)",
            nIndex,
            this->object_register_length
      );
      uint nObjectAt = this->object_register_start_at + nIndex;
      if (this->values[nObjectAt] != NULL)
      {
         ((t::Object*)this->values[nObjectAt])->drop();
      }

      ((t::Object*)pObject)->pick();
      this->values[nObjectAt] = (t::Value)pObject;
   }

   void
   RegisterPool::set_int (uint nIndex, int nValue)
   {
      ASSERT(
            nIndex < this->int_register_length,
            "INT_REGISTER_DOES_NOT_EXIST (.at %u, .max %u)",
            nIndex,
            this->int_register_length
      );
      this->values[this->int_register_start_at + nIndex] = (t::Value)nValue;
   }

   void
   RegisterPool::set_long (uint nIndex, long nValue)
   {
      ASSERT(
            nIndex < this->long_register_length,
            "LONG_REGISTER_DOES_NOT_EXIST (.at %u, .max %u)",
            nIndex,
            this->long_register_length
      );
      this->values[this->long_register_start_at + nIndex] = (t::Value)nValue;
   }

   void
   RegisterPool::size (uint nInt, uint nLong, uint nObject)
   {
      ASSERT_NULL(this->values);

      this->length = nInt + (nLong * 2) + nObject;

      this->int_register_start_at = 0;
      this->int_register_length = nInt;

      this->long_register_start_at = this->int_register_start_at + nInt;
      this->long_register_length = nLong;

      this->object_register_start_at = this->long_register_start_at + nLong;
      this->object_register_length = nObject;

      Memory_ALLOC(this->values, t::Value, this->length);

      for (uint i = 0 ; i < this->length ; ++i)
      {
         this->values[i] = NULL;
      }
   }
}
