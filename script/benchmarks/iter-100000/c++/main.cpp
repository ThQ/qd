#include <stdio.h>

int main(int* argc, char** argv)
{
   for (unsigned int i = 0 ; i < 100000 ; ++i)
   {
      printf("%d\n", i);
   }
   return 0;
}
