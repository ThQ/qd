#include "t/Map.h"
#include "Stats.h"

int
main (int argc, char** argv)
{
   t::Map* pBaseMap = new t::Map();
   util::Object::pick(pBaseMap);

   t::Map* pKey = new t::Map();
   util::Object::pick(pKey);

   t::Map* pValue = new t::Map();
   util::Object::pick(pValue);

   pBaseMap->set_item(pKey, pValue);

   util::Object::drop(pValue);
   util::Object::drop(pKey);
   util::Object::drop(pBaseMap);

   Stats.print_report();

   return 0;
}
