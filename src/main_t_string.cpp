#include "t/String.h"

int
main (int argc, char** argv)
{
   t::String* pBaseString = new t::String("FUCK ME");
   pBaseString->pick();

   t::String* pAString = new t::String("_-+");
   pAString->pick();

   t::String* pCenteredString = pBaseString->center((t::UInt64)20, pAString);
   pCenteredString->pick();
   pCenteredString->fpPrintLine(pCenteredString);

   t::String* pLowerCasedString = pBaseString->lower_case();
   pLowerCasedString->pick();
   pLowerCasedString->fpPrintLine(pLowerCasedString);

   pLowerCasedString->drop();
   pCenteredString->drop();
   pAString->drop();
   pBaseString->drop();

   Stats.print_report();

   return 0;
}
