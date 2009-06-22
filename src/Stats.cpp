#include "Stats.h"

void
Stats::init()
{
   Stats::dwDrops = 0;
   Stats::dwPicks = 0;
   Stats::dwReferences = 0;
}
void
Stats::print_report()
{
   printf("Reference count : %ld\n", dwReferences);
   printf(" -> Picks : %ld\n", dwPicks);
   printf(" -> Drops : %ld\n", dwDrops);
}

