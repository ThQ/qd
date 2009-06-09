#include "t/Array.h"

namespace t
{
   Array::Array ()
   {
      this->type = NULL;
      this->items = NULL;
      this->item_count = 0;
      this->set_class(NS_TYPE::tARRAY);
   }

   Array::~Array ()
   {
      T_OBJECT::assert_not_null(this->type);

      T_OBJECT::drop(this->type);
      for (ULong item_index = 0 ; item_index < this->item_count ; ++item_index)
      {
         T_OBJECT::assert_not_null(this->items[item_index]);
         T_OBJECT::drop(this->items[item_index]);
         this->items[item_index] = NULL;
      }
   }

   T_OBJECT*
   Array::build (T_OBJECT* type, T_OBJECT* len)
   {
      return Array::build(type, ((T_INT*)len)->value);
   }

   T_OBJECT*
   Array::build (T_OBJECT* type, ULong array_length)
   {
      T_OBJECT::assert_not_null(type);

      Array* result = new Array();
      Array::set_type(result, type);
      result->size(array_length);

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Array::build (T_OBJECT* type, ULong len, T_OBJECT** items)
   {
      T_OBJECT::assert_not_null(type);
      // ASSERT(len != 0, "Length should not be 0.");

      Array* result = new Array();
      Array::set_type(result, type);
      result->item_count = len;
      result->items = items;

      for (ULong item_index = 0 ; item_index < len ; ++ item_index)
      {
         T_OBJECT::pick(items[item_index]);
      }

      return (T_OBJECT*)result;
   }

   void
   Array::clear ()
   {
      for (ULong item_index = 0 ; item_index < this->item_count ; ++item_index)
      {
         T_OBJECT::drop_safe(this->items[item_index]);
         T_OBJECT::pick(NS_TYPE::gNULL);
         this->items[item_index] = NS_TYPE::gNULL;
      }
   }

   void
   Array::clear_item (ULong item_index)
   {
      CHECK(item_index >= this->item_count, "Index out of range.");

      T_OBJECT::drop_safe(this->items[item_index]);
      T_OBJECT::pick(NS_TYPE::gNULL);
      this->items[item_index] = NS_TYPE::gNULL;
   }

   void
   Array::clear_range (ULong range_start, ULong range_end)
   {
      ASSERT(range_start < range_end, "Start index must be lower than end index.");
      ASSERT(range_end < this->item_count - 1, "End index must be lower than the item count.");

      for (ULong item_index = range_start ; item_index < range_end ; item_index ++)
      {
         T_OBJECT::assert_not_null(this->items[item_index]);
         T_OBJECT::drop(this->items[item_index]);
         T_OBJECT::pick(t::gNULL);
         this->items[item_index] = t::gNULL;
      }
   }

   void
   Array::set_item (ULong item_index, T_OBJECT* new_item)
   {
      T_OBJECT::assert_not_null(new_item);
      T_OBJECT::drop(this->items[item_index]);
      T_OBJECT::pick(new_item);
      this->items[item_index] = new_item;
   }

   void
   Array::set_type (T_CLASS* type)
   {
      t::Class::assert(type);
      T_OBJECT::drop_safe(this->type);
      T_OBJECT::pick(type);
      this->type = type;
   }

   void
   Array::size (ULong array_size)
   {
      // A 0-length array may be useful : A function may want to return an empty array.
      // ASSERT(array_size != 0, "An Array of 0-length must not be created.");

      this->item_count = array_size;
      this->items = (T_OBJECT**)MALLOC(sizeof(T_OBJECT*) * array_size);

      for (ULong item_index = 0 ; item_index < array_size ; item_index ++)
      {
         this->items[item_index] = t::gNULL;
         T_OBJECT::pick(t::gNULL);
      }
   }

   T_OBJECT* tARRAY = NULL;
}


