#ifndef SVM_ARRAY_H
#define SVM_ARRAY_H

#include "debug.h"
#include "memory.h"
#include "svm/Int.h"
#include "svm/Object.h"
#include "types.h"

namespace svm
{
   extern Object* array_type;

   class Array: public Object
   {
      public: Object* type;
      public: Object** items;
      public: ULong item_count;

      public: Array();
      public: ~Array();
      public: static Object* build(Object* type, Object* len);
      public: static Object* build(Object* type, ULong len);
      public: static Object* build(Object* type, ULong len, Object** items);
      public: static void clear(Array* arr);
      public: static void clear_item(Array* arr, ULong at);
      public: static void clear_range(Array* arr, ULong start, ULong end);
      public: static void set_item(Array* arr, ULong at, Object* obj);
   };
}

#endif
