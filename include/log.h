#ifndef LOG__H
#define LOG__H __FILE__

#include <stdio.h>

#include "config.h"

#define DEPRECATED() FATAL("This function is deprecated.\n"); abort();

#ifdef QD__LOG__SHOW_INTERNAL
#  ifdef USE_COLORS
#     define INTERNAL(args ...)  printf(QD__LOG__PREFIX"\033[00;37mIntrn\033[00m [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  else
#     define INTERNAL(args ...)  printf(QD__LOG__PREFIX"Intrn [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  endif
#  define INTERNAL_APD(args ...) printf(args);
#else
#  define INTERNAL(args ...)
#  define INTERNAL_APD(args ...)
#endif

#ifdef QD__LOG__SHOW_FATAL
#  define FATAL(args ...)  printf("\n\n"QD__LOG__PREFIX"Fatal [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);printf("\n\n");
#else
#  define FATAL(args...)
#endif

#ifdef QD__LOG__SHOW_WARNING
#  ifdef USE_COLORS
#     define WARNING(args ...)  printf(QD__LOG__PREFIX"\033[41;1;37mWarng\033[00m [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  else
#     define WARNING(args ...)  printf(QD__LOG__PREFIX"Warng [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  endif
#else
#  define WARNING(args...)
#endif

#ifdef QD__LOG__SHOW_DEBUG
#  define DEBUG(args ...)  printf(QD__LOG__PREFIX"Debug [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  define DEBUG_APD(args ...) printf(args);
#else
#  define DEBUG(args...)
#  define DEBUG_APD(args...)
#endif

#ifdef QD__LOG__SHOW_REF_COUNT
#  define LOG_REFCOUNT(args ...)  printf(QD__LOG__PREFIX"RfCnt [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  define LOG_REFCOUNT_APD(args ...) printf(args);
#else
#  define LOG_REFCOUNT(args...)
#  define LOG_REFCOUNT_APD(args...)
#endif

#ifdef QD__LOG__SHOW_MEMORY
#  define LOG_MEMORY(args ...)  printf(QD__LOG__PREFIX"Memry [%s:%d#%s] ", __FILE__, __LINE__, __FUNCTION__);printf(args);
#  define LOG_MEMORY_APD(args ...) printf(args);
#else
#  define LOG_MEMORY(args...)
#  define LOG_MEMORY_APD(args...)
#endif

#ifdef QD__LOG__SHOW_OPCODE
#  define LOG_OPCODE(pOpc, args ...)  printf(QD__LOG__PREFIX"OpCde [%s:%d#%s] <Opcode:0x%x> ", __FILE__, __LINE__, __FUNCTION__, (uint)(pOpc));printf(args);
#  define LOG_OPCODE_(args ...) printf(args);
#else
#  define LOG_OPCODE(pOpc, args...)
#  define LOG_OPCODE_(args...)
#endif

#endif

