#include "t/BaseArray.h"

namespace t
{
   BaseArray::BaseArray()
   {
      this->item_class = NULL;
      //this->item_cursor = NULL;
      this->item_type = t::NULL_TYPE;
      this->items = NULL;
      this->slot_size = 1;
   }

   void
   BaseArray::clear ()
   {
      if (T__IS_VALUE_TYPE(this->item_type))
      {
         for (UInt64 i = 0; i < this->length; ++i)
         {
            this->items[i] = NULL;
         }
      }
      else
      {
         for (UInt64 i = 0; i < this->slot_count ; i += this->slot_size)
         {
            ASSERT_NOT_NULL(this->items[i]);

            ((Object*)this->items[i])->drop();
            this->items[i] = NULL;
         }
      }
   }

   void
   BaseArray::clear_item (UInt64 nRelativeIndex)
   {
      ASSERT(
            nRelativeIndex < this->length,
            "Index [%lu] out of range [0:%lu].",
            (ulong)nRelativeIndex,
            (ulong)this->length
      );

      UInt64 nAbsoluteIndex = nRelativeIndex * this->slot_size;
      if (T__IS_NOT_VALUE_TYPE(this->item_type) && this->items[nAbsoluteIndex] != NULL)
      {
         ((Object*)this->items[nAbsoluteIndex])->drop();
      }

      for (UInt64 i = nAbsoluteIndex ; i < this->slot_size ; ++i)
      {
         this->items[nAbsoluteIndex] = NULL;
      }
   }

   void
   BaseArray::clear_range (UInt64 nRelativeRangeStart, UInt64 nRelativeRangeEnd)
   {
      ASSERT(nRelativeRangeStart < nRelativeRangeEnd, "Start index must be lower than end index.");
      ASSERT(nRelativeRangeEnd <= this->length, "End index must be lower than the item count.");

      UInt64 nAbsoluteRangeStart = nRelativeRangeStart * this->slot_size;
      UInt64 nAbsoluteRangeEnd = nRelativeRangeEnd * this->slot_size;

      if (T__IS_VALUE_TYPE(this->item_type))
      {
         for (UInt64 i = nAbsoluteRangeStart ; i < nAbsoluteRangeEnd ; ++ i)
         {
            this->items[i] = NULL;
         }
      }
      else
      {
         for (UInt64 i = nAbsoluteRangeStart ; i < nAbsoluteRangeEnd ; i += this->slot_size)
         {
            if (this->items[i] != NULL)
            {
               ASSERT_NOT_NULL(((Object*)this->items[i])->klass);

               ((Object*)this->items[i])->drop();

               for (UInt64 j = 0 ; j < this->slot_size ; ++ j)
               {
                  this->items[nAbsoluteRangeStart + j] = NULL;
               }
            }
         }
      }
   }

   Value
   BaseArray::get_object_at (UInt64 nRelativeIndex)
   {
      ASSERT(
            nRelativeIndex < this->length,
            "Index %ld out of range [0:%ld[.",
            (ulong)nRelativeIndex,
            (ulong)this->length
      );
      ASSERT(
            T__IS_NOT_LITERAL_TYPE(this->item_type),
            "Cannot use ::get_object_at on a list of literals."
      );
      return this->items[nRelativeIndex * this->slot_size];
   }

   Value
   BaseArray::get_value_at (UInt64 nRelativeIndex)
   {
      ASSERT(
            nRelativeIndex < this->length,
            "Index %ld out of range [0:%ld[.",
            (ulong)nRelativeIndex,
            (ulong)this->length
      );
      return this->items[nRelativeIndex * this->slot_size];
   }

   void
   BaseArray::reverse (uint nStartIndex, uint nLength)
   {
      t::Value pTmp = NULL;
      uint nHalfLength = nLength / 2;
      uint nEndIndex = nStartIndex + nLength - 1;
      for (uint i = nStartIndex ; i < nHalfLength ; ++i)
      {
         pTmp = this->items[i];
         this->items[i] = this->items[nEndIndex - i];
         this->items[nEndIndex - i] = pTmp;
      }
   }

   void
   BaseArray::set_item (UInt64 nRelativeIndex, Value pNewItem)
   {
      ASSERT(
            this->item_type != t::UNDEFINED_TYPE,
             "An array must have its type defined"
      );
      ASSERT(
            nRelativeIndex < this->length,
            "Index [%ld] out of range [0:%ld].",
            (ulong)nRelativeIndex,
            (ulong)this->length
      );

      UInt64 nAbsoluteIndex = nRelativeIndex * this->slot_size;

      if (T__IS_NOT_VALUE_TYPE(this->item_type))
      {
         ASSERT_NOT_NULL(pNewItem);

         if (this->items[nAbsoluteIndex] != NULL)
         {
            ASSERT_NOT_NULL(((Object*)this->items[nAbsoluteIndex])->klass);
            ((Object*)this->items[nAbsoluteIndex])->drop();
         }
         ((Object*)pNewItem)->pick();
      }

      this->items[nAbsoluteIndex] = pNewItem;
   }

   void
   BaseArray::set_item_type (ushort type, vm::Class* cls)
   {
      #ifdef _DEBUG_
      if (T__IS_VALUE_TYPE(type))
      {
         ASSERT_NULL(cls);
      }
      else
      {
         ASSERT(
               cls != NULL,
               "<Array 0x%x> NULL_CLASS (.type %u)",
               (uint)this,
               type
         );
      }
      #endif

      this->item_type = type;
      this->item_class = cls;
      this->slot_size = t::get_type_slots(type);
   }
}
