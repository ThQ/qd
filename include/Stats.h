#ifndef STATS_H
#define STATS_H

#include <stdio.h>

#include "types.h"


class _Stats
{
   public: ulonglong dwDrops;
   public: ulonglong dwFinalDrops;
   public: ulonglong dwInitialPicks;
   public: ulonglong dwPicks;
   public: ulonglong dwReferences;

   public: _Stats();
   public: void print_report();
} ;

extern _Stats Stats;
//_Stats Stats;

#endif
