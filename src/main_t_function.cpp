#include "t/Function.h"
#include "t/CoreFunction.h"
#include "t/UserFunction.h"

int
main (int argc, char** argv)
{
   t::Function* pFunc = new t::Function;
   pFunc->pick();
   //pFunc->define_arguments(3, (uchar*)"\x0A\x0A\x0A");
   pFunc->klass->print_line_func(pFunc);
   pFunc->drop();

   t::Function* pAnotherFunc = new t::Function;
   pAnotherFunc->pick();
   pAnotherFunc->drop();

   return 0;
}
