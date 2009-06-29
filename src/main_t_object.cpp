#include "t/Object.h"
#include "Stats.h"

int
main (int argc, char** argv)
{
   t::Object* obj = new t::Object;
   obj->pick();
   obj->drop();

   Stats.print_report();

   return 0;
}
