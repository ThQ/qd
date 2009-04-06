#include "t/Array.h"

namespace NS_TYPE
{
   Array::Array()
   {
      this->type = NULL;
      this->items = NULL;
      this->item_count = 0;
      this->set_class(NS_TYPE::tARRAY);
   }

   Array::~Array()
   {
      T_OBJECT::assert_not_null(this->type);

      T_OBJECT::drop(this->type);
      for (ULong i = 0 ; i < this->item_count ; ++i)
      {
         T_OBJECT::assert_not_null(this->items[i]);
         T_OBJECT::drop(this->items[i]);
         this->items[i] = NULL;
      }
   }

   T_OBJECT*
   Array::build(T_OBJECT* type, T_OBJECT* len)
   {
      return Array::build(type, ((T_INT*)len)->value);
   }

   T_OBJECT*
   Array::build(T_OBJECT* type, ULong len)
   {
      T_OBJECT::assert_not_null(type);

      Array* result = new Array();
      Array::set_type(result, type);
      result->item_count = len;
      result->items = (T_OBJECT**)MALLOC(sizeof(T_OBJECT*) * len);
      Array::clear(result);

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Array::build(T_OBJECT* type, ULong len, T_OBJECT** items)
   {
      T_OBJECT::assert_not_null(type);
      ASSERT(len != 0, "Length should not be 0.");

      Array* result = new Array();
      Array::set_type(result, type);
      result->item_count = len;
      result->items = items;

      for (ULong i = 0 ; i < len ; ++ i)
      {
         T_OBJECT::pick(items[i]);
      }

      return (T_OBJECT*)result;
   }

   void
   Array::clear(T_OBJECT* obj)
   {
      Array::assert(obj);

      Array* arr = (Array*)obj;

      ULong i_max = arr->item_count;
      for (ULong i = 0 ; i < i_max ; ++i)
      {
         T_OBJECT::drop_safe(arr->items[i]);
         arr->items[i] = NS_TYPE::gNULL;
         T_OBJECT::pick(NS_TYPE::gNULL);
      }
   }

   void
   Array::clear_item(T_OBJECT* obj, ULong at)
   {
      Array::assert(obj);

      Array* arr = (Array*)obj;
      CHECK(at >= arr->item_count, "Index out of range.");

      T_OBJECT::drop_safe(arr->items[at]);
      arr->items[at] = NS_TYPE::gNULL;
      T_OBJECT::pick(NS_TYPE::gNULL);
   }

   void
   Array::clear_range(T_OBJECT* obj, ULong start, ULong end)
   {
      Array::assert(obj);

      Array* arr = (Array*)obj;
      ASSERT(start < end, "Start index must be lower than end index.");
      ASSERT(end < arr->item_count - 1, "End index must be lower than the item count.");

      for (ULong i = start ; i < end ; ++i)
      {
         T_OBJECT::assert_not_null(arr->items[i]);
         T_OBJECT::drop(arr->items[i]);
         arr->items[i] = NS_TYPE::gNULL;
         T_OBJECT::pick(NS_TYPE::gNULL);
      }
   }

   void
   Array::set_item(T_OBJECT* obj, ULong at, T_OBJECT* item)
   {
      Array::assert(obj);
      Array* arr = (Array*)obj;

      ASSERT(at >= arr->item_count, "Index out of range.");
      T_OBJECT::assert_not_null(arr->items[at]);

      T_OBJECT::pick(item);
      T_OBJECT::drop(arr->items[at]);
      arr->items[at] = item;
   }

   void
   Array::set_type(T_OBJECT* obj, T_OBJECT* type)
   {
      Array::assert(obj);

      Array* arr = (Array*)obj;
      T_OBJECT::drop_safe(arr->type);
      T_OBJECT::pick(type);
      arr->type = type;
   }

   T_OBJECT* tARRAY = NULL;
}


