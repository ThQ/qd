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
   printf(" -> Drops : %lu\n", this->dwDrops);
   printf(" -> Picks / Drops : %lu / %lu = %f\n", (ulong)this->dwPicks, (ulong)this->dwDrops, (float)(this->dwPicks / this->dwDrops));

   printf(" -> Initial picks: %lu\n", this->dwInitialPicks);
   printf(" -> Final drops : %lu\n", this->dwFinalDrops);

   printf(" -> Initial picks / Final drops: %lu / %lu = %f\n", (ulong)this->dwInitialPicks, (ulong)this->dwFinalDrops, (float)(this->dwInitialPicks / this->dwFinalDrops));
}

