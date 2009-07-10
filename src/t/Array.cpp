#include "t/Array.h"

namespace t
{
   VM_CLASS__NEW(cARRAY, t::Array, t::ARRAY_TYPE, &cOBJECT);

   Array::Array ()
   {
      this->_init();
   }

   Array::Array (ushort nItemType, vm::Class* pItemClass, UInt64 length)
   {
      this->_init();
      this->set_item_type(nItemType, pItemClass);
      this->size(length);
   }

   Array::Array (ushort nItemType, vm::Class* pItemClass, UInt64 dwArrayLength, Value* pItems)
   {
      this->_init();
      this->set_item_type(nItemType, pItemClass);
      this->size(dwArrayLength);

      if (T__IS_LITERAL_TYPE(nItemType))
      {
         LOOP_FROM_TO(UInt64, i, 0, dwArrayLength)
         {
            this->items[i] = pItems[i];
         }
      }
      else
      {
         LOOP_FROM_TO(UInt64, i, 0, dwArrayLength)
         {
            ASSERT_NULL(this->items[i]);
            ASSERT_NOT_NULL(pItems[i]);
            ((Object*)pItems[i])->assert_type((ushort)nItemType);

            ((Object*)pItems[i])->pick();
            this->items[i] = pItems[i];
         }
      }
   }

   Array::~Array ()
   {
      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, i, 0, this->item_count)
         {
            if (this->items[i] != NULL)
            {
               ((Object*)this->items[i])->drop();
               this->items[i] = NULL;
            }
         }
      }
   }

   void
   Array::clear ()
   {
      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, item_index, 0, this->item_count)
         {
            this->items[item_index] = NULL;
         }
      }
      else
      {
         LOOP_FROM_TO(UInt64, item_index, 0, this->item_count)
         {
            ASSERT_NOT_NULL(this->items[item_index]);

            ((Object*)this->items[item_index])->drop();
            this->items[item_index] = NULL;
         }
      }
   }

   void
   Array::clear_item (UInt64 item_index)
   {
      ASSERT(
            item_index < this->item_count,
            "Index [%lu] out of range [0:%lu].",
            (ulong)item_index,
            (ulong)this->item_count
      );

      if (T__IS_NOT_LITERAL_TYPE(this->item_type) && this->items[item_index] != NULL)
      {
         ((Object*)this->items[item_index])->drop();
      }
      this->items[item_index] = NULL;
   }

   void
   Array::clear_range (UInt64 range_start, UInt64 range_end)
   {
      ASSERT(range_start < range_end, "Start index must be lower than end index.");
      ASSERT(range_end <= this->item_count, "End index must be lower than the item count.");

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, item_index, range_start, range_end)
         {
            this->items[item_index] = NULL;
         }
      }
      else
      {
         LOOP_FROM_TO(UInt64, item_index, range_start, range_end)
         {
            if (this->items[item_index] != NULL)
            {
               ASSERT_NOT_NULL(((Object*)this->items[item_index])->klass);

               ((Object*)this->items[item_index])->drop();
               this->items[item_index] = NULL;
            }
         }
      }
   }

   void
   Array::set_item (UInt64 item_index, Value new_item)
   {
      ASSERT(this->item_type != t::UNDEFINED_TYPE, "An array must have its type defined");
      ASSERT(item_index < this->item_count, "Index [%ld] out of range [0:%ld].", (ulong)item_index, (ulong)this->item_count);

      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         ASSERT_NOT_NULL(new_item);
         if (this->items[item_index] != NULL)
         {
            ASSERT_NOT_NULL(((Object*)this->items[item_index])->klass);
            ((Object*)this->items[item_index])->drop();
         }
         ((Object*)new_item)->pick();
      }

      this->items[item_index] = new_item;
   }

   void
   Array::set_item_type (ushort type, vm::Class* cls)
   {
#     ifdef _DEBUG_
      if (T__IS_LITERAL_TYPE(type))
      {
         ASSERT_NULL(cls);
      }
      else
      {
         ASSERT_NOT_NULL(cls);
      }
#     endif

      this->item_type = type;
      this->item_class = cls;

   }

   void
   Array::size (UInt64 array_size)
   {
      // A 0-length array may be useful : A function may want to return an empty array.
      // ASSERT(array_size != 0, "An Array of 0-length must not be created.");
      ASSERT(this->item_count == 0, "Cannot size an array already sized.");
      ASSERT(this->items == NULL, "Cannot size an array that is already containing objects.");

      this->item_count = array_size;
      this->items = (Value*) malloc(sizeof(Object*) * array_size);

      LOOP_FROM_TO(UInt64, i, 0, array_size)
      {
         this->items[i] = NULL;
      }
   }

   //T_OBJECT* tARRAY = NULL;
}


