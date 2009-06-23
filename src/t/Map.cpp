#include "t/Map.h"

namespace t
{
   // T_OBJECT* tMAP = NULL;

   Map::Map()
   {
      this->length = 0;
      this->keys = 0;
      this->items = 0;
      this->references = 0;
      this->type = t::MAP_TYPE;

      this->fpDestroy = t::Map::destroy;
      this->fpPrint = t::Map::print;
      this->fpPrintLine = t::Map::print_line;
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
   Map::destroy(Object* pObject)
   {
      Map::assert(pObject);
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
   Map::print(Object* pObject)
   {
      Map::assert(pObject);
      Map* pMap = (Map*)pObject;

      printf("[");
      LOOP_FROM_TO(UInt64, i, 0, pMap->length)
      {
         ASSERT_NOT_NULL(pMap->keys[i]->fpPrint);
         ASSERT_NOT_NULL(pMap->items[i]->fpPrint);
         if (pMap->keys[i] != NULL)
         {
            if (i != 0)
            {
               printf(", ");
            }
            pMap->keys[i]->fpPrint(pMap->keys[i]);
         }
         else
         {
            printf("Null");
         }
         printf(": ");
         if (pMap->items[i] != NULL)
         {
            pMap->items[i]->fpPrint(pMap->items[i]);
         }
         else
         {
            printf("Null");
         }

      }
      printf("]");
   }

   void
   Map::print_line(Object* pMap)
   {
      Map::assert(pMap);
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
