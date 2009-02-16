#ifndef SVM_FILE_H
#define SVM_FILE_H

#include <iostream>
#include <fstream>
#include <unicode/putil.h>
#include <string>

#include "svm/Bool.h"
#include "svm/Object.h"
#include "svm/String.h"

#ifdef _ALLOW_SVM_ASSERTATIONS_
#define SVM_ASSERT_FILE_READER(f) if(f->cls != svm::file_type){FATAL("Bad type, <system.io.FileReader> expected.");abort();}
#else
#define SVM_ASSERT_FILE_READER(f)
#endif

namespace svm
{
   extern Object* file_type;

   class File : public Object
   {
      public: std::string file_path;
      public: std::ifstream file;
      public: bool opened;

      public: File();
      public: ~File();
      public: Object* build(UnicodeString file_path);
      public: Object* build(UnicodeString file_path, UnicodeString mode);
      public: static Object* open(Object* file, Object* file_path);
      public: static Object* read_all(Object* file);
      public: Object* write(Object* file, UnicodeString data);
   };
}

#endif
