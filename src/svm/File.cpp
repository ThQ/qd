#include "svm/File.h"

namespace svm
{
   Object* file_type = NULL;

   File::File()
   {
      SVM_ASSERT_NOT_NULL(svm::file_type);
      this->set_class(svm::file_type);
      this->opened = false;
   }

   File::~File()
   {

   }

   Object*
   File::build(UnicodeString file_path)
   {
      return NULL;
   }

   Object*
   File::build(UnicodeString file_path, UnicodeString mode)
   {
      return NULL;
   }

   Object*
   File::read_all(Object* file)
   {
      char* buff = new char[1024];
      svm::String* str = new svm::String();
      while (((svm::File*)file)->file.good())
      {
         ((svm::File*)file)->file.read(buff, 1023);
         str->value.append(buff);
      }
      free(buff);
      return str;
   }

   Object*
   File::open(Object* file, Object* file_path)
   {
      SVM_ASSERT_FILE_READER(file);
      SVM_ASSERT_STRING(file_path);

      Object* result = svm::False;
      svm::File* f = ((svm::File*)file);

      f->file.open(((svm::String*)file_path)->value.c_str());
      if (f->file)
      {
         result = svm::True;
      }

      return result;
   }

   Object*
   File::write(Object* file, UnicodeString data)
   {
      return NULL;
   }
}

