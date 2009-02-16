#ifndef SVM_VARIABLE_H
#define SVM_VARIABLE_H


#include <string>
#include <unicode/unistr.h>
#include "svm/Class.h"
#include "svm/Object.h"
#include "svm/String.h"

#define SVM_VARIABLE_NAME_SIZE 256

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_VARIABLE(v) if(v->cls != svm::variable_type){FATAL("Bad type given, expected system.Variable.\n\n");abort();}
#else
   #define SVM_ASSERT_VARIABLE(v)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_VARIABLE(v) if(v->cls != svm::variable_type){WARNING("Bad type given, expected system.Variable.\n\n");}
#else
   #define SVM_CHECK_VARIABLE(v)
#endif

namespace svm
{
   extern Object* variable_type;

   class Variable : public Object
   {
      public: Object* object_type;
      public: Object* object;
      public: std::string name;

      public: Variable();
      public: ~Variable();
      public: static Object* build(Object* type);
      public: static Object* build(Object* type, std::string name);
      public: static bool check(Object* variable);
      public: static Object* set(Object* variable, Object* obj);
      public: void set_object_type(Object* type);
   };
}

#endif
