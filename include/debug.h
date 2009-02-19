#ifndef DEBUG_H
#define DEBUG_H

#ifdef __DEBUG__
   #define _DEBUG_
   #define __ALLOW_ASSERTIONS__
   #define __ALLOW_SVM_ASSERTIONS__
   #define __ALLOW_CHECKS__
   #define __ALLOW_SVM_CHECKS__
   #define _SHOW_DEBUG_
   #define _SHOW_FATAL_
   #define _SHOW_WARNING_
   #define ALLOW_UNICODE 1

#elif defined(__INTROSPECTION__)
   #define _INTROSPECTION_
   #define _DEBUG_
   #define __ALLOW_ASSERTIONS__
   #define __ALLOW_SVM_ASSERTIONS__
   #define __ALLOW_CHECKS__
   #define _SHOW_DEBUG_
   #define _SHOW_FATAL_
   #define _SHOW_INTERNAL_
   #define _SHOW_WARNING_
   #define ALLOW_UNICODE 1

#elif defined(__INTERNAL__)
   #define _INTERNAL_
   #define _DEBUG_
   #define __DEBUG__
   #define _INTROSPECTION_
   #define __INTROSPECTION__
   #define __ALLOW_ASSERTIONS__
   #define __ALLOW_SVM_ASSERTIONS__
   #define __ALLOW_CHECKS__
   #define _SHOW_DEBUG_
   #define _SHOW_FATAL_
   #define _SHOW_INTERNAL_
   #define _SHOW_WARNING_
   #define _SHOW_GC_
   #define ALLOW_UNICODE 1

#elif defined(__RELEASE__)
   #define ALLOW_UNICODE 1
#endif

#define DEPRECATED() FATAL("This function is deprecated.\n"); abort();

#ifdef _SHOW_INTERNAL_
   #ifdef USE_COLORS
      #define INTERNAL(args ...)  printf(";; \033[00;37mINTRN\033[00m [%s:%d] ", __FILE__, __LINE__);printf(args);
   #else
      #define INTERNAL(args ...)  printf(";; INTRN [%s:%d] ", __FILE__, __LINE__);printf(args);
   #endif
   #define INTERNAL_APD(args ...) printf(args);
#else
   #define INTERNAL(args ...)
   #define INTERNAL_APD(args ...)
#endif

#ifdef _SHOW_FATAL_
   #define FATAL(args ...)  printf("\n\n{{ FATAL ERROR }} %s:%d | ", __FILE__, __LINE__);printf(args);printf("\n\n");
#else
   #define FATAL(args...)
#endif

#ifdef _SHOW_WARNING_
   #ifdef USE_COLORS
      #define WARNING(args ...)  printf(";; \033[41;1;37mWARNG\033[00m  [%s:%d] ", __FILE__, __LINE__);printf(args);
   #else
      #define WARNING(args ...)  printf(";; WARNG [%s:%d] ", __FILE__, __LINE__);printf(args);
   #endif
#else
   #define WARNING(args...)
#endif

#ifdef _SHOW_DEBUG_
   #define DEBUG(args ...)  printf(";; DEBUG [%s:%d] ", __FILE__, __LINE__);printf(args);
   #define DEBUG_APD(args ...) printf(args);
#else
   #define DEBUG(args...)
   #define DEBUG_APD(args...)
#endif

#ifdef _SHOW_GC_
   #define GC(args ...)  printf(";; GCOLL [%s:%d] ", __FILE__, __LINE__);printf(args);
   #define GC_APD(args ...) printf(args);
#else
   #define GC(args...)
   #define GC_APD(args...)
#endif

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_NOT_NULL(v) ASSERT_NOT_NULL(v); if(v == svm::Null) {FATAL("SVM_ASSERT_NOT_NULL: Must not be <svm::Null>.\n");abort();}
#else
   #define SVM_ASSERT_NOT_NULL(v)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_NOT_NULL(v) if(v == 0 || v == NULL || v == svm::Null) {WARNING("SVM_CHECK_NOT_NULL: Should not be C's <NULL> or <svm::Null>.\n");}
#else
   #define SVM_CHECK_NOT_NULL(v)
#endif

#define DELETE(p) INTERNAL("<c::delete> on object @%lu...", (long unsigned)p); delete p; p = NULL; ASSERT_DELETE(p); INTERNAL_APD(" OK\n");

#ifdef __ALLOW_ASSERTIONS__
#  define ASSERT(b,args...) if((b)!=true) {FATAL(args);abort();}
#  define ASSERT_DELETE(p) if (p != NULL) {FATAL("delete failed @%lu.\n", (long unsigned)p);}
#  define ASSERT_MALLOC(p) if(p == NULL) {FATAL("Malloc failed.");abort();}
#  define ASSERT_NOT_NULL(p) if((p) == NULL) {FATAL("@%lu must not be <NULL>.\n", (ULong)(p));abort();}
#  define ASSERT_NULL(p) if((p) != NULL) {FATAL("@%lu must be <NULL>.\n", (ULong)(p)); abort();}
#  define ASSERT_REALLOC(p) if(p == NULL) {FATAL("Realloc failed."); abort();}
#else
#  define ASSERT(b,args...)
#  define ASSERT_DELETE(p)
#  define ASSERT_MALLOC(p)
#  define ASSERT_NOT_NULL(p)
#  define ASSERT_NULL(p)
#  define ASSERT_REALLOC(p)
#endif

#ifdef __ALLOW_CHECKS__
   #define CHECK(b,args...) if((b)!=true) {WARNING(args);}
   #define CHECK_NOT_NULL(p) if((p) == NULL) {WARNING("@%lu should not be <NULL>.\n", (ULong)(p));}
#else
   #define CHECK(b,args...)
   #define CHECK_NOT_NULL(p)
#endif

#endif

