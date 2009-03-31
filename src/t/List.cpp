#include "t/List.h"

namespace NS_TYPE
{
   T_OBJECT* tLIST = NULL;

   List::List()
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->set_class(NS_TYPE::tLIST);
   }

   T_OBJECT*
   List::append(T_OBJECT* list, T_OBJECT* obj)
   {
      DEPRECATED();
      List::assert(list);
      T_OBJECT::assert_not_null(obj);

      List* l = (List*)list;
      List::resize(l, l->length + 1);
      l->items[l->length -1] = obj;
      return (T_OBJECT*)l;
   }

   T_OBJECT*
   List::build()
   {
      return (T_OBJECT*)new List();
   }

   T_OBJECT*
   List::clear(T_OBJECT* list)
   {
      List::assert(list);

      List* l = (List*)list;

      for (UInt i = 0 ; i < l->length ; ++ i)
      {
         T_OBJECT::drop(l->items[i]);
         l->items[i] = NS_TYPE::gNULL;
         T_OBJECT::pick(NS_TYPE::gNULL);
      }
      l->items = (T_OBJECT**)REALLOC(l->items, 0);
      return (T_OBJECT*)l;
   }

   T_OBJECT*
   List::flatten(T_OBJECT* list)
   {
      List::assert(list);

      List* base = (List*)list;
      List* dest = (List*)List::build();

      for (UInt i = 0 ; i < base->length ; ++i)
      {
         if (base->items[i]->cls == NS_TYPE::tLIST)
         {
            List::push_list((T_OBJECT*)dest, List::flatten(base->items[i]));
         }
         else
         {
            List::push((T_OBJECT*)dest, base->items[i]);
         }
      }
      return (T_OBJECT*)dest;
   }

   T_OBJECT*
   List::get_item(T_OBJECT* list, UInt at)
   {
      List::assert(list);
      return ((List*)list)->items[at];
   }

   T_OBJECT*
   List::insert(T_OBJECT* list, UInt at, T_OBJECT* obj)
   {
      List::assert(list);
      List* l = (List*)list;

      if (at == l->length)
      {
         List::append(list, obj);
      }
      else
      {
         List::resize(l, l->length + 1);
         for (UInt i = l->length - 1 ; i > (at - 1) ; -- i)
         {
            l->items[i] = l->items[i - 1];
         }
         l->items[at] = obj;
         T_OBJECT::pick(obj);
      }

      return (T_OBJECT*)l;
   }

   T_OBJECT*
   List::pop(T_OBJECT* self)
   {
      List::assert(self);

      List* l = (List*)self;
      T_OBJECT::pick(l);
      --l->length;
      T_OBJECT* result = l->items[l->length];
      List::resize(self, l->length);
      T_OBJECT::drop(l);
      return result;
   }

   T_OBJECT*
   List::pop(T_OBJECT* self, UInt num)
   {
      List::assert(self);

      List* l = (List*)self;
      T_OBJECT::pick(l);
      T_OBJECT* result = l->items[l->length - 1];
      T_OBJECT::pick(result);

      for (UInt i = l->length - num ; i < l->length ; ++i)
      {
         T_OBJECT::drop(l->items[i]);
         l->items[i] = NULL;
      }
      l->length = l->length - num;
      List::resize(l, l->length);
      T_OBJECT::drop(l);
      return result;
   }

   T_OBJECT*
   List::push(T_OBJECT* list, T_OBJECT* obj)
   {
      List::assert(list);
      T_OBJECT::assert_not_null(obj);

      List* l = (List*)list;
      List::resize(l, l->length + 1);
      l->items[l->length -1] = obj;
      return (T_OBJECT*)l;
   }

   void
   List::push_list(T_OBJECT* l1, T_OBJECT* l2)
   {
      List::assert(l1);
      List::assert(l2);

      List* base = (List*)l1;
      List* ext = (List*)l2;
      UInt base_len = base->length;

      List::resize(l1, base->length + ext->length);

      for (UInt i = 0 ; i < ext->length ; ++i)
      {
         base->items[base_len + i] = ext->items[i];
      }
   }

   T_OBJECT*
   List::remove_item(T_OBJECT* list, UInt at)
   {
      List::assert(list);

      List* l = (List*)list;

      T_OBJECT::drop(l->items[at]);
      l->items[at] = 0;
      for (UInt pos = at + 1 ; pos < (l->length - 1) ; ++pos)
      {
         l->items[pos] = l->items[pos + 1];
      }
      return List::resize((T_OBJECT*)l, l->length - 1);
   }

   T_OBJECT*
   List::reverse(T_OBJECT* list)
   {
      List::assert(list);

      List* src = (List*)list;
      List* dest = (List*)List::build();
      List::resize((T_OBJECT*)dest, src->length);

      for (UInt i = 0 ; i < src->length ; ++i)
      {
         dest->items[i] = src->items[src->length - i - 1];
      }

      return (T_OBJECT*)dest;
   }

   T_OBJECT*
   List::resize(T_OBJECT* list, UInt size)
   {
      List::assert(list);

      List* l = (List*)list;

      if (size != l->length)
      {
         if (size < l->length)
         {
            for (UInt i = size ; i < l->length ; ++ i)
            {
               T_OBJECT::drop(l->items[i]);
            }
         }

         size_t obj_size = sizeof(T_OBJECT*);
         l->items = (T_OBJECT**)REALLOC(l->items, size * obj_size);
         ASSERT_REALLOC(l->items);
         l->length = size;
      }

      return (T_OBJECT*)l;
   }


   T_OBJECT*
   List::set_item(T_OBJECT* list, UInt at, T_OBJECT* obj)
   {
      List::assert(list);

      List* l = (List*)list;
      l->items[at] = obj;
      T_OBJECT::pick(obj);
      return list;
   }

   T_OBJECT*
   List::slice(T_OBJECT* list, UInt start, UInt end, UInt step)
   {
      List::assert(list);

      List* base = (List*)list;
      List* result = new List();

      for (UInt i = start ; i < end ; i += step)
      {
         List::push((T_OBJECT*)result, base->items[i]);
      }

      return (T_OBJECT*)result;
   }
}

