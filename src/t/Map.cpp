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

      this->items = (Object**) Memory::realloc(this->items, 0);
      this->keys = (Object**) Memory::realloc(this->keys, 0);
      this->length = 0;
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
         UInt64 new_size = ++ this->length * sizeof(Object*);

         this->keys = (Object**) Memory::realloc(this->keys, new_size);
         this->items = (Object**) Memory::realloc(this->items, new_size);

         this->items[this->length - 1] = pValue;
         pValue->pick();

         this->keys[this->length - 1] = pKey;
         pKey->pick();
      }

      return bSetWentOk;
   }
}
