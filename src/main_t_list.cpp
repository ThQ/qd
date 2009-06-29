#include "t/List.h"

int
main (int argc, char **arv)
{
   t::List* pList = new t::List;
   pList->pick();

   t::List* pValue1 = new t::List;
   pValue1->pick();

   t::List* pValue2 = new t::List;
   pValue2->pick();

   INTERNAL("PUSH_ITEM (.at %x)\n", (uint)pValue1);
   pList->push(pValue1);

   INTERNAL("PUSH_ITEM (.at %x)\n", (uint)pValue2);
   pList->push(pValue2);

   pList->fpPrintLine((t::Object*)pList);

   INTERNAL("REMOVE_ITEM (.at 0)\n");
   pList->remove_item(0);

   INTERNAL("DROP_OBJECT (.at %x)\n", (uint)pValue2);
   pValue2->drop();
   INTERNAL("DROP_OBJECT (.at %x)\n", (uint)pValue1);
   pValue1->drop();
   INTERNAL("DROP_OBJECT (.at %x)\n", (uint)pList);
   pList->drop();

   Stats.print_report();

   return 0;
}
