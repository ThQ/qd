#ifndef SVM_FIELD_TABLE_H
#define SVM_FIELD_TABLE_H

#include "t/Variable.h"

#define SVM_FIELD_TABLE_DEFAULT_ROOM_COUNT 10

namespace NS_VM
{
   class FieldTable
   {
      public: t::Variable** fields;
      public: ULong field_count;
      public: ULong field_room;

      public: FieldTable();
      public: ~FieldTable();

      public: void append(t::Variable* var);
      public: void clear();
      public: void clear_range(ULong from, ULong to);
      public: void resize_down(ULong new_size);
      public: void resize_up(ULong new_size);
      public: void set_fields(ULong count, t::Variable** fields);
   };
}

#endif
