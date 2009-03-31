#ifndef T_FILE
#define T_FILE NS_TYPE::File

#include <iostream>
#include <fstream>
#include <string>

#include "t/Bool.h"
#include "t/Object.h"
#include "t/String.h"

#ifdef _ALLOW_SVM_ASSERTATIONS_
   #define SVM_ASSERT_FILE_READER(f) \
   DEPRECATED(); \
   if(f->cls != NS_TYPE::tTYPE) \
   { \
      FATAL("Bad type, <system.io.FileReader> expected."); \
      abort(); \
   }
#else
   #define SVM_ASSERT_FILE_READER(f) DEPRECATED();
#endif

namespace NS_TYPE
{
   extern T_OBJECT* tFILE;

   class File : public T_OBJECT
   {
      public: std::string file_path;
      public: std::ifstream file;
      public: bool opened;

      public: File();
      public: static T_OBJECT* open(T_OBJECT* file, T_OBJECT* file_path);
      public: static T_OBJECT* read_all(T_OBJECT* file);
   };
}

#endif
