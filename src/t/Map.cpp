#include "t/Map.h"

namespace t
{
   T_OBJECT* tMAP = NULL;

   Map::Map()
   {
      this->length = 0;
      this->keys = 0;
      this->items = 0;
      this->references = 0;
      this->set_class(NS_TYPE::tMAP);
   }

   T_OBJECT*
   Map::build()
   {
      return (T_OBJECT*)new Map();
   }

   T_OBJECT*
   Map::clear(T_OBJECT* map)
   {
      Map::assert(map);

      Map* m = (Map*)map;
      for (int i = 0 ; i < m->length ; ++i)
      {
         T_OBJECT::drop(m->items[i]);
         T_OBJECT::drop(m->keys[i]);
         m->items[i] = 0;
         m->keys[i] = 0;
      }
      m->items = (T_OBJECT**)REALLOC(m->items, 0);
      m->keys = (T_OBJECT**)REALLOC(m->keys, 0);
      m->length = 0;
      return (T_OBJECT*)m;
   }

   int
   Map::find_key(Map* map, T_OBJECT* key)
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

   T_OBJECT*
   Map::set_item(T_OBJECT* list, T_OBJECT* key, T_OBJECT* value)
   {
      Map::assert(list);

      Map* m = (Map*)list;
      int pos;
      if ((pos = Map::find_key(m, key)) != -1)
      {
         m->items[pos] = value;
      }
      else
      {
         m->length ++;
         int new_size = m->length * sizeof(T_OBJECT*);
         m->keys = (T_OBJECT**)REALLOC(m->keys, new_size);
         m->items = (T_OBJECT**)REALLOC(m->items, new_size);
         m->keys[m->length - 1] = key;
         m->items[m->length - 1] = value;
         T_OBJECT::pick(key);
         T_OBJECT::pick(value);
      }

      return value;
   }

   T_OBJECT*
   Map::set_item(T_OBJECT* map, std::string key, std::string value)
   {
      Map::assert(map);

      T_OBJECT* k = T_STRING::build((std::string)key);
      T_OBJECT* v = T_STRING::build((std::string)value);

      return Map::set_item(map, k, v);
   }

   T_OBJECT*
   Map::slice(T_OBJECT* map, T_OBJECT* key1, T_OBJECT* key2)
   {
      Map::assert(map);

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
            T_OBJECT::pick(m->keys[at]);
            T_OBJECT::pick(m->items[at]);
            Map::set_item(result, m->keys[at], m->items[at]);
         }
      }

      return result;
   }
}
