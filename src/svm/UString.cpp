#include "svm/UString.h"

namespace svm
{
   Object* ustring_type = NULL;

   UString::UString()
   {
      this->references = 0;
      this->value = "";
      this->set_class(ustring_type);
   }

   Object*
   UString::append(Object* base, UnicodeString s)
   {
      SVM_ASSERT_USTRING(base);

      ((UString*)base)->value += s;
      return base;
   }

   Object*
   UString::append(Object* base, Object* s)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(s);

      ((UString*)base)->value += ((UString*)s)->value;
      return base;
   }

   Object*
   UString::append(Object* base, ULong i)
   {
      SVM_ASSERT_USTRING(base);

      char buff[33];
      sprintf(buff, "%lu", i);
      ((UString*)base)->value += buff;
      return base;
   }

   Object*
   UString::build()
   {
      return (Object*)new UString();
   }

   Object*
   UString::build(const char* s)
   {
      UString* strv = new UString();
      strv->value = s;

      return (Object*)strv;
   }

   Object*
   UString::build(UnicodeString s)
   {
      UString* result = new UString();
      result->value = s;

      return (Object*)result;
   }

   Object*
   UString::cast_to_string(Object* s)
   {
      SVM_ASSERT_USTRING(s);

      UString* str = (UString*)s;
      UString::prepend(s, "\"");
      UString::append(s, "\"");
      return (Object*)str;
   }

   bool
   UString::check(Object* obj)
   {
      return obj->cls == svm::ustring_type;
   }

   Object*
   UString::copy(Object* self)
   {
      SVM_ASSERT_USTRING(self);

      UString* result = new UString();
      result->value = ((UString*)self)->value;

      return (Object*)result;
   }


   Object*
   UString::cut_after(Object* base, Object* search)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(search);

      Object* result;

      int32_t pos = ((UString*)base)->value.indexOf(((UString*)search)->value);
      if (pos != -1)
      {
         UChar* new_string = (UChar*)malloc(sizeof(UChar) * pos);
         ((UString*)base)->value.extract(0, pos, new_string);
         result = new UString();
         ((UString*)result)->value += new_string;
      }
      else
      {
         result = base;
      }
      return result;
   }

   Object*
   UString::dump(Object* s)
   {
      SVM_ASSERT_USTRING(s);

      printf("\"");
      UString::print_unicode_string(&(((UString*)s)->value));
      printf("\"\n");

      return svm::Null;
   }

   Object*
   UString::equals(Object* s1, Object* s2)
   {
      Object* result = NULL;

      if (((UString*)s1)->value == ((UString*)s2)->value)
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

   Object*
   UString::find(Object* base, Object* substring, Object* start_at)
   {
      SVM_ASSERT_USTRING(base);
      SVM_ASSERT_USTRING(substring);
      SVM_ASSERT_INT(start_at);

      long int at = ((UString*)base)->value.indexOf(((UString*)substring)->value, ((Int*)start_at)->value);

      return Int::build(at);
   }

   Object*
   UString::join(Object* s1, Object* s2)
   {
      SVM_ASSERT_USTRING(s1);
      SVM_ASSERT_USTRING(s2);

      Object* result = UString::build();
      UString::append(result, s1);
      UString::append(result, s2);

      return result;
   }

   Object*
   UString::multiply(Object* self, Object* times)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_INT(times);

      UnicodeString pattern = ((UString*)self)->value;

      for (int i = 1 ; i < ((Int*)times)->value ; ++i)
      {
         ((UString*)self)->value.append(pattern);
      }

      return self;
   }

   Object*
   UString::print(Object* s)
   {
      SVM_ASSERT_USTRING(s);

      printf("\"");
      UString::print_unicode_string(&(((UString*)s)->value));
      printf("\"");
      return svm::Null;
   }

   void
   UString::print_unicode_string(UnicodeString* s)
   {
      for (int i = 0 ; i < s->length() ; ++ i)
      {
         printf("%c", s->char32At(i));
      }
  }

   void
   UString::print_unicode_string(UnicodeString& s)
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

   Object*
   UString::prepend(Object* s, UnicodeString s2)
   {
      SVM_ASSERT_USTRING(s);

      ((UString*)s)->value = s2 + ((UString*)s)->value;
      return s;
   }

   Object*
   UString::show(Object* s)
   {
      SVM_ASSERT_USTRING(s);

      UString::print_unicode_string(&(((UString*)s)->value));

      return svm::Null;
   }

   Object*
   UString::get_character(Object* self, Object* pos)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_INT(pos);

      long int self_len = ((UString*)self)->value.length();

      if (((Int*)pos)->value > self_len - 1)
      {
         return svm::Null;
      }

      UnicodeString c = ((UString*)self)->value.charAt(((Int*)pos)->value);
      return UString::build(c);
   }

   Object*
   UString::strip(Object* self, Object* characters, Object* start_at, Object* end_at)
   {
      SVM_ASSERT_USTRING(self);
      SVM_ASSERT_USTRING(characters);
      SVM_ASSERT_INT(start_at);
      SVM_ASSERT_INT(end_at);

      long int self_len = ((UString*)self)->value.length();
      UnicodeString base = UNICODE_STRING("", 0);
      UnicodeString chars = ((UString*)characters)->value;
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
         UChar c = ((UString*)self)->value.charAt(i);
         if (chars.indexOf(c) == -1)
         {
            base.append(c);
         }
      }

      return UString::build(base);
   }
}

