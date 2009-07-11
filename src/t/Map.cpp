#include "t/Map.h"

namespace t
{
   VM_CLASS__NEW(cMAP, t::Map, t::MAP_TYPE, &cOBJECT);

   Map::Map()
   {
      this->length = 0;
      this->keys = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::MAP_TYPE;
      this->klass = &t::cMAP;

      this->key_type = t::UNDEFINED_TYPE;
      this->key_class = NULL;
      this->item_type = t::UNDEFINED_TYPE;
      this->item_class = NULL;
   }

   Map::~Map()
   {
      this->clear();
   }

   void
   Map::clear()
   {
      LOOP_FROM_TO(UInt64, i, 0, this->length)
      {
         this->items[i]->drop();
         this->items[i] = NULL;

         this->keys[i]->drop();
         this->keys[i] = NULL;
      }

      this->items = (Object**) realloc(this->items, 0);
      this->keys = (Object**) realloc(this->keys, 0);
      this->length = 0;
   }

   bool
   Map::destroy(Value pObject)
   {
      Map::assert((Object*)pObject);
      ((Map*)pObject)->clear();
      return true;
   }

   bool
   Map::find_key(Object* pKey, UInt64& dwPos)
   {
      bool bKeyFound = false;
      LOOP_FROM_TO (UInt64, i, 0, this->length)
      {
         if (this->keys[i] == pKey)
         {
            bKeyFound = true;
            dwPos = i;
            break;
         }
      }
      return bKeyFound;
   }

   bool
   Map::has_key(Object* pKey)
   {
      bool bKeyFound = false;
      LOOP_FROM_TO (UInt64, i, 0, this->length)
      {
         if (this->keys[i] == pKey)
         {
            bKeyFound = true;
            break;
         }
      }
      return bKeyFound;
   }

   void
   Map::print(Value pObject)
   {
      Map::assert((Object*)pObject);
      Map* pMap = (Map*)pObject;

      printf("[");
      LOOP_FROM_TO(UInt64, i, 0, pMap->length)
      {
         if (pMap->keys[i] != NULL)
         {
            if (i != 0)
            {
               printf(", ");
            }
            vm::Class* pKeyClass = ((Object*)pMap->keys[i])->klass;
            pKeyClass->print_func((Object*)pMap->keys[i]);
         }
         else
         {
            printf("Null");
         }
         printf(": ");
         if (pMap->items[i] != NULL)
         {
            vm::Class* pItemClass = ((Object*)pMap->items[i])->klass;
            pItemClass->print_func((Object*)pMap->items[i]);
         }
         else
         {
            printf("Null");
         }

      }
      printf("]");
   }

   void
   Map::print_line(Value pMap)
   {
      Map::assert((Object*)pMap);
      Map::print(pMap);
      printf("\n");
   }

   bool
   Map::set_item(Object* pKey, Object* pValue)
   {
      bool bSetWentOk = true;
      UInt64 dwPos;
      if (this->find_key(pKey, dwPos))
      {
         this->items[dwPos] = pValue;
      }
      else
      {
         UInt64 dwNewSize = ++ this->length * sizeof(Object*);

         this->keys = (Object**) realloc(this->keys, dwNewSize);
         this->items = (Object**) realloc(this->items, dwNewSize);

         this->items[this->length - 1] = pValue;
         pValue->pick();

         this->keys[this->length - 1] = pKey;
         pKey->pick();
      }

      return bSetWentOk;
   }
}
