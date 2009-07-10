#include "t/List.h"
#include "vm/Class.h"

int
main (int argc, char **arv)
{
   t::List* pList = new t::List(t::LIST_TYPE, &t::cLIST);
   pList->pick();

   t::List* pValue1 = new t::List(t::INT32_TYPE);
   pValue1->pick();

   t::List* pValue2 = new t::List(t::INT32_TYPE);
   pValue2->pick();

   INTERNAL("<%s @%x> PUSH_ITEM (.at %x)\n", t::cast_type_to_string(pList->type), (uint)pList, (uint)pValue1);
   pList->push(pValue1);

   INTERNAL("<%s @%x> PUSH_ITEM (.at %x)\n", t::cast_type_to_string(pList->type), (uint)pList, (uint)pValue2);
   pList->push(pValue2);

   ((vm::Class*)pList->klass)->print_line_func((t::Object*)pList);

   INTERNAL(
         "<%s @%x> REMOVE_ITEM (.at 0)\n",
         t::cast_type_to_string(pList->type),
         (uint)pList
   );
   pList->remove_item(0);

   INTERNAL(
         "<%s @%x> DROP\n",
         t::cast_type_to_string(pValue2->type),
         (uint)pValue2
   );
   pValue2->drop();

   INTERNAL(
         "<%s @%x> DROP\n",
         t::cast_type_to_string(pValue1->type),
         (uint)pValue1
   );
   pValue1->drop();

   INTERNAL(
         "<%s @%x> DROP\n",
         t::cast_type_to_string(pList->type),
         (uint)pList
   );
   pList->drop();

   Stats.print_report();

   return 0;
}
