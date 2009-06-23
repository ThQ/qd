#include "t/List.h"

namespace t
{
   T_OBJECT* tLIST = NULL;

   List::List()
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::LIST_TYPE;

      this->fpDestroy = t::List::destroy;
      this->fpPrint = t::List::print;
      this->fpPrintLine = t::List::print_line;
   }

   void
   List::clear()
   {
      LOOP_FROM_TO (UInt64, i, 0, this->length)
      {
         if (this->items[i] != NULL)
         {
            this->items[i]->drop();
         }
         this->items[i] = NULL;
      }
      this->items = (T_OBJECT**)REALLOC(this->items, 0);
   }

   bool
   List::destroy(Object* pList)
   {
      List::assert(pList);

      ((List*)pList)->clear();

      return true;
   }

   List*
   List::flatten()
   {
      List* pFlattenedList = new List;

      LOOP_FROM_TO(UInt64, i, 0, this->length)
      {
         if (this->items[i]->type == t::LIST_TYPE)
         {
            pFlattenedList->push_list(((List*)this->items[i])->flatten());
         }
         else
         {
            pFlattenedList->push(this->items[i]);
         }
      }
      return pFlattenedList;
   }

   Object*
   List::get_item(UInt64 at)
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
      --this->length;
      this->resize(this->length);
   }

   void
   List::pop(UInt64 num)
   {
      for (UInt64 i = this->length - num ; i < this->length ; ++i)
      {
         if (this->items[i] != NULL)
         {
            this->items[i]->drop();
            this->items[i] = NULL;
         }
      }
      this->length = this->length - num;
      this->resize(this->length);
   }

   void
   List::print(Object* pObject)
   {
      List::assert(pObject);

      List* pList = (List*)pObject;

      printf("(");
      LOOP_FROM_TO(UInt64, i, 0, pList->length)
      {
         if (i != 0)
         {
            printf(", ");
         }
         pList->items[i]->fpPrint(pList->items[i]);
      }
      printf(")");
   }

   void
   List::print_line(Object* pObject)
   {
      List::print(pObject);
      printf("\n");
   }

   void
   List::push(Object* obj)
   {
      ASSERT_NOT_NULL(obj);

      this->resize(this->length + 1);
      this->items[this->length -1] = obj;
      obj->pick();
   }

   void
   List::push_list(List* pAList)
   {
      ASSERT_NOT_NULL(pAList);

      UInt64 dwPushAt = this->length;

      this->resize(this->length + pAList->length);

      LOOP_FROM_TO(UInt64, i, 0, pAList->length)
      {
         this->items[dwPushAt + i] = pAList->items[i];
         if (pAList->items[i] != NULL)
         {
            pAList->items[i]->pick();
         }
      }
   }

   void
   List::remove_item(UInt64 at)
   {
      if (this->items[at] != NULL)
      {
         this->items[at]->drop();
         this->items[at] = NULL;
      }
      for (UInt64 pos = at + 1 ; pos < (this->length - 1) ; ++pos)
      {
         this->items[pos - 1] = this->items[pos];
      }
      this->resize(this->length - 1);
   }

   Object*
   List::reverse()
   {
      List* pReversedList = new List();
      pReversedList->resize(this->length);

      LOOP_FROM_TO(UInt64, i, 0, this->length)
      {
         pReversedList->items[i] = this->items[this->length - i - 1];
      }

      return pReversedList;
   }

   void
   List::resize(UInt64 size)
   {
      if (size != this->length)
      {
         if (size < this->length)
         {
            LOOP_FROM_TO(UInt64, i, size, this->length)
            {
               if (this->items[i] != NULL)
               {
                  this->items[i]->drop();
               }
            }
         }

         size_t obj_size = sizeof(T_OBJECT*);
         this->items = (T_OBJECT**)REALLOC(this->items, size * obj_size);
         ASSERT_REALLOC(this->items);
         this->length = size;
      }
   }


   void
   List::set_item(UInt64 at, Object* obj)
   {
      if (this->items[at] != NULL)
      {
         this->items[at]->drop();
      }
      this->items[at] = obj;
      obj->pick();
   }

   List*
   List::slice(UInt64 start, UInt64 end, UInt64 step)
   {
      List* pSlice = new List();

      for (UInt64 i = start ; i < end ; i += step)
      {
         pSlice->push(this->items[i]);
      }

      return pSlice;
   }
}

