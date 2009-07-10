#include "t/List.h"

namespace t
{
   VM_CLASS__NEW(cLIST, t::List, t::LIST_TYPE, &cOBJECT);

   List::List()
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::LIST_TYPE;
      this->klass = &cLIST;
      this->item_type = t::NULL_TYPE;
      this->item_class = NULL;
   }

   List::List(ushort ItemType)
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::LIST_TYPE;
      this->klass = &cLIST;
      this->item_type = ItemType;
      this->item_class = NULL;
   }

   List::List(ushort ItemType, vm::Class* pItemClass)
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::LIST_TYPE;
      this->klass = &cLIST;
      this->item_type = ItemType;
      this->item_class = pItemClass;
   }

   void
   List::clear()
   {
      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO (UInt64, i, 0, this->length)
         {
            this->items[i] = NULL;
         }
      }
      else
      {
         LOOP_FROM_TO (UInt64, i, 0, this->length)
         {
            if (this->items[i] != NULL)
            {
               ((Object*)this->items[i])->drop();
            }
            this->items[i] = NULL;
         }
      }
   }

   List*
   List::copy()
   {
      List* pCopiedList = new List;
      pCopiedList->item_type = this->item_type;
      pCopiedList->item_class = this->item_class;
      pCopiedList->length = this->length;
      pCopiedList->items = (Value*)MALLOC(sizeof(Value) * this->length);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, i, 0, this->length)
         {
            pCopiedList->items[i] = this->items[i];
         }
      }
      else
      {
         LOOP_FROM_TO(UInt64, i, 0, this->length)
         {
            pCopiedList->items[i] = this->items[i];
            ((Object*)pCopiedList->items[i])->pick();
         }
      }
      ASSERT_NOT_NULL(pCopiedList);
      return pCopiedList;
   }

   List*
   List::copy_flatten()
   {
      List* pFlattenedList = NULL;

      if (this->item_type == t::LIST_TYPE)
      {
         LOOP_FROM_TO(UInt64, i, 0, this->length)
         {
            pFlattenedList->push_list(((List*)this->items[i])->copy_flatten());
         }
      }
      else
      {
         pFlattenedList = this->copy();
      }

      ASSERT_NOT_NULL(pFlattenedList);

      return pFlattenedList;
   }

   Object*
   List::copy_reverse()
   {
      List* pReversedList = new List();
      pReversedList->resize(this->length);

      LOOP_FROM_TO(UInt64, i, 0, this->length)
      {
         pReversedList->items[i] = this->items[this->length - i - 1];
      }

      return pReversedList;
   }

   bool
   List::destroy(Value pList)
   {
      List::assert((Object*)pList);

      ((List*)pList)->clear();
      ((List*)pList)->items = (Value*)REALLOC(((List*)pList)->items, 0);

      return true;
   }

   Value
   List::get_object_at(UInt64 at)
   {
      ASSERT(
            at < this->length,
            "Index %ld out of range [0:%ld[.",
            (ulong)at,
            (ulong)this->length
      );
      ASSERT(
            T__IS_NOT_LITERAL_TYPE(this->item_type),
            "Cannot use ::get_object_at on a list of literals."
      );
      return this->items[at];
   }

   Value
   List::get_value_at(UInt64 at)
   {
      ASSERT(
            at < this->length,
            "Index %ld out of range [0:%ld[.",
            (ulong)at,
            (ulong)this->length
      );
      return this->items[at];
   }

   void
   List::insert(UInt64 at, Object* obj)
   {
      ASSERT(
            at <= this->length,
            "Index %ld out of range [0:%ld].",
            (ulong)at,
            (ulong)this->length
      );

      if (at == this->length)
      {
         this->push(obj);
      }
      else
      {
         this->resize(this->length + 1);
         for (UInt64 i = this->length - 1 ; i > (at - 1) ; -- i)
         {
            this->items[i] = this->items[i - 1];
         }
         this->items[at] = obj;
         obj->pick();
      }
   }

   void
   List::pop()
   {
      if (this->length > 0)
      {
         if (T__IS_NOT_LITERAL_TYPE(this->item_type))
         {
            ((Object*)this->items[this->length - 1])->drop();
         }
         --this->length;
         this->resize(this->length);
      }
   }

   void
   List::pop(UInt64 num)
   {
      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, i, this->length - num, this->length)
         {
            if (this->items[i] != NULL)
            {
               ((Object*)this->items[i])->drop();
               this->items[i] = NULL;
            }
         }
      }
      this->length = this->length - num;
      this->resize(this->length);
   }

   void
   List::print(Value pObject)
   {
      List::assert((Object*)pObject);

      List* pList = (List*)pObject;

      printf("(");
      if (T__IS_LITERAL_TYPE(pList->item_type))
      {
         // @todo Do something here.
      }
      else
      {
         LOOP_FROM_TO(UInt64, i, 0, pList->length)
         {
            if (i != 0)
            {
               printf(", ");
            }
            vm::Class* pClass = ((Object*)pList->items[i])->klass;
            pClass->print_func(pList->items[i]);
         }
         printf(")");
      }
   }

   void
   List::print_line(Value pObject)
   {
      List::print(pObject);
      printf("\n");
   }

   void
   List::push(Object* obj)
   {
      ASSERT_NOT_NULL(obj);

      this->resize(this->length + 1);
      this->items[this->length - 1] = obj;
      obj->pick();
   }

   void
   List::push_list(List* pAList)
   {
      ASSERT_NOT_NULL(pAList);
      ASSERT(
            this->item_type == pAList->item_type,
            "The list to push must have the same item type (%s != %s).",
            t::cast_type_to_string(this->item_type),
            t::cast_type_to_string(pAList->item_type)
      );
      ASSERT(
            this->item_class == pAList->item_class,
            "The list to push must have the same item class (%x != %x).",
            (uint)this->item_class,
            (uint)pAList->item_class
      );

      UInt64 dwPushAt = this->length;

      this->resize(this->length + pAList->length);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(UInt64, i, 0, pAList->length)
         {
            this->items[dwPushAt + i] = pAList->items[i];
         }
      }
      else
      {
         LOOP_FROM_TO(UInt64, i, 0, pAList->length)
         {
            this->items[dwPushAt + i] = pAList->items[i];
            if (pAList->items[i] != NULL)
            {
               ((Object*)pAList->items[i])->pick();
            }
         }
      }
   }

   void
   List::remove_item(UInt64 at)
   {
      T__LIST__ASSERT_IN_RANGE(this, at);

      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         if (this->items[at] != NULL)
         {
            ((Object*)this->items[at])->drop();
         }
      }

      for (UInt64 pos = at + 1 ; pos < this->length ; ++pos)
      {
         this->items[pos - 1] = this->items[pos];
      }

      this->resize(this->length - 1);
   }

   void
   List::resize(UInt64 size)
   {
      if (size != this->length)
      {
         /**
         if (size < this->length && T__IS_NOT_LITERAL_TYPE(this->item_type))
         {
            LOOP_FROM_TO(UInt64, i, size - 1, this->length)
            {
               if (this->items[i] != NULL)
               {
                  ((Object*)this->items[i])->drop();
               }
            }
         }
         */

         size_t obj_size = sizeof(Value);
         this->items = (Value*)REALLOC(this->items, size * obj_size);
         this->length = size;
      }
   }


   void
   List::set_item(UInt64 at, Object* obj)
   {
      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         if (this->items[at] != NULL)
         {
            ((Object*)this->items[at])->drop();
         }
         obj->pick();
      }
      this->items[at] = obj;
   }

   List*
   List::slice(UInt64 start, UInt64 end, UInt64 step)
   {
      List* pSlice = new List();
      pSlice->item_type = this->item_type;
      pSlice->item_class = this->item_class;
      pSlice->resize((end - start) / step);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         for (UInt64 i = start, j = 0 ; i < end ; i += step, ++j)
         {
            pSlice->items[j] = this->items[i];
         }
      }
      else
      {
         for (UInt64 i = start, j = 0 ; i < end ; i += step, ++j)
         {
            pSlice->items[j] = this->items[i];
            if (pSlice->items[j] != NULL)
            {
               ((Object*)pSlice->items[j])->pick();
            }
         }
      }

      return pSlice;
   }
}

