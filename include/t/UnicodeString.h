#ifdef NODIA_ALLOW_UNICODE
#ifndef T_UNICODE_STRING_H
#define T_UNICODE_STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>

#include "t/Bool.h"
#include "t/Int.h"
#include "t/Object.h"

typedef NS_TYPE::UnicodeString T_UNICODE_STRING;

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_USTRING(s) DEPRECATED(); SVM_ASSERT_NOT_NULL(s); if(!T_UNICODE_STRING::check(s)){FATAL("Bad type given, expected system.UString\n\n");abort();}
#else
   #define SVM_ASSERT_USTRING(s) DEPRECATED();
#endif


#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_USTRING(s) DEPRECATED(); SVM_CHECK_NOT_NULL(s); if(!T_UNICODE_STRING::check(s)){WARNING("Bad type given, expected system.UString\n\n");}
#else
   #define SVM_CHECK_USTRING(s) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* ustring_type;

   class UnicodeString : public Object
   {
      public: UnicodeString value;

      public: UString();
      public: static T_OBJECT* append(T_OBJECT* base, UnicodeString s);
      public: static T_OBJECT* append(T_OBJECT* base, T_OBJECT* s);
      public: static T_OBJECT* append(T_OBJECT* base, ULong i);
      public: static T_OBJECT* build();
      public: static T_OBJECT* build(const char* s);
      public: static T_OBJECT* build(UnicodeString s);
      public: static T_OBJECT* cast_to_string(T_OBJECT* s);
      public: static bool check(T_OBJECT* obj);
      public: static T_OBJECT* copy(T_OBJECT* self);
      public: static T_OBJECT* cut_after(T_OBJECT* base, T_OBJECT* search);
      public: static T_OBJECT* dump(T_OBJECT* s);
      public: static T_OBJECT* equals(T_OBJECT* s1, T_OBJECT* s2);
      public: static T_OBJECT* find(T_OBJECT* s, T_OBJECT* search, T_OBJECT* start_at);
      public: static T_OBJECT* get_character(T_OBJECT* self, T_OBJECT* pos);
      public: static T_OBJECT* join(T_OBJECT* s1, T_OBJECT* s2);
      public: static T_OBJECT* multiply(T_OBJECT* self, T_OBJECT* times);
      public: static T_OBJECT* prepend(T_OBJECT* base, UnicodeString s);
      public: static T_OBJECT* print(T_OBJECT* s);
      public: static T_OBJECT* show(T_OBJECT* s);
      public: static T_OBJECT* strip(T_OBJECT* self, T_OBJECT* characters, T_OBJECT* start_at, T_OBJECT* end_at);
      public: static void print_unicode_string(T_UNICODE_STRING* s);
      public: static void print_unicode_string(T_UNICODE_STRING& s);
   };
}

#endif
#endif
