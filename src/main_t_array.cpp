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

   t::Array* pIntArray = new t::Array(t::U_LONG_TYPE, NULL, 10000000);
   pIntArray->pick();

   for (t::ULong i = 0; i < 10000000; ++i)
   {
      pIntArray->set_item(i, (t::Value)(t::ULong)i);
   }

   pIntArray->klass->print_line_func(pIntArray);
   for (t::ULong i = 0; i < 10000000; ++i)
   {
      pIntArray->clear_item(i);
   }
   pIntArray->drop();

   Stats.print_report();
}
