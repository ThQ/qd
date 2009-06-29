#include "t/String.h"

int
main (int argc, char** argv)
{
   t::String* pBaseString = new t::String("FUCK");
   pBaseString->pick();

   t::String* pAString = new t::String("_-+");
   pAString->pick();

   t::String* pCenteredString = pBaseString->center((t::UInt64)30, pAString);
   pCenteredString->pick();
   //pCenteredString->print_line();

   t::String* pLowerCasedString = pBaseString->lower_case();
   pLowerCasedString->pick();
   //pLowerCasedString->print_line();

   pLowerCasedString->drop();
   pCenteredString->drop();
   pAString->drop();
   pBaseString->drop();

   Stats.print_report();

   return 0;
}
