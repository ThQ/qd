#ifndef SVM_STRING_H
#define SVM_STRING_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef ALLOW_UNICODE
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#endif

#include "debug.h"
#include "svm/Bool.h"
#include "svm/Int.h"
#include "svm/Object.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_STRING(s) SVM_ASSERT_NOT_NULL(s); if(!svm::String::check(s)){FATAL("Bad type given, expected system.String\n\n");abort();}
#else
   #define SVM_ASSERT_STRING(s)
#endif


#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_STRING(s) SVM_CHECK_NOT_NULL(s); if(!svm::String::check(s)){WARNING("Bad type given, expected system.String\n\n");}
#else
   #define SVM_CHECK_STRING(s)
#endif

namespace svm
{
   extern Object* string_type;

   class String : public Object
   {
      public: std::string value;

      public: String();
      #ifdef ALLOW_UNICODE
      public: static Object* append(Object* base, UnicodeString s);
      #endif
      public: static Object* append(Object* base, Object* s);
      public: static Object* append(Object* base, ULong i);
      public: static Object* append(Object* base, char c);
      public: static Object* build();
      public: static Object* build(Object* s);
      public: static Object* build(char c);
      public: static Object* build(const char* s);
      public: static Object* build(std::string s);
      #ifdef ALLOW_UNICODE
      public: static Object* build(UnicodeString s);
      #endif
      public: static Object* cast_to_string(Object* s);
      public: static Object* center(Object* s_base, Object* i_length, Object* s_padding);
      public: static bool check(Object* obj);
      public: static Short compare_to(Object* s1, Object* s2);
      public: static Object* copy(Object* self);
      public: static Object* cut_after(Object* base, Object* search);
      public: static Object* cut_at(Object* base, Object* at);
      public: static Object* equals(Object* s1, Object* s2);
      public: static Object* find(Object* s, Object* search, Object* start_at);
      public: static Object* get_character(Object* self, Object* pos);
      public: static Object* get_length(Object* s);
      public: static Object* insert(Object* s, Object* sub, ULong at);
      public: static Object* is_alphabetic(Object* s);
      public: static Object* is_digit(Object* s);
      public: static Object* is_lowercase(Object* s);
      public: static Object* is_space(Object* s);
      public: static Object* is_uppercase(Object* s);
      public: static Object* lower(Object* s);
      public: static Object* lpad(Object* base, ULong len, Object* spad);
      public: static Object* join(Object* s1, Object* s2);
      public: static Object* multiply(Object* self, Object* times);
      public: static Object* pad(Object* base, ULong len, Object* spad);
      public: static Object* prepend(Object* s1, Object* s2);
      public: static void print(Object* s);
      public: static void print_line(Object* s);
      public: static Object* reverse(Object* self);
      public: static Object* strip(Object* self, Object* characters, Object* start_at, Object* end_at);
      public: static Object* swap_case(Object* self);
      public: static Object* upper(Object* s);
   };
}

#endif

