#include "vm/Heap.h"

namespace vm
{
   Heap::Heap()
   {
      this->items = NULL;
      this->item_count = 0;
      this->rooms = 0;
      this->last_position = -1;
      //this->resize(SVM_HEAP_ROOM_STEP);
   }

   Heap::~Heap()
   {
      LOOP_FROM_TO(uint, i, 0, this->item_count)
      {
         if (this->items[i] != NULL)
         {
            this->items[i]->drop();
         }
      }
      free(this->items);
   }

   void
   Heap::append(T_OBJECT* obj)
   {
      // ASSERT(obj->cls != t::tHEAP_OBJECT, "<heap:%ld> : Cannot store object of type <system.HeapObject>.", (long)this);

      if (this->rooms == this->item_count)
      {
         this->resize_up();
         //this->resize(this->rooms + SVM_HEAP_ROOM_STEP);
      }

      ++ this->item_count;
      ++ this->last_position;
      obj->pick();
      this->items[this->last_position] = obj;
   }

   void
   Heap::append(uint object_count, T_OBJECT** objects)
   {
      LOOP_FROM_TO(uint, i, 0, object_count)
      {
         this->append(objects[i]);
      }
   }

   void
   Heap::clear()
   {
      LOOP_FROM_TO(uint, i, 0, this->item_count)
      {
         if (this->items[i] != NULL) this->items[i]->drop();
         this->items[i] = NULL;
      }
      this->last_position = 0;
      this->item_count = 0;
   }

   uint
   Heap::count()
   {
      return this->item_count;
   }

   t::Object*
   Heap::get(uint at)
   {
      ASSERT(
            at < this->item_count,
            "<Heap @x%x>: INDEX_OUT_OF_RANGE (.from %lu, .to %lu)\n",
            (uint)this,
            at,
            this->item_count
      );
      t::Object* result = this->items[this->last_position - at];

      // ASSERT(result != t::tHEAP_OBJECT, "<heap@x%x> cannot return <system.HeapObject> objects.\n", (UInt)this);

      return result;
   }

   t::Object*
   Heap::pick_last_and_pop()
   {
      t::Object* result = this->get(0);
      result->pick();
      this->pop(1);
      return result;
   }

   void
   Heap::pop(uint count)
   {
      ASSERT(
            this->item_count > count,
            "<Heap @x%x> CANNOT_POP_MORE_THAN_IN_THE_HEAP (.real %lu, .expected %lu)",
            this->item_count,
            count
      )

      if (this->item_count > 0)
      {
         //if (count > this->item_count) count = this->item_count;

         LOOP_FROM_TO(uint, i, 0, count)
         {
            this->items[this->last_position - i]->drop();
            this->items[this->last_position - i] = NULL;
         }

         this->item_count -= count;
         this->last_position -= count;
      }
   }

   void
   Heap::replace_at(uint nAt, t::Object* pReplacement)
   {
      uint nPos = this->last_position - at;
      pReplacement->pick();
      this->items[nPos]->drop();
      this->items[pos] = by;

      CHECK(
            pReplacement != this->items[nPos],
            "<Heap @x%x> REPLACING_AN_OBJECT_BY_ITSELF (.at %lu, .object %u)\n",
            (uint)this,
            nAt,
            (uint)pReplacement
      );
   }

   void
   Heap::resize(uint nRooms)
   {
      INTERNAL(
         "<Heap @x%x> RESIZING (.from %ld, .to %ld)\n",
         (uint)this,
         this->rooms,
         rooms
      );

      this->items = (t::Object**)REALLOC(this->items, T__OBJECT__SIZEOF_PTR * rooms);
      ASSERT_REALLOC(this->items);

      LOOP_FROM_TO(uint, i, this->rooms, nRooms)
      {
         if (this->items[i] != NULL) this->items[i]->drop();
         this->items[i] = NULL;
      }
      this->rooms = rooms;
   }

   bool
   Heap::reverse(uint nNum)
   {
      CHECK(
            "<Heap @x%x> TRYING_TO_REVERSE_MORE_THAN_IN_THE_HEAP"
            (uint)this
      )

      if (this->item_count >= nNum)
      {
         t::Object* pTmp = NULL;
         uint i_max = nNum % 2 == 0 ? nNum / 2 : (nNum - 1) / 2;
         --nNum;

         LOOP_FROM_TO(uint, i, 0, i_max)
         {
            pTmp = this->items[this->last_position - nNum + i];
            this->items[this->last_position - nNum + i] = this->items[this->last_position - i];
            this->items[this->last_position - i]->pick();
            this->items[this->last_position - i] = pTmp;
         }
      }
   }

   void
   Heap::swap()
   {
      CHECK(
            "<Heap @x%x> SWAPING_WITH_ONLY_ONE_ITEM"
            (uint)this
      );

      if (this->item_count > 1)
      {
         t::Object* pLastObj = this->items[this->last_position];
         this->items[this->last_position] = this->items[this->last_position - 1];
         this->items[this->last_position - 1] = pLastObj;
      }
   }
}
