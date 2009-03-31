#include "vm/Heap.h"

namespace NS_VM
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
      for (unsigned int i = 0 ; i < this->item_count ; ++ i)
      {
         T_OBJECT::drop(this->items[i]);
      }
      free(this->items);
   }

   void
   Heap::clear()
   {
      this->change_length(0);
   }

   void
   Heap::append(T_OBJECT* obj)
   {
      ASSERT(obj->cls != svm::heap_object_type, "<heap:%ld> : Cannot store object of type <system.HeapObject>.", (long)this);

      if (this->rooms == this->item_count)
      {
         this->resize(this->rooms + SVM_HEAP_ROOM_STEP);
      }

      ++ this->item_count;
      ++ this->last_position;
      T_OBJECT::pick(obj);
      this->items[this->last_position] = obj;
   }

   void
   Heap::append(UInt object_count, T_OBJECT** objects)
   {
      for (UInt i = 0 ; i < object_count ; ++ i)
      {
         this->append(objects[i]);
      }
   }

   void
   Heap::change_length(ULong length)
   {
      if (length > this->item_count)
      {
         for (ULong i = length ; i < this->item_count ; ++ i)
         {
            T_OBJECT::drop(this->items[i]);
         }
      }
      else
      {
         for (ULong i = this->item_count ; i < length ; ++i)
         {
            this->items[i] = NULL;
         }
      }

      this->last_position = length - 1;
      this->item_count = length;
   }

   ULong
   Heap::count()
   {
      return this->item_count;
   }

   T_OBJECT*
   Heap::get(ULong at)
   {
      ASSERT(at < this->item_count, "<heap@x%x>: Index [%lu] out of range [0 .. %lu].\n", (UInt)this, at, this->item_count);
      T_OBJECT* result = this->items[this->last_position - at];
      T_OBJECT::pick(result);

      ASSERT(result != svm::heap_object_type, "<heap@x%x> cannot return <system.HeapObject> objects.\n", (UInt)this);

      return result;
   }

   T_OBJECT*
   Heap::pick_last_and_pop()
   {
      T_OBJECT* result = this->get(0);
      T_OBJECT::pick(result);
      this->pop(1);
      return result;
   }

   void
   Heap::pop()
   {
      this->pop(1);
   }

   void
   Heap::pop(ULong count)
   {
      if (this->item_count > 0)
      {
         if (count > this->item_count) count = this->item_count;

         for (ULong i = 0 ; i < count ; ++ i)
         {
            T_OBJECT::drop(this->items[this->last_position - i]);
            this->items[this->last_position - i] = NULL;
         }

         this->item_count -= count;
         this->last_position -= count;

         if (this->rooms - SVM_HEAP_ROOM_STEP > this->item_count)
         {
            this->resize(this->rooms - SVM_HEAP_ROOM_STEP);
         }
      }
   }

   void
   Heap::replace(ULong count, T_OBJECT* by)
   {
      ASSERT(this->item_count >= count, "Cannot replace more than items in the heap.");
      ASSERT_NOT_NULL(by);

      ULong new_length = this->item_count - count + 1;
      this->change_length(new_length);
      this->replace_at(0, by);
   }

   void
   Heap::replace_at(ULong at, T_OBJECT* by)
   {
      ULong pos = this->last_position - at;
      T_OBJECT::pick(by);
      CHECK(by != this->items[pos], "You should not try to replace an object by itself.\n");
      T_OBJECT::drop(this->items[pos]);
      this->items[pos] = by;
   }

   void
   Heap::resize(ULong rooms)
   {
      INTERNAL(
         "<heap:%lu> : Resizing from <%ld> rooms to <%ld>. (@%ld + %ld b)\n",
         (ULong)this,
         this->rooms,
         rooms,
         (ULong)this->items,
         sizeof(T_OBJECT*) * rooms
      );
      this->items = (T_OBJECT**)REALLOC(this->items, sizeof(T_OBJECT*) * rooms);
      ASSERT_REALLOC(this->items);
      for (ULong i = this->rooms ; i < rooms ; ++i)
      {
         // @TODO: SVM_DROP ? probably...
         this->items[i] = NULL;
      }
      this->rooms = rooms;
   }

   bool
   Heap::reverse(ULong num)
   {
      bool result;
      if (this->item_count >= num)
      {
         T_OBJECT* tmp = NULL;
         ULong i_max = num % 2 == 0 ? num / 2 : (num - 1) / 2;
         --num;
         for (ULong i = 0 ; i < i_max ; ++i)
         {
            tmp = this->items[this->last_position - num + i];
            this->items[this->last_position - num + i] = this->items[this->last_position - i];
            T_OBJECT::pick(this->items[this->last_position - i]);
            this->items[this->last_position - i] = tmp;
         }
         result = true;
      }
      else
      {
         result = false;
      }
      return result;
   }

   bool
   Heap::swap()
   {
      bool result;
      if (this->item_count > 1)
      {
         T_OBJECT* last = this->items[this->last_position];
         T_OBJECT::pick(last);
         this->items[this->last_position] = this->items[this->last_position - 1];
         this->items[this->last_position - 1] = last;
         T_OBJECT::drop(last);
         result = true;
      }
      else
      {
         result = false;
      }
      return result;
   }
}
