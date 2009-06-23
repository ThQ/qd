#include "t/Map.h"
#include "util/Object.h"

int
main (int argc, char** argv)
{
   t::Map* pBaseMap = new t::Map();
   pBaseMap->pick();

   t::Map* pKey = new t::Map();
   pKey->pick();

   t::Map* pValue = new t::Map();
   pValue->pick();

   pBaseMap->set_item(pKey, pValue);
   pBaseMap->set_item(pValue, pKey);
   pBaseMap->fpPrintLine(pBaseMap);

   pValue->drop();
   pKey->drop();
   pBaseMap->drop();

   Stats.print_report();

   ASSERT(Stats.dwReferences == 0, "There must not be any references left.");
   return 0;
}
