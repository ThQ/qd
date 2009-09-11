#ifndef CONFIG__H
#define CONFIG__H __FILE__

#define QD__NAME                    "Qd"
#define QD__AUTHOR_NAME             "Thomas Quémard"
#define QD__VERSION                 "0.1"
#define QD__VERSION_MAJOR           "0"
#define QD__VERSION_MINOR           "1"

#define QD__ASSERT__ALLOW                 1
#define QD__T__EXCEPTION__HAVE_MESSAGE    1
#define QD__VM__KEEP_STATS                1

#define QD__LOG__PREFIX                   "### "

#ifdef __DEBUG__
   #define _DEBUG_
   #define __ALLOW_ASSERTIONS__
   #define __ALLOW_SVM_ASSERTIONS__
   #define __ALLOW_CHECKS__
   #define __ALLOW_SVM_CHECKS__
   #define QD__LOG__SHOW_DEBUG
   #define QD__LOG__SHOW_FATAL
   #define QD__LOG__SHOW_WARNING
   #define ALLOW_UNICODE 1

#elif defined(__INTROSPECTION__)
   #define _INTROSPECTION_
   #define _DEBUG_
   #define __ALLOW_ASSERTIONS__
   #define __ALLOW_SVM_ASSERTIONS__
   #define __ALLOW_CHECKS__
   #define QD__LOG__SHOW_DEBUG
   #define QD__LOG__SHOW_FATAL
   #define QD__LOG__SHOW_INTERNAL
   #define QD__LOG__SHOW_OPCODE
   #define QD__LOG__SHOW_WARNING
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
   #define QD__LOG__SHOW_DEBUG
   #define QD__LOG__SHOW_FATAL
   #define QD__LOG__SHOW_INTERNAL
   #define QD__LOG__SHOW_MEMORY
   #define QD__LOG__SHOW_OPCODE
   #define QD__LOG__SHOW_REF_COUNT
   #define QD__LOG__SHOW_WARNING
   #define ALLOW_UNICODE 1

#elif defined(__RELEASE__)
   #define ALLOW_UNICODE 1
#endif

// ------------------
// Do NOT delete : this is a place holder for configuration defines.
//
// @@CONFIGURATION
//
// ------------------
// -------------------------
// NAMESPACES
// -------------------------
#endif
