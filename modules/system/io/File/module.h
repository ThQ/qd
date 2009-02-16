#ifndef MODULES_SYSTEM_IO_FILE_H
#define MODULES_SYSTEM_IO_FILE_H

include(`../../../module.m4')


#include "debug.h"
#include "svm/CoreFunction.h"
#include "svm/File.h"

namespace modules { namespace system { namespace io {

   class File
   {
      public: static SVM_CLASS_METHOD(construct)
      {
         svm::Object* f = (svm::Object*)new svm::File();

         SVM_ASSERT_NOT_NULL(f);
         return f;
      }

      public: static SVM_CLASS_METHOD(open)
      {
         SVM_ASSERT_FILE_READER(argv[0]); // svm::File* file
         SVM_ASSERT_STRING(argv[1]); // svm::String* File path
         return svm::File::open(argv[0], argv[1]);
      }

      public: static SVM_CLASS_METHOD(read_all)
      {
         SVM_ASSERT_FILE_READER(argv[0]); //svm::File* file

         return svm::File::read_all(argv[0]);
      }

      public: static void declare_methods(svm::Engine& engine)
      {
         SVM_ASSERT_NOT_NULL(svm::file_type);

         FUNCTION(`system.io.FileReader.__construct__', construct)
         RETURNS(svm::file_type);

         METHOD(svm::file_type, `open', open)
         PARAM(`self', svm::file_type)
         PARAM(`file_path', svm::string_type)
         RETURNS(svm::bool_type)

         METHOD(svm::file_type, `read_all', read_all)
         PARAM(`self', svm::file_type)
         RETURNS(svm::string_type);
      }

      public: static void initialize(svm::Engine& engine)
      {
         svm::file_type = engine.classes.declare_class("system.io.FileReader", svm::object_type);
         SVM_ASSERT_CLASS(svm::file_type);
         SVM_PICK(svm::file_type);
      }

      public: static void tear_down(svm::Engine& engine)
      {
         SVM_DROP(svm::file_type);
      }
   };

} } }

#endif
