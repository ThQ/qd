#ifndef ASSERT__H
#define ASSERT__H __FILE__

#include "config.h"

#ifdef __ALLOW_ASSERTIONS__
#  define ASSERT(b,args...) if((b)!=true) {FATAL("ASSERTION_FAILED");printf(args);printf("\n%s\n\n", #b);abort();}
#  define ASSERT_DELETE(p) if (p != NULL) {FATAL("delete failed @%u.\n", (uint)(p));}
#  define ASSERT_MALLOC(p) if(p == NULL) {FATAL("Malloc failed.");abort();}
#  define ASSERT_NOT_NULL(p) if((p) == NULL) \
   { \
      FATAL("POINTER_MUST_NOT_BE_NULL (.pointer \"%s\", .pointer_at 0x%u)\n", \
         #p, \
         (uint)(p) \
      ); \
      abort();\
   }
#  define ASSERT_NULL(p) if((p) != NULL) {FATAL("POINTER_MUST_BE_NULL (.pointer \"%s\", .pointer_at 0x%u)\n", #p, (uint)(p)); abort();}
#  define ASSERT_REALLOC(p) if(p == NULL) {FATAL("REALLOC_FAILED (.pointer \"%s\", .pointer_at 0x%u", #p, (uint)(p)); abort();}
#else
#  define ASSERT(b,args...)
#  define ASSERT_DELETE(p)
#  define ASSERT_MALLOC(p)
#  define ASSERT_NOT_NULL(p)
#  define ASSERT_NULL(p)
#  define ASSERT_REALLOC(p)
#endif

#ifdef __ALLOW_CHECKS__
#  define CHECK(b,args...) if((b)!=true) {WARNING(args);}
#  define CHECK_NULL(p) if((p) != NULL) {WARNING("POINTER_SHOULD_BE_NULL (.at 0x%x, .name \"%s\")\n", (uint)(p), #p);}
#  define CHECK_NOT_NULL(p) if((p) == NULL) {WARNING("POINTER_SHOULD_NOT_BE_NULL (.at 0x%x, .name \"%s\")\n", (uint)(p), #p);}
#else
#  define CHECK(b,args...)
#  define CHECK_NULL(p)
#  define CHECK_NOT_NULL(p)
#endif

#endif /* ASSERT__H */

