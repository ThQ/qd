#include "svm/List.h"

namespace svm
{
   Object* list_type = NULL;

   List::List()
   {
      this->length = 0;
      this->items = 0;
      this->references = 0;
      this->set_class(svm::list_type);
   }

   Object*
   List::append(Object* list, Object* obj)
   {
      DEPRECATED();
      SVM_ASSERT_LIST(list);
      SVM_ASSERT_NOT_NULL(obj);

      List* l = (List*)list;
      List::resize(l, l->length + 1);
      l->items[l->length -1] = obj;
      return (Object*)l;
   }

   Object*
   List::build()
   {
      return (Object*)new List();
   }

   // TODO : Make this work !
   Object*
   List::cast_to_string(Object* obj)
   {
      SVM_ASSERT_LIST(obj);

      //List* l = (List*)obj;
      String* s = new String();
      /*
      String::append(s, "[");
      for (UInt i = 0 ; i < l->length ; ++i)
      {
         if (i != 0)
         {
            String::append(s, ", ");
         }
         Object* app = l->items[i];
         if (app != NULL)
         {
            Object* s_app_obj = svm_cast_to_string(app);
            String* s_app = (String*)s_app_obj;
            String::append(s, (String*)s_app);
         }
      }

      String::append(s, "]");
      */
      return (Object*)s;
   }

   Object*
   List::clear(Object* list)
   {
      if (!List::check(list))
      {
         return NULL;
      }

      List* l = (List*)list;

      for (UInt i = 0 ; i < l->length ; ++ i)
      {
         Object::drop(l->items[i]);
         l->items[i] = 0;
      }
      l->items = (Object**)realloc(l->items, 0);
      return (Object*)l;
   }

   bool
   List::check(Object* obj)
   {
      return obj->cls == svm::list_type;
   }

   void
   List::debug_id(Object* list)
   {
      if (List::check(list))
      {
         printf("<list:%i>\n", ((List*)list)->length);
      }
   }

   Object*
   List::flatten(Object* list)
   {
      List* base = (List*)list;
      List* dest = (List*)List::build();

      for (UInt i = 0 ; i < base->length ; ++i)
      {
         if (base->items[i]->cls == svm::list_type)
         {
            List::push_list((Object*)dest, List::flatten(base->items[i]));
         }
         else
         {
            List::push((Object*)dest, base->items[i]);
         }
      }
      return (Object*)dest;
   }

   Object*
   List::get_item(Object* list, UInt at)
   {
      List* l = (List*)list;
      Object* result = l->items[at];
      return result;
   }

   Object*
   List::insert(Object* list, UInt at, Object* obj)
   {
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
         SVM_PICK(obj);
      }

      return (Object*)l;
   }

   Object*
   List::pop(Object* self)
   {
      List* l = (List*)self;
      SVM_PICK(l);
      --l->length;
      Object* result = l->items[l->length];
      List::resize(self, l->length);
      SVM_DROP(l);
      return result;
   }

   Object*
   List::pop(Object* self, UInt num)
   {
      List* l = (List*)self;
      SVM_PICK(l);
      Object* result = l->items[l->length - 1];
      SVM_PICK(result);

      for (UInt i = l->length - num ; i < l->length ; ++i)
      {
         SVM_DROP(l->items[i]);
         l->items[i] = NULL;
      }
      l->length = l->length - num;
      List::resize(l, l->length);
      SVM_DROP(l);
      return result;
   }

   Object*
   List::push(Object* list, Object* obj)
   {
      SVM_ASSERT_LIST(list);
      SVM_ASSERT_NOT_NULL(obj);

      List* l = (List*)list;
      List::resize(l, l->length + 1);
      l->items[l->length -1] = obj;
      return (Object*)l;
   }

   void
   List::push_list(Object* l1, Object* l2)
   {
      List* base = (List*)l1;
      List* ext = (List*)l2;
      UInt base_len = base->length;

      svm::List::resize(l1, base->length + ext->length);

      for (UInt i = 0 ; i < ext->length ; ++i)
      {
         base->items[base_len + i] = ext->items[i];
      }
   }

   Object*
   List::remove_item(Object* list, UInt at)
   {
      List* l = (List*)list;

      Object::drop(l->items[at]);
      l->items[at] = 0;
      for (UInt pos = at + 1 ; pos < (l->length - 1) ; ++pos)
      {
         l->items[pos] = l->items[pos + 1];
      }
      return List::resize((Object*)l, l->length - 1);
   }

   Object*
   List::reverse(Object* list)
   {
      List* src = (List*)list;
      List* dest = (List*)List::build();
      List::resize((Object*)dest, src->length);

      for (UInt i = 0 ; i < src->length ; ++i)
      {
         dest->items[i] = src->items[src->length - i - 1];
      }

      return (Object*)dest;
   }

   Object*
   List::resize(Object* list, UInt size)
   {
      List* l = (List*)list;

      if (size != l->length)
      {
         if (size < l->length)
         {
            for (UInt i = size ; i < l->length ; ++ i)
            {
               SVM_DROP(l->items[i]);
            }
         }

         size_t obj_size = sizeof(Object*);
         l->items = (Object**)realloc(l->items, size * obj_size);
         ASSERT_REALLOC(l->items);
         l->length = size;
      }

      return (Object*)l;
   }

   Object*
   List::set_item(Object* list, UInt at, Object* obj)
   {
      List* l = (List*)list;
      l->items[at] = obj;
      SVM_PICK(l->items[at]);
      return (Object*)l;
   }

   Object*
   List::slice(Object* list, UInt start, UInt end, UInt step)
   {
      List* base = (List*)list;
      List* result = new List();

      for (UInt i = start ; i < end ; i += step)
      {
         List::push((Object*)result, base->items[i]);
      }

      return (Object*)result;
   }
}

