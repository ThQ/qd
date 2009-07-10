#include "t/Array.h"
#include "Stats.h"

int
main (int argc, char** argv)
{
   t::Array* pArrayArray = new t::Array(t::LIST_TYPE, &t::cARRAY, 1);
   pArrayArray->pick();

   t::Array* pAnotherArray = new t::Array(t::LIST_TYPE, &t::cARRAY, 0);
   pAnotherArray->pick();
   pArrayArray->set_item(0, pAnotherArray);
   pArrayArray->clear_item(0);
   pArrayArray->set_item(0, pAnotherArray);
   pArrayArray->clear_item(0);
   pAnotherArray->drop();
   pArrayArray->drop();


   t::Array* pInt16Array = new t::Array(t::INT16_TYPE, NULL, 1);
   pInt16Array->pick();
   pInt16Array->set_item(0, (t::Value)16);
   pInt16Array->clear_item(0);
   pInt16Array->drop();

   Stats.print_report();
   return 0;
}
