#include "t/File.h"

namespace NS_TYPE
{
   T_OBJECT* tFILE = NULL;

   File::File()
   {
      T_OBJECT::assert_not_null(NS_TYPE::tFILE);
      this->set_class(NS_TYPE::tFILE);
      this->opened = false;
   }

   T_OBJECT*
   File::read_all(T_OBJECT* file)
   {
      char* buff = new char[1024];
      T_STRING* str = new T_STRING();
      while (((T_FILE*)file)->file.good())
      {
         ((T_FILE*)file)->file.read(buff, 1023);
         str->value.append(buff);
      }
      free(buff);
      return str;
   }

   T_OBJECT*
   File::open(T_OBJECT* file, T_OBJECT* file_path)
   {
      //SVM_ASSERT_FILE_READER(file);
      T_STRING::assert(file_path);

      T_OBJECT* result = NS_TYPE::gFALSE;
      T_FILE* f = ((T_FILE*)file);

      f->file.open(((T_STRING*)file_path)->value.c_str());
      if (f->file)
      {
         result = NS_TYPE::gTRUE;
      }

      return result;
   }
}
