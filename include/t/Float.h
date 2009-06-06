#ifndef T_FLOAT
#define T_FLOAT t::Float

#include "t/Object.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_FLOAT(f) \
   DEPRECATED(); \
   if(f->cls != svm::float_type) \
   { \
      FATAL("Bad type given, expected system.Float.\n\n"); \
      abort(); \
   }
#else
   #define SVM_ASSERT_FLOAT(f) DEPRECATED();
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_FLOAT(f) \
   DEPRECATED(); \
   if(f->cls != svm::float_type) \
   { \
      WARNING("Bad type given, expected system.Float.\n\n"); \
   }
#else
   #define SVM_CHECK_FLOAT(f) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* tFLOAT;

   /**
    * An internal representation of a float.
    */
   class Float : public T_OBJECT
   {
      public: long double value;

      public: Float();

      /**
       * Builds a t::Float from a c long double [d].
       *
       * @param d A c long double to use.
       * @return A pointer to a t::Float newly created.
       */
      public: static T_OBJECT* build(long double d);
   };
}

#endif
