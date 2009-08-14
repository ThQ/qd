#ifndef STATS_H
#define STATS_H

#include <stdio.h>

#include "types.h"


/**
 * @brief Holds all the stats.
 */
class _Stats
{
   public: ulong dwDrops;        ///< How many drops have been made.
   public: ulong dwFinalDrops;   ///< How many deletes have been made subsequently of a drop.
   public: ulong dwInitialPicks; ///< How many first drops have been made.
   public: ulong dwPicks;        ///< How many picks have been made.
   public: ulong dwReferences;   ///< How many references are still available.

   /**
    * @brief Default constructor.
    */
   public: _Stats();

   /**
    * @brief Prints a full report.
    */
   public: void print_report();
} ;

extern _Stats Stats;

#endif
