#ifndef STATS_H
#define STATS_H

#include <stdio.h>

#include "types.h"

class Stats
{
   public: static ulonglong dwDrops;
   public: static ulonglong dwPicks;
   public: static ulonglong dwReferences;

   public: static void init();
   public: static void print_report();
};

#endif
