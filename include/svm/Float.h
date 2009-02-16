#ifndef SVM_FLOAT_H
#define SVM_FLOAT_H

#include "svm/Object.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_FLOAT(f) if(f->cls != svm::float_type){FATAL("Bad type given, expected system.Float.\n\n");abort();}
#else
   #define SVM_ASSERT_FLOAT(f)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_FLOAT(f) if(f->cls != svm::float_type){WARNING("Bad type given, expected system.Float.\n\n");}
#else
   #define SVM_CHECK_FLOAT(f)
#endif

namespace svm
{
   extern Object* float_type;

   class Float : public Object
   {
      public: long double value;

      public: Float();
      public: static Object* build(long double d);
   };
}

#endif
