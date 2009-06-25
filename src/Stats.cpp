#include "Stats.h"

_Stats Stats;

_Stats::_Stats()
{
   this->dwDrops = 0;
   this->dwFinalDrops = 0;
   this->dwInitialPicks = 0;
   this->dwPicks = 0;
   this->dwReferences = 0;
}

void
_Stats::print_report()
{
   printf("-- Stats --\n");
   printf("Reference count : %lu\n", this->dwReferences);
   printf(" -> Picks : %lu\n", this->dwPicks);
   printf(" -> Initial picks: %lu\n", this->dwInitialPicks);
   printf(" -> Drops : %lu\n", this->dwDrops);
   printf(" -> Final drops : %lu\n", this->dwFinalDrops);
}

