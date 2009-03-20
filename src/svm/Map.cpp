#include "svm/Map.h"

namespace svm
{
   Object* map_type = NULL;

   Map::Map()
   {
      this->length = 0;
      this->keys = 0;
      this->items = 0;
      this->references = 0;
      this->set_class(svm::map_type);
   }

   Object*
   Map::build()
   {
      return (Object*)new Map();
   }

   bool
   Map::check(Object* m)
   {
      return m->cls == map_type;
   }

   Object*
   Map::clear(Object* map)
   {
      SVM_ASSERT_MAP(map);

      Map* m = (Map*)map;
      for (int i = 0 ; i < m->length ; ++i)
      {
         SVM_DROP(m->items[i]);
         SVM_DROP(m->keys[i]);
         m->items[i] = 0;
         m->keys[i] = 0;
      }
      m->items = (Object**)realloc(m->items, 0);
      m->keys = (Object**)realloc(m->keys, 0);
      m->length = 0;
      return (Object*)m;
   }

   int
   Map::find_key(Map* map, Object* key)
   {
      int result = -1;
      int i;
      for (i = 0 ; i < map->length ; ++i)
      {
         if (map->keys[i] == key)
         {
            result = i;
            break;
         }
      }
      return result;
   }

   // @TODO: Move to something like CollectionUtil.cpp
   void
   Map::print(Object* map)
   {
      /*
      SVM_ASSERT_MAP(map);

         Map* m = (Map*)map;
         int i;
         printf("{");
         for (i = 0 ; i < m->length ; ++i)
         {
            if (i != 0)
            {
               printf(", ");
            }
            Object* key = m->keys[i];
            Object* value = m->items[i];
            if (key != NULL && value != NULL)
            {
               svm_print(key);
               printf(" = ");
               svm_print(value);
            }
         }
         printf("}");
         */
   }

   Object*
   Map::set_item(Object* list, Object* key, Object* value)
   {
      SVM_CHECK_MAP(list);

      Map* m = (Map*)list;
      int pos;
      if ((pos = Map::find_key(m, key)) != -1)
      {
         m->items[pos] = value;
      }
      else
      {
         m->length ++;
         int new_size = m->length * sizeof(Object*);
         m->keys = (Object**)realloc(m->keys, new_size);
         m->items = (Object**)realloc(m->items, new_size);
         m->keys[m->length - 1] = key;
         m->items[m->length - 1] = value;
         SVM_PICK(key);
         SVM_PICK(value);
      }

      return value;
   }

   Object*
   Map::set_item(Object* map, std::string key, std::string value)
   {
      SVM_CHECK_MAP(map);

      Object* k = String::build((std::string)key);
      Object* v = String::build((std::string)value);

      return Map::set_item(map, k, v);
   }

   Object*
   Map::slice(Object* map, Object* key1, Object* key2)
   {
      SVM_ASSERT_MAP(map);

      Map* result = new Map();
      Map* m = (Map*)map;
      int slice_start = Map::find_key(m, key1);
      int slice_end = Map::find_key(m, key2);
      int slice_len;
      int step;

      if (slice_start != -1 && slice_end != -1)
      {
         if (slice_start < slice_end)
         {
            step = 1;
            slice_len = slice_end - slice_start;
         }
         else
         {
            step = -1;
            slice_len = slice_start - slice_end;
         }
         ++slice_len;
         int at;
         for (int i = 0 ; i < slice_len ; ++i)
         {
            at = slice_start + (step * i);
            SVM_PICK(m->keys[at]);
            SVM_PICK(m->items[at]);
            Map::set_item(result, m->keys[at], m->items[at]);
         }
      }

      return result;
   }
}
