#include "t/Array.h"

namespace t
{
   Array::Array ()
   {
      this->_init();
   }

   Array::Array (ushort nItemType, Class* pItemClass, UInt64 length)
   {
      this->_init();
      this->set_type(nItemType, pItemClass);
      this->size(length);
   }

   Array::Array (ushort nItemType, Class* pItemClass, UInt64 dwArrayLength, Object** pItems)
   {
      this->_init();
      this->set_type(nItemType, pItemClass);
      this->size(dwArrayLength);

      LOOP_FROM_TO(UInt64, i, 0, dwArrayLength)
      {
         ASSERT_NULL(this->items[i]);
         ASSERT_NOT_NULL(pItems[i]);
         pItems[i]->assert_type((ushort)nItemType);

         pItems[i]->pick();
         this->items[i] = pItems[i];
      }
   }

   Array::~Array ()
   {
      LOOP_FROM_TO(UInt64, i, 0, this->item_count)
      {
         if (this->items[i] != NULL)
         {
            this->items[i]->drop();
            this->items[i] = NULL;
         }
      }

      if (this->item_class != NULL)
      {
         this->item_class->drop();
      }
   }

   void
   Array::clear ()
   {
      LOOP_FROM_TO(UInt64, item_index, 0, this->item_count)
      {
         ASSERT_NOT_NULL(this->items[item_index]);

         this->items[item_index]->drop();
         this->items[item_index] = t::gNULL;
         t::gNULL->pick();
      }
   }

   void
   Array::clear_item (UInt64 item_index)
   {
      ASSERT(item_index < this->item_count, "Index [%ld] out of range [0:%ld].", (ulong)item_index, (ulong)this->item_count);
      ASSERT_NOT_NULL(this->items[item_index]);

      if (this->items[item_index] != NULL)
      {
         this->items[item_index]->drop();
      }
      this->items[item_index] = NULL;
   }

   void
   Array::clear_range (UInt64 range_start, UInt64 range_end)
   {
      ASSERT(range_start < range_end, "Start index must be lower than end index.");
      ASSERT(range_end <= this->item_count, "End index must be lower than the item count.");

      LOOP_FROM_TO(UInt64, item_index, range_start, range_end)
      {
         ASSERT_NOT_NULL(this->items[item_index]);

         this->items[item_index]->drop();
         this->items[item_index] = NULL;
      }
   }

   void
   Array::set_item (UInt64 item_index, T_OBJECT* new_item)
   {
      ASSERT_NOT_NULL(new_item);
      ASSERT(item_index < this->item_count, "Index [%ld] out of range [0:%ld].", (ulong)item_index, (ulong)this->item_count);

      if (this->items[item_index] != NULL)
      {
         this->items[item_index]->drop();
      }

      this->items[item_index] = new_item;
      new_item->pick();
   }

   void
   Array::set_type (ushort type, Class* cls)
   {
      ASSERT_NULL(this->cls);

      this->item_type = type;
      this->item_class = cls;
      if (cls != NULL)
      {
         cls->pick();
      }
   }

   void
   Array::size (UInt64 array_size)
   {
      // A 0-length array may be useful : A function may want to return an empty array.
      // ASSERT(array_size != 0, "An Array of 0-length must not be created.");
      ASSERT(this->item_count == 0, "Cannot size an array already sized.");
      ASSERT(this->items == NULL, "Cannot size an array that is already containing objects.");
      this->item_count = array_size;
      this->items = (Object**) malloc(sizeof(Object*) * array_size);

      LOOP_FROM_TO(UInt64, i, 0, array_size)
      {
         this->items[i] = NULL;
      }
   }

   //T_OBJECT* tARRAY = NULL;
}


