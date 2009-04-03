#ifndef VM_HEAP
#define VM_HEAP NS_VM::Heap

#include "t/HeapObject.h"
#include "t/Int.h"
#include "t/Object.h"

#define SVM_HEAP_ROOM_STEP 80

namespace NS_VM
{
   class Heap
   {
      public: T_OBJECT** items;
      public: ULong item_count;
      public: ULong last_position;
      public: ULong rooms;

      public: Heap();
      public: ~Heap();
      public: void append(T_OBJECT* obj);
      public: void append(UInt object_count, T_OBJECT** objects);
      public: void clear();
      public: ULong count();
      public: void change_length(ULong length);
      public: T_OBJECT* get(ULong at);
      public: void resize(ULong rooms);
      public: T_OBJECT* pick_last_and_pop();
      public: void pop();
      public: void pop(ULong count);
      public: void replace(ULong count, T_OBJECT* by);
      public: void replace_at(ULong at, T_OBJECT* by);
      public: bool reverse(ULong num);
      public: bool swap();
   };
}

#endif
