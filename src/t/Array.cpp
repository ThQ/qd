#include "t/Array.h"

namespace t
{
   VM_CLASS__NEW(cARRAY, t::Array, t::ARRAY_TYPE, &cOBJECT);

   Array::Array ()
   {
      this->_init();
   }

   Array::Array (ushort nItemType, uint length)
   {
      this->_init();
      this->set_item_type(nItemType);
      this->size(length);
   }

   Array::Array (ushort nItemType, vm::Class* pItemClass, uint length)
   {
      this->_init();
      this->set_item_type(nItemType, pItemClass);
      this->size(length);
   }

   Array::Array (ushort nItemType, vm::Class* pItemClass, uint dwArrayLength, Value* pItems)
   {
      this->_init();
      this->set_item_type(nItemType, pItemClass);
      this->size(dwArrayLength);

      if (T__IS_VALUE_TYPE(nItemType))
      {
         LOOP_FROM_TO(uint, i, 0, dwArrayLength)
         {
            this->items[i] = pItems[i];
         }
      }
      else
      {
         LOOP_FROM_TO(uint, i, 0, dwArrayLength)
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
      if (T__IS_NOT_VALUE_TYPE(this->item_type))
      {
         LOOP_FROM_TO(uint, i, 0, this->length)
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
   Array::__delete__ (Value pArray)
   {

   }

   Value
   Array::__new__ ()
   {
      NEW(pResult, t::Array);
      return pResult;
   }

   void
   Array::__print__ (Value pArray)
   {
      t::Array* pArr = (t::Array*)pArray;
      switch (pArr->item_type)
      {
         case t::BOOL_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pArr->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%s", ((bool)pArr->items[i]) == 0 ? "False" : "True");
            }
            printf("]");
            break;
         }

         case t::CHAR_TYPE:
         case t::SHORT_TYPE:
         case t::INT_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pArr->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%d", (int)pArr->items[i]);
            }
            printf("]");
            break;
         }

         case t::U_CHAR_TYPE:
         case t::U_SHORT_TYPE:
         case t::U_INT_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pArr->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%u", (uint)pArr->items[i]);
            }
            printf("]");
            break;
         }
      }
   }

   void
   Array::__print_line__ (Value pArray)
   {
      Array::__print__ (pArray);
      printf("\n");
   }

   void
   Array::size (uint array_size)
   {
      // A 0-length array may be useful : A function may want to return an empty array.
      // ASSERT(array_size != 0, "An Array of 0-length must not be created.");
      ASSERT(this->length == 0, "Cannot size an array already sized.");
      ASSERT(this->items == NULL, "Cannot size an array that is already containing objects.");

      this->length = array_size;
      this->slot_count = array_size * this->slot_size;
      Memory_ALLOC(this->items, Value, array_size * this->slot_size);

      LOOP_FROM_TO(uint, i, 0, slot_count)
      {
         this->items[i] = NULL;
      }
   }

   t::Array*
   Array::slice (uint nStartIndex, uint nLength, uint nStep)
   {
      ASSERT(nStep != 0, "ZERO_STEP");
      ASSERT(nLength <= this->length, "SLICE_TOO_BIG");

      uint nSliceLen = (nLength % nStep) == 0 ? (nLength / nStep) : (nLength / nStep) + 1;

      NEW(pSlice, t::Array)(this->item_type, this->item_class, nSliceLen);

      for (uint i = nStartIndex, j = 0; i < nLength ; i += nStep, ++j)
      {
         pSlice->items[j] = this->items[i];
      }

      return pSlice;
   }
}
