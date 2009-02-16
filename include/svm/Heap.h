#ifndef SVM_HEAP_H
#define SVM_HEAP_H

#include "debug.h"
#include "svm/HeapObject.h"
#include "svm/Int.h"
#include "svm/Object.h"

#define SVM_HEAP_ROOM_STEP 80

namespace svm
{
   class Heap
   {
      public: Object** items;
      public: ULong item_count;
      public: ULong last_position;
      public: ULong rooms;

      public: Heap();
      public: ~Heap();
      public: void append(Object* obj);
      public: void append(unsigned int object_count, Object** objects);
      public: void clear();
      public: unsigned long int count();
      public: void change_length(ULong length);
      public: Object* get(ULong at);
      public: void resize(unsigned long rooms);
      public: Object* pick_last_and_pop();
      public: void pop();
      public: void pop(unsigned long int count);
      public: void replace(ULong count, Object* by);
      public: void replace_at(ULong at, Object* by);
      public: bool reverse(unsigned long num);
      public: bool swap();
   };
}


#endif

