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
   List::__delete__ (Value pList)
   {

   }

   Value
   List::__new__ ()
   {
      NEW(pResult, t::List);
      return pResult;
   }

   void
   List::__print__ (Value pLst)
   {
      t::List* pList = (t::List*)pLst;
      switch (pList->item_type)
      {
         case t::BOOL_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pList->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%s", ((bool)pList->items[i]) == 0 ? "False" : "True");
            }
            printf("]");
            break;
         }

         case t::CHAR_TYPE:
         case t::SHORT_TYPE:
         case t::INT_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pList->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%d", (int)pList->items[i]);
            }
            printf("]");
            break;
         }

         case t::U_CHAR_TYPE:
         case t::U_SHORT_TYPE:
         case t::U_INT_TYPE:
         {
            printf("[");
            for (uint i = 0 ; i < pList->length ; ++i)
            {
               if (i != 0) printf(", ");
               printf("%u", (uint)pList->items[i]);
            }
            printf("]");
            break;
         }
      }
   }

   void
   List::__print_line__ (Value pList)
   {
      List::__print__ (pList);
      printf("\n");
   }

   List*
   List::copy()
   {
      List* pCopiedList = new List;
      pCopiedList->item_type = this->item_type;
      pCopiedList->item_class = this->item_class;
      pCopiedList->length = this->length;
      Memory_ALLOC(pCopiedList->items, Value, this->length);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(uint, i, 0, this->length)
         {
            pCopiedList->items[i] = this->items[i];
         }
      }
      else
      {
         LOOP_FROM_TO(uint, i, 0, this->length)
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
         LOOP_FROM_TO(uint, i, 0, this->length)
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

      LOOP_FROM_TO(uint, i, 0, this->length)
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
      Memory_FREE(((List*)pList)->items);

      return true;
   }

   void
   List::insert(uint at, Value obj)
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
         for (uint i = this->length - 1 ; i > (at - 1) ; -- i)
         {
            this->items[i] = this->items[i - 1];
         }
         this->items[at] = obj;
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
   List::pop(uint num)
   {
      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(uint, i, this->length - num, this->length)
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
         LOOP_FROM_TO(uint, i, 0, pList->length)
         {
            if (i != 0)
            {
               printf(", ");
            }
            //vm::Class* pClass = ((Object*)pList->items[i])->klass;
            //pClass->print_func(pList->items[i]);
         }
      }
      printf(")");
   }

   void
   List::print_line(Value pObject)
   {
      List::print(pObject);
      printf("\n");
   }

   void
   List::push(Value pValue)
   {
      this->resize(this->length + 1);
      this->items[this->length - 1] = pValue;
   }

   void
   List::push_list(List* pAList)
   {
      ASSERT_NOT_NULL(pAList);
      ASSERT(
            this->item_type == pAList->item_type,
            "The list to push must have the same item type (%s != %s).",
            t::get_type_name(this->item_type),
            t::get_type_name(pAList->item_type)
      );
      ASSERT(
            this->item_class == pAList->item_class,
            "The list to push must have the same item class (%x != %x).",
            (uint)this->item_class,
            (uint)pAList->item_class
      );

      uint dwPushAt = this->length;

      this->resize(this->length + pAList->length);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         LOOP_FROM_TO(uint, i, 0, pAList->length)
         {
            this->items[dwPushAt + i] = pAList->items[i];
         }
      }
      else
      {
         LOOP_FROM_TO(uint, i, 0, pAList->length)
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
   List::remove_item(uint at)
   {
      T__LIST__ASSERT_IN_RANGE(this, at);

      if (T__IS_NOT_LITERAL_TYPE(this->item_type))
      {
         if (this->items[at] != NULL)
         {
            ((Object*)this->items[at])->drop();
         }
      }

      for (uint pos = at + 1 ; pos < this->length ; ++pos)
      {
         this->items[pos - 1] = this->items[pos];
      }

      this->resize(this->length - 1);
   }

   void
   List::resize(uint size)
   {
      if (size != this->length)
      {
         /**
         if (size < this->length && T__IS_NOT_LITERAL_TYPE(this->item_type))
         {
            LOOP_FROM_TO(uint, i, size - 1, this->length)
            {
               if (this->items[i] != NULL)
               {
                  ((Object*)this->items[i])->drop();
               }
            }
         }
         */

         Memory_REALLOC(this->items, Value, size);
         this->length = size;
      }
   }

   List*
   List::slice(uint start, uint end, uint step)
   {
      List* pSlice = new List();
      pSlice->item_type = this->item_type;
      pSlice->item_class = this->item_class;
      pSlice->resize((end - start) / step);

      if (T__IS_LITERAL_TYPE(this->item_type))
      {
         for (uint i = start, j = 0 ; i < end ; i += step, ++j)
         {
            pSlice->items[j] = this->items[i];
         }
      }
      else
      {
         for (uint i = start, j = 0 ; i < end ; i += step, ++j)
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

