#include "Stats.h"

_Stats Stats;

_Stats::_Stats()
{
   this->dwDrops = 0;
   this->dwPicks = 0;
   this->dwReferences = 0;
}

void
_Stats::print_report()
{
   printf("-- Stats --\n");
   printf("Reference count : %ld\n", this->dwReferences);
   printf(" -> Picks : %ld\n", this->dwPicks);
   printf(" -> Drops : %ld\n", this->dwDrops);
}

