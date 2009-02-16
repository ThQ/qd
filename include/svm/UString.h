#ifndef SVM_USTRING_H
#define SVM_USTRING_H


#include <stdlib.h>
#include <stdio.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>

#include "debug.h"
#include "svm/Bool.h"
#include "svm/Int.h"
#include "svm/Object.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_USTRING(s) SVM_ASSERT_NOT_NULL(s); if(!svm::UString::check(s)){FATAL("Bad type given, expected system.UString\n\n");abort();}
#else
   #define SVM_ASSERT_USTRING(s)
#endif


#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_USTRING(s) SVM_CHECK_NOT_NULL(s); if(!svm::UString::check(s)){WARNING("Bad type given, expected system.UString\n\n");}
#else
   #define SVM_CHECK_USTRING(s)
#endif

namespace svm
{
   extern Object* ustring_type;

   class UString : public Object
   {
      public: UnicodeString value;

      public: UString();
      public: static Object* append(Object* base, UnicodeString s);
      public: static Object* append(Object* base, Object* s);
      public: static Object* append(Object* base, ULong i);
      public: static Object* build();
      public: static Object* build(const char* s);
      public: static Object* build(UnicodeString s);
      public: static Object* cast_to_string(Object* s);
      public: static bool check(Object* obj);
      public: static Object* copy(Object* self);
      public: static Object* cut_after(Object* base, Object* search);
      public: static Object* dump(Object* s);
      public: static Object* equals(Object* s1, Object* s2);
      public: static Object* find(Object* s, Object* search, Object* start_at);
      public: static Object* get_character(Object* self, Object* pos);
      public: static Object* join(Object* s1, Object* s2);
      public: static Object* multiply(Object* self, Object* times);
      public: static Object* prepend(Object* base, UnicodeString s);
      public: static Object* print(Object* s);
      public: static Object* show(Object* s);
      public: static Object* strip(Object* self, Object* characters, Object* start_at, Object* end_at);
      public: static void print_unicode_string(UnicodeString* s);
      public: static void print_unicode_string(UnicodeString& s);
   };
}

#endif

