#ifndef SVM_CLASS_H
#define SVM_CLASS_H

#include <string>
#include <unicode/unistr.h>

#include "debug.h"
#include "svm/Object.h"
#include "svm/String.h"


#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_CLASS(o) if (svm::Class::check(o) != true) { FATAL("Must be of type <system.Class>.\n"); abort();}
   #define SVM_ASSERT_SAME_TYPES(t1, t2) \
       if (t1 != t2) {\
          FATAL("Types(@%d and @%d) mistmatch.\n<svm::Class*[at=%d; name=\"", (int)t1, (int)t2, (int)t1); \
          if (t1 != NULL) { \
            printf("%s", ((svm::Class*)t1)->name.c_str()); \
          } else { \
            printf("NULL"); \
          } \
          printf("\"]> != <svm::Class*[at=%d; name=\"", (int)t2); \
          if (t2 != NULL) { \
            printf("%s", ((svm::Class*)t2)->name.c_str()); \
          } else { \
             printf("NULL"); \
          } \
          printf("\"]>.\n"); \
          abort(); \
       }
   #define SVM_CHECK_CLASS(o) if (svm::Class::check(o) != true) { WARNING("Should be of type <system.Class>.\n"); }
#else
   #define SVM_ASSERT_CLASS(o)
   #define SVM_ASSERT_SAME_TYPES(t1, t2)
   #define SVM_CHECK_CLASS(o)
#endif


namespace svm
{
   extern Object* class_not_found_exception_type;
   extern Object* bad_type_exception_type;

   class Class : public Object
   {
      public: Object* parent_class;
      public: std::string name;

      public: Class();
      public: ~Class();
      public: static Object* build();
      public: static Object* build(std::string name);
      public: static Object* build(const char* name);
      public: static Object* build(const char* name, Object* parent_class);
      public: static Object* build(std::string name, Object* parent_class);
      public: static Object* build(Object* parent_class);
      public: static bool check(Object* obj);
      public: static bool is_child_of(Object* cls, Object* parent_class);
      public: void set_parent_class(Object* parent_class);
   };
}

#endif
