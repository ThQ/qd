#include "t/Array.h"

int
main (int argc, char** argv)
{
   t::Array* pArray = new t::Array(t::ARRAY_TYPE, NULL, 1);
   pArray->pick();

   t::Array* pAnotherArray = new t::Array;
   pAnotherArray->pick();

   INTERNAL(
         "<%s @%x> SET_ITEM (.at 0, .item <%s @%x>)\n",
         t::cast_type_to_string(pArray->type),
         (uint)pArray,
         t::cast_type_to_string(pAnotherArray->type),
         (uint)pAnotherArray
   );
   pArray->set_item(0, pAnotherArray);

   INTERNAL(
         "<%s @%x> CLEAR_ITEM (.at 0)\n",
         t::cast_type_to_string(pArray->type),
         (uint)pArray
   );
   pArray->clear_item(0);

   INTERNAL(
         "<%s @%x> SET_ITEM (.at 0, .item <%s @%x>)\n",
         t::cast_type_to_string(pArray->type),
         (uint)pArray,
         t::cast_type_to_string(pAnotherArray->type),
         (uint)pAnotherArray
   );
   pArray->set_item(0, pAnotherArray);
   pArray->clear_range(0, 1);

   pAnotherArray->drop();

   pArray->drop();
   return 0;
}
