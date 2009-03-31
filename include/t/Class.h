#ifndef T_CLASS
#define T_CLASS NS_TYPE::Class

#include <string>

#include "t/Object.h"
#include "t/String.h"


#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_CLASS(o) \
   DEPRECATED(); \
   if (T_CLASS::check(o) != true) \
   { \
      FATAL("Must be of type <system.Class>.\n"); \
      abort(); \
   }
   #define SVM_ASSERT_SAME_TYPES(t1, t2) \
       if (t1 != t2) {\
          FATAL("Types(@%d and @%d) mistmatch.\n<svm::Class*[at=%d; name=\"", (int)t1, (int)t2, (int)t1); \
          if (t1 != NULL) { \
            printf("%s", ((T_CLASS*)t1)->name.c_str()); \
          } else { \
            printf("NULL"); \
          } \
          printf("\"]> != <svm::Class*[at=%d; name=\"", (int)t2); \
          if (t2 != NULL) { \
            printf("%s", ((T_CLASS*)t2)->name.c_str()); \
          } else { \
             printf("NULL"); \
          } \
          printf("\"]>.\n"); \
          abort(); \
       }
   #define SVM_CHECK_CLASS(o) \
   DEPRECATED(); \
   if (T_CLASS::check(o) != true) \
   { \
      WARNING("Should be of type <system.Class>.\n"); \
   }
#else
   #define SVM_ASSERT_CLASS(o) DEPRECATED();
   #define SVM_ASSERT_SAME_TYPES(t1, t2)
   #define SVM_CHECK_CLASS(o) DEPRECATED();
#endif


namespace NS_TYPE
{
   extern T_OBJECT* class_not_found_exception_type;
   extern T_OBJECT* bad_type_exception_type;

   class Class : public T_OBJECT
   {
      public: T_OBJECT* parent_class;
      public: std::string name;

      public: Class();
      public: ~Class();

      /**
       * Asserts that an object is of type t::Class.
       */
      public: inline static bool assert(T_OBJECT* obj)
      {
         return true;
      }

      public: static T_OBJECT* build();
      public: static T_OBJECT* build(std::string name);
      public: static T_OBJECT* build(const char* name);
      public: static T_OBJECT* build(const char* name, T_OBJECT* parent_class);
      public: static T_OBJECT* build(std::string name, T_OBJECT* parent_class);
      public: static T_OBJECT* build(T_OBJECT* parent_class);

      /*
       * Checks if an object is of type t::Class.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return true;
      }

      public: static bool is_child_of(T_OBJECT* cls, T_OBJECT* parent_class);
      public: void set_parent_class(T_OBJECT* parent_class);
   };
}

#endif
