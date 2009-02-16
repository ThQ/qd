#ifndef SVM_FIELD_TABLE_H
#define SVM_FIELD_TABLE_H

#include "memory.h"
#include "svm/Variable.h"
#include "types.h"

#define SVM_FIELD_TABLE_DEFAULT_ROOM_COUNT 10

namespace svm
{
   class FieldTable
   {
      public: svm::Variable** fields;
      public: ULong field_count;
      public: ULong field_room;

      public: FieldTable();
      public: ~FieldTable();

      public: void append(svm::Variable* var);
      public: void clear();
      public: void clear_range(ULong from, ULong to);
      public: void resize_down(ULong new_size);
      public: void resize_up(ULong new_size);
      public: void set_fields(ULong count, Variable** fields);
   };
}

#endif
