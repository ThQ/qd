#include "svm/Heap.h"

namespace svm
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
         SVM_DROP(this->items[i]);
      }
      free(this->items);
   }

   void
   Heap::clear()
   {
      this->change_length(0);
   }

   void
   Heap::append(Object* obj)
   {
      ASSERT(obj->cls != svm::heap_object_type, "<heap:%ld> : Cannot store object of type <system.HeapObject>.", (long int)this);

      if (this->rooms == this->item_count)
      {
         this->resize(this->rooms + SVM_HEAP_ROOM_STEP);
      }

      ++ this->item_count;
      ++ this->last_position;
      this->items[this->last_position] = obj;
      SVM_PICK(this->items[this->last_position]);
   }

   void
   Heap::append(UInt object_count, Object** objects)
   {
      for (UInt i = 0 ; i < object_count ; ++ i)
      {
         this->append(objects[i]);
      }
   }

   void
   Heap::change_length(ULong length)
   {
      for (ULong i = 0 ; i < length ; ++ i)
      {
         SVM_DROP(this->items[i]);
      }
      this->last_position = length - 1;
      this->item_count = length;
   }

   ULong
   Heap::count()
   {
      return this->item_count;
   }

   Object*
   Heap::get(ULong at)
   {
      ASSERT(at < this->item_count, "<heap@x%x>: Index [%lu] out of range [0 .. %lu].\n", (UInt)this, at, this->item_count);
      Object* result = this->items[this->last_position - at];
      SVM_PICK(result);

      ASSERT(result != svm::heap_object_type, "<heap@x%x> cannot return <system.HeapObject> objects.\n", (UInt)this);

      return result;
   }

   Object*
   Heap::pick_last_and_pop()
   {
      svm::Object* result = this->get(0);
      SVM_PICK(result);
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
            SVM_DROP(this->items[this->last_position - i]);
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
   Heap::replace(ULong count, Object* by)
   {
      ASSERT(this->item_count >= count, "Cannot replace more than items in the heap.");
      ASSERT_NOT_NULL(by);

      ULong new_length = this->item_count - count + 1;
      this->change_length(new_length);
      this->replace_at(0, by);
   }

   void
   Heap::replace_at(ULong at, Object* by)
   {
      ULong pos = this->last_position - at;
      SVM_PICK(by);
      svm::Object* old = this->items[pos];
      SVM_DROP(old);
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
         sizeof(Object*) * rooms
      );
      this->items = (Object**)REALLOC(this->items, sizeof(Object*) * rooms);
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
         Object* tmp = NULL;
         ULong i_max = num % 2 == 0 ? num / 2 : (num - 1) / 2;
         --num;
         for (ULong i = 0 ; i < i_max ; ++i)
         {
            tmp = this->items[this->last_position - num + i];
            this->items[this->last_position - num + i] = this->items[this->last_position - i];
            SVM_PICK(this->items[this->last_position - i]);
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
         Object* last = this->items[this->last_position];
         SVM_PICK(last);
         this->items[this->last_position] = this->items[this->last_position - 1];
         this->items[this->last_position - 1] = last;
         SVM_DROP(last);
         result = true;
      }
      else
      {
         result = false;
      }
      return result;
   }
}
