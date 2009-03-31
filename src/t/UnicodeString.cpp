#ifdef NODIA_ALLOW_UNICODE
#include "t/UnicodeString.h"

namespace NS_TYPE
{
   T_OBJECT* ustring_type = NULL;

   UnicodeString::UnicodeString()
   {
      this->references = 0;
      this->value = "";
      this->set_class(ustring_type);
   }

   T_OBJECT*
   UnicodeString::append(T_OBJECT* base, UnicodeString s)
   {
      SVM_ASSERT_USTRING(base);

      ((T_UNICODE_STRING*)base)->value += s;
      return base;
   }

   T_OBJECT*
   UnicodeString::append(T_OBJECT* base, T_OBJECT* s)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(s);

      ((T_UNICODE_STRING*)base)->value += ((T_UNICODE_STRING*)s)->value;
      return base;
   }

   T_OBJECT*
   UnicodeString::append(T_OBJECT* base, ULong i)
   {
      SVM_ASSERT_USTRING(base);

      char buff[33];
      sprintf(buff, "%lu", i);
      ((T_UNICODE_STRING*)base)->value += buff;
      return base;
   }

   T_OBJECT*
   UnicodeString::build()
   {
      return (T_OBJECT*)new UString();
   }

   T_OBJECT*
   UnicodeString::build(const char* s)
   {
      T_UNICODE_STRING* strv = new UString();
      strv->value = s;

      return (T_OBJECT*)strv;
   }

   T_OBJECT*
   UnicodeString::build(UnicodeString s)
   {
      T_UNICODE_STRING* result = new UString();
      result->value = s;

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   UnicodeString::cast_to_string(T_OBJECT* s)
   {
      SVM_ASSERT_USTRING(s);

      T_UNICODE_STRING* str = (T_UNICODE_STRING*)s;
      UnicodeString::prepend(s, "\"");
      UnicodeString::append(s, "\"");
      return (T_OBJECT*)str;
   }

   bool
   UnicodeString::check(T_OBJECT* obj)
   {
      return obj->cls == svm::ustring_type;
   }

   T_OBJECT*
   UnicodeString::copy(T_OBJECT* self)
   {
      SVM_ASSERT_USTRING(self);

      T_UNICODE_STRING* result = new UString();
      result->value = ((T_UNICODE_STRING*)self)->value;

      return (T_OBJECT*)result;
   }


   T_OBJECT*
   UnicodeString::cut_after(T_OBJECT* base, T_OBJECT* search)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(search);

      T_OBJECT* result;

      int32_t pos = ((T_UNICODE_STRING*)base)->value.indexOf(((T_UNICODE_STRING*)search)->value);
      if (pos != -1)
      {
         UChar* new_string = (UChar*)malloc(sizeof(UChar) * pos);
         ((T_UNICODE_STRING*)base)->value.extract(0, pos, new_string);
         result = new UString();
         ((T_UNICODE_STRING*)result)->value += new_string;
      }
      else
      {
         result = base;
      }
      return result;
   }

   T_OBJECT*
   UnicodeString::dump(T_OBJECT* s)
   {
      SVM_ASSERT_USTRING(s);

      printf("\"");
      UnicodeString::print_unicode_string(&(((T_UNICODE_STRING*)s)->value));
      printf("\"\n");

      return svm::Null;
   }

   T_OBJECT*
   UnicodeString::equals(T_OBJECT* s1, T_OBJECT* s2)
   {
      T_OBJECT* result = NULL;

      if (((T_UNICODE_STRING*)s1)->value == ((T_UNICODE_STRING*)s2)->value)
      {
         result = svm::True;
      }
      else
      {
         result = svm::False;
      }
      ASSERT_NOT_NULL(result);
      return result;
   }

   T_OBJECT*
   UnicodeString::find(T_OBJECT* base, T_OBJECT* substring, T_OBJECT* start_at)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(substring);
      SVM_ASSERT_INT(start_at);

      long int at = ((T_UNICODE_STRING*)base)->value.indexOf(((T_UNICODE_STRING*)substring)->value, ((Int*)start_at)->value);

      return Int::build(at);
   }

   T_OBJECT*
   UnicodeString::join(T_OBJECT* s1, T_OBJECT* s2)
   {
      SVM_ASSERT_USTRING(s1);
      SVM_ASSERT_USTRING(s2);

      T_OBJECT* result = UnicodeString::build();
      UnicodeString::append(result, s1);
      UnicodeString::append(result, s2);

      return result;
   }

   T_OBJECT*
   UnicodeString::multiply(T_OBJECT* self, T_OBJECT* times)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_INT(times);

      UnicodeString pattern = ((T_UNICODE_STRING*)self)->value;

      for (int i = 1 ; i < ((Int*)times)->value ; ++i)
      {
         ((T_UNICODE_STRING*)self)->value.append(pattern);
      }

      return self;
   }

   T_OBJECT*
   UnicodeString::print(T_OBJECT* s)
   {
      SVM_ASSERT_USTRING(s);

      printf("\"");
      UnicodeString::print_unicode_string(&(((T_UNICODE_STRING*)s)->value));
      printf("\"");
      return svm::Null;
   }

   void
   UnicodeString::print_unicode_string(UnicodeString* s)
   {
      for (int i = 0 ; i < s->length() ; ++ i)
      {
         printf("%c", s->char32At(i));
      }
  }

   void
   UnicodeString::print_unicode_string(UnicodeString& s)
   {
      for (int i = 0 ; i < s.length() ; ++ i)
      {
         printf("%c", s.char32At(i));
      }
      /*UErrorCode e;
      UConverter* u = ucnv_open(NULL, &e);
      const UChar* src = s.getBuffer();
      int size = s.length() * 2;
      char* dest = new char[size];
      ucnv_fromUChars(u,
         dest,
         size,
         src,
         s.length(),
         &e);
      printf("%s", dest);
      */
   }

   T_OBJECT*
   UnicodeString::prepend(T_OBJECT* s, UnicodeString s2)
   {
      SVM_ASSERT_USTRING(s);

      ((T_UNICODE_STRING*)s)->value = s2 + ((T_UNICODE_STRING*)s)->value;
      return s;
   }

   T_OBJECT*
   UnicodeString::show(T_OBJECT* s)
   {
      SVM_ASSERT_USTRING(s);

      UnicodeString::print_unicode_string(&(((T_UNICODE_STRING*)s)->value));

      return svm::Null;
   }

   T_OBJECT*
   UnicodeString::get_character(T_OBJECT* self, T_OBJECT* pos)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_INT(pos);

      long int self_len = ((T_UNICODE_STRING*)self)->value.length();

      if (((Int*)pos)->value > self_len - 1)
      {
         return svm::Null;
      }

      UnicodeString c = ((T_UNICODE_STRING*)self)->value.charAt(((Int*)pos)->value);
      return UnicodeString::build(c);
   }

   T_OBJECT*
   UnicodeString::strip(T_OBJECT* self, T_OBJECT* characters, T_OBJECT* start_at, T_OBJECT* end_at)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_USTRING(characters);
      T_INT::assert(start_at);
      T_INT::assert(end_at);

      long int self_len = ((T_UNICODE_STRING*)self)->value.length();
      UnicodeString base = UNICODE_STRING("", 0);
      UnicodeString chars = ((T_UNICODE_STRING*)characters)->value;
      long int start, end;

      if (((Int*)start_at)->value == 0 || ((Int*)start_at)->value < 0) start = 0;
      else if (((Int*)start_at)->value > self_len) start = self_len;
      else start = ((Int*)start_at)->value;

      if (((Int*)end_at)->value == -1) end = self_len;
      else if (((Int*)end_at)->value > self_len) end = self_len;
      else if (((Int*)end_at)->value < 0) end = self_len;
      else end = ((Int*)end_at)->value;

      for (long int i = start ; i < end ; ++i)
      {
         UChar c = ((T_UNICODE_STRING*)self)->value.charAt(i);
         if (chars.indexOf(c) == -1)
         {
            base.append(c);
         }
      }

      return UnicodeString::build(base);
   }
}

#endif
