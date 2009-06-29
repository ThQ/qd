#include "t/Exception.h"

int
main (int argc, char** argv)
{
   t::Exception* obj = new t::Exception;
   obj->pick();
   obj->drop();

   return 0;
}
