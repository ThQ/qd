#include "svm/Array.h"

namespace svm
{
   Array::Array()
   {
      this->type = NULL;
      this->items = NULL;
      this->item_count = 0;
      this->set_class(svm::array_type);
   }

   Array::~Array()
   {
      SVM_DROP_SAFE(this->type);
      for (ULong i = 0 ; i < this->item_count ; ++i)
      {
         SVM_DROP(this->items[i]);
         this->items[i] = NULL;
      }
   }

   Object*
   Array::build(Object* type, Object* len)
   {
      return Array::build(type, ((svm::Int*)len)->value);
   }

   Object*
   Array::build(Object* type, ULong len)
   {
      CHECK_NOT_NULL(type);

      Array* result = new Array();
      result->type = type;
      SVM_PICK(type);
      result->item_count = len;
      result->items = (Object**)MALLOC(sizeof(Object*) * len);
      Array::clear(result);

      return (Object*)result;
   }

   Object*
   Array::build(Object* type, ULong len, Object** obj)
   {
      CHECK_NOT_NULL(type);
      CHECK_NOT_NULL(obj);
      CHECK(len != 0, "Length should not be 0.");

      Array* result = new Array();
      result->type = type;
      SVM_PICK(type);
      result->item_count = len;
      result->items = obj;

      for (ULong i = 0 ; i < len ; ++ i)
      {
         SVM_PICK(obj[i]);
      }

      return (Object*)result;
   }

   void
   Array::clear(Array* arr)
   {
      CHECK_NOT_NULL(svm::Null);
      CHECK_NOT_NULL(arr);

      ULong i_max = arr->item_count;
      for (ULong i = 0 ; i < i_max ; ++i)
      {
         arr->items[i] = svm::Null;
         SVM_PICK(svm::Null);
      }
   }

   void
   Array::clear_item(Array* arr, ULong at)
   {
      CHECK_NOT_NULL(arr);
      CHECK(at >= arr->item_count, "Index out of range.");
      CHECK_NOT_NULL(arr->items[at]);

      SVM_PICK(svm::Null);
      SVM_DROP(arr->items[at]);
      arr->items[at] = svm::Null;
   }

   void
   Array::clear_range(Array* arr, ULong start, ULong end)
   {
      for (ULong i = start ; i < end ; ++i)
      {
         SVM_DROP_SAFE(arr->items[i]);
         arr->items[i] = svm::Null;
         SVM_PICK(svm::Null);
      }
   }

   void
   Array::set_item(Array* arr, ULong at, Object* obj)
   {
      CHECK_NOT_NULL(arr);
      CHECK_NOT_NULL(obj);
      CHECK(at >= arr->item_count, "Index out of range.");
      CHECK_NOT_NULL(arr->items[at]);

      SVM_PICK(obj);
      SVM_DROP(arr->items[at]);
      arr->items[at] = obj;
   }

   Object* array_type = NULL;
}


