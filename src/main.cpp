#include <getopt.h>

#include "svm/EngineStarter.h"

int
main (int argc, char **argv)
{
   int c;
   while (1)
   {
      static struct option long_options[] =
      {
         {"initialize",     no_argument,       0, 'i'}
      };
      int option_index = 0;
      c = getopt_long (argc, argv, "", long_options, &option_index);

      if (c == -1)
      {
         break;
      }

      switch (c)
      {
         case 'i':
            //svm::EngineStarter* is = new svm::EngineStarter();
            //is->setup();
            //is->tear_down();
            break;

         default:
            abort();
      }
   }

   int real_argc = argc - optind;
   if (real_argc == 1)
   {
      svm::EngineStarter starter;
      starter.setup();
      starter.engine.run_file(argv[optind]);
      starter.tear_down();
   }
}

