#ifndef T_STRING
#define T_STRING t::String

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef ALLOW_UNICODE
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#endif

#include "t/Bool.h"
#include "t/Int.h"
#include "t/Object.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_STRING(s) SVM_ASSERT_NOT_NULL(s); \
   DEPRECATED(); \
   if(!T_STRING::check(s)) \
   { \
      FATAL("Bad type given, expected system.String\n\n"); \
      abort(); \
   }
#else
   #define SVM_ASSERT_STRING(s) DEPRECATED();
#endif


#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_STRING(s) SVM_CHECK_NOT_NULL(s); \
   DEPRECATED(); \
   if(!T_STRING::check(s)) \
   { \
      WARNING("Bad type given, expected system.String\n\n"); \
   }
#else
   #define SVM_CHECK_STRING(s) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* string_type;

   class String : public T_OBJECT
   {
      public: std::string value;

      public: String();
      #ifdef ALLOW_UNICODE
      public: static T_OBJECT* append(T_OBJECT* base, UnicodeString s);
      #endif
      public: static T_OBJECT* append(T_OBJECT* base, T_OBJECT* s);
      public: static T_OBJECT* append(T_OBJECT* base, ULong i);
      public: static T_OBJECT* append(T_OBJECT* base, char c);

      /**
       * Asserts that an object is of type t::String.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         ASSERT_NOT_NULL(NS_TYPE::string_type);
         T_OBJECT::assert_type(obj, NS_TYPE::string_type);
      }

      public: static T_OBJECT* build();

      /**
       * Creates a t::String by copying another one.
       */
      public: static T_OBJECT* build(T_OBJECT* s);

      /**
       * Creates a t::String by using a C char.
       */
      public: static T_OBJECT* build(char c);

      /**
       * Creates a t::String by using a C string.
       */
      public: static T_OBJECT* build(const char* s);

      /**
       * Creates a t::String by using a std::string.
       */
      public: static T_OBJECT* build(std::string s);
      #ifdef ALLOW_UNICODE
      public: static T_OBJECT* build(UnicodeString s);
      #endif
      public: static T_OBJECT* cast_to_string(T_OBJECT* s);
      public: static T_OBJECT* center(T_OBJECT* s_base, T_OBJECT* i_length, T_OBJECT* s_padding);

      /*
       * Checks if an object is of type t::String.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::string_type);
      }

      public: static Short compare_to(T_OBJECT* s1, T_OBJECT* s2);
      public: static T_OBJECT* copy(T_OBJECT* self);
      public: static T_OBJECT* cut_after(T_OBJECT* base, T_OBJECT* search);
      public: static T_OBJECT* cut_at(T_OBJECT* base, T_OBJECT* at);

      /**
       * Checks if two strings are equal.
       */
      public: static T_OBJECT* equals(T_OBJECT* s1, T_OBJECT* s2);

      /**
       * Finds a t::String substring in another t::String, starting from
       * <start_at>.
       */
      public: static T_OBJECT* find(T_OBJECT* s, T_OBJECT* search, T_OBJECT* start_at);

      /**
       * Returns the character at <po> in <self> as a t::String.
       */
      public: static T_OBJECT* get_character(T_OBJECT* self, T_OBJECT* pos);

      /**
       * Returns the length of a t::String.
       */
      public: static T_OBJECT* get_length(T_OBJECT* s);

      /**
       * Inserts a t::String substring <sub> in another t::String <s>, at <at>.
       */
      public: static T_OBJECT* insert(T_OBJECT* s, T_OBJECT* sub, ULong at);

      /**
       * Returns t::True if t::String <s> only contains letters.
       */
      public: static T_OBJECT* is_alphabetic(T_OBJECT* s);

      /**
       * Returns t::True if a t::String only contains digits.
       */
      public: static T_OBJECT* is_digit(T_OBJECT* s);

      /**
       * Returns t::True if all letters contained in a t::String are lower case.
       */
      public: static T_OBJECT* is_lowercase(T_OBJECT* s);

      /**
       * Returns t::True if a t::String only contains space characters.
       */
      public: static T_OBJECT* is_space(T_OBJECT* s);

      /**
       * Returns t::True if all letters contained in a t::String are upper case.
       */
      public: static T_OBJECT* is_uppercase(T_OBJECT* s);

      /**
       * Converts all upper case letters to lower case.
       */
      public: static T_OBJECT* lower(T_OBJECT* s);
      public: static T_OBJECT* lpad(T_OBJECT* base, ULong len, T_OBJECT* spad);

      /**
       * Creates a t::String by joining two other strings.
       */
      public: static T_OBJECT* join(T_OBJECT* s1, T_OBJECT* s2);
      public: static T_OBJECT* multiply(T_OBJECT* self, T_OBJECT* times);
      public: static T_OBJECT* pad(T_OBJECT* base, ULong len, T_OBJECT* spad);
      public: static T_OBJECT* prepend(T_OBJECT* s1, T_OBJECT* s2);

      /**
       * Prints the content of a t::String.
       */
      public: static void print(T_OBJECT* s);

      /**
       * Prints the content of a t::String on a new line.
       */
      public: static void print_line(T_OBJECT* s);

      /**
       * Reverses the characters of a t::String.
       */
      public: static T_OBJECT* reverse(T_OBJECT* self);

      /**
       * Strips white characters off a t::String <self.>
       */
      public: static T_OBJECT* strip(T_OBJECT* self, T_OBJECT* characters, T_OBJECT* start_at, T_OBJECT* end_at);

      /**
       * Changes all lowercased characters to upper case, and all uppercased
       * characters to lower case.
       */
      public: static T_OBJECT* swap_case(T_OBJECT* self);

      /**
       * Converts all upper case letters to lower case.
       */
      public: static T_OBJECT* upper(T_OBJECT* s);
   };
}

#endif

