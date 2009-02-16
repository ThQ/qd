#include "svm/FieldTable.h"

namespace svm
{
   FieldTable::FieldTable()
   {
      this->field_count = 0;
      this->field_room = 0;
      this->fields = 0;
   }

   FieldTable::~FieldTable()
   {
      this->clear();
      delete[] this->fields;
   }

   void
   FieldTable::append(svm::Variable* var)
   {
      ++ this->field_count;
      if (this->field_room < this->field_count)
      {
         this->resize_up(this->field_room + SVM_FIELD_TABLE_DEFAULT_ROOM_COUNT);
      }
      SVM_PICK(var);
      this->fields[this->field_count - 1] = var;
   }

   void
   FieldTable::clear()
   {
      for(ULong i = 0 ; i < this->field_count ; ++i)
      {
         SVM_DROP(this->fields[i]);
         this->fields[i] = NULL;
      }
   }

   void
   FieldTable::clear_range(ULong from, ULong to)
   {
      ASSERT(to < this->field_count, "Range exceeds actual field count.");
      for (ULong i = from ; i < to ; ++i)
      {
         SVM_DROP(this->fields[i]);
         this->fields[i] = NULL;
      }
   }

   void
   FieldTable::resize_down(ULong new_size)
   {
      ASSERT(new_size < this->field_room, "New size should be lower than %lu.", this->field_room);

      if (new_size < this->field_count)
      {
         for (ULong i = new_size ; i < this->field_count ; ++i)
         {
            SVM_DROP(this->fields[i]);
         }
      }
      this->field_count = new_size;
      this->field_room = new_size;
      this->fields = (svm::Variable**)REALLOC(this->fields, new_size * sizeof(svm::Variable*));
   }

   void
   FieldTable::resize_up(ULong new_size)
   {
      ASSERT(new_size > this->field_room, "New size should be higher than %lu.", this->field_room);

      this->field_room = new_size;
      this->fields = (svm::Variable**)REALLOC(this->fields, new_size * sizeof(svm::Variable*));
   }

   void
   FieldTable::set_fields(ULong count, Variable** fields)
   {
      if(count > this->field_room)
      {
         this->resize_up(count);
      }

      for (ULong i = 0 ; i < count ; ++i)
      {
         SVM_DROP_SAFE(this->fields[i]);
         this->fields[i] = fields[i];
         SVM_PICK_SAFE(this->fields[i]);
      }
   }

      /*
      bool result = false;

      if (count < this->field_count)
      {
         for (unsigned long i = this->field_count; i < count ; ++i)
         {
            SVM_ASSERT_VARIABLE(this->fields[i]);
            SVM_DROP(this->fields[i]);
            this->fields[i] = NULL;
         }
      }

      this->fields = (Variable**)realloc(this->fields, sizeof(Variable*) * count);
      ASSERT_REALLOC(this->fields);
      if (this->fields != NULL)
      {
         result = true;
         this->field_count = count;

         for (unsigned long i = 0 ; i < count ; ++i)
         {
            SVM_ASSERT_VARIABLE(this->fields[i]);
            SVM_DROP(this->fields[i]);
            this->fields[i] = fields[i];
            SVM_PICK(fields[i]);
         }
      }    
      return result; 
   }
   */
}
