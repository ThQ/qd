#ifndef ENGINE_H
#define ENGINE_H


#include <fstream>
#include <math.h>
#include <string>
#include <unicode/unistr.h>

#include "debug.h"
#include "svm/Array.h"
#include "svm/Block.h"
#include "svm/Bool.h"
#include "svm/Class.h"
#include "svm/ClassTable.h"
#include "svm/Exception.h"
#include "svm/Float.h"
#include "svm/Function.h"
#include "svm/FunctionTable.h"
#include "svm/Heap.h"
#include "svm/HeapObject.h"
#include "svm/Int.h"
#include "svm/IntUtil.h"
#include "svm/List.h"
#include "svm/ListUtil.h"
#include "svm/Map.h"
#include "svm/Object.h"
#include "svm/OpCode.h"
#include "svm/Parser.h"
#include "svm/Stack.h"
#include "svm/String.h"
#include "svm/UserObject.h"
#include "svm/UString.h"
#include "types.h"
// @MODULES[INCLUDE]

#define SVM_METHOD(name) svm::Object* name(svm::Engine* engine, int argc, svm::Object** argv)
#define SVM_CLASS_METHOD(name) svm::Object* name(svm::Engine* engine, svm::Object* self, int argc, svm::Object** argv)
#define SVM_THROW_CLASS_NOT_FOUND_EXCEPTION(eng, cls) \
   svm::Object* e = svm::Exception::build(); \
   e->set_class(svm::class_not_found_exception_type); \
   eng->throw_exception(e);

#define SVM_THROW_INDEX_OUT_OF_RANGE_EXCEPTION(engine, index, count) \
   svm::Object* e = svm::Exception::build(); \
   e->set_class(svm::index_out_of_range_exception_type); \
   engine->throw_exception(e);

namespace svm
{
   class Engine
   {
      public: svm::Block** blocks;
      public: UInt block_count;
      public: ClassTable classes;
      public: svm::Block* current_block;
      public: FunctionTable functions;
      public: svm::Heap heap;
      public: svm::Stack stack;

      public: Engine();
      public: ~Engine();
      public: void append_block(svm::Block* block);
      public: svm::Object* build_traceback();
      public: Object* call(std::string method_name, UInt argc, svm::Object**& argv);
      public: Object* call_object(std::string method_name, UInt argc, svm::Object**& argv);
      public: bool check_arguments(svm::Function* f, UInt argc, svm::Object**& argv);
      public: bool check_arguments(int argc, ...);
      public: void clear_arguments(UInt& argc, svm::Object**& argv);
      public: void clear_blocks();
      public: void exit();
      public: svm::Block* find_nearest_exception_handler();
      public: svm::Block* get_block(std::string name);
      public: void import_swap(svm::Block* block);
      public: static void make_empty_object_array(svm::Object**& obj, UInt count);
      public: void run_block(svm::Block* block, bool add_to_stack = true);
      // [!opcodes:prototypes]
      public: void run_file(const char* file_path);
      public: void throw_exception(svm::Object* exception);
   };

   typedef Object*(*MethodPointer)(int argc, Object** argv);
   typedef Object*(*ClassMethodPointer)(Engine* engine, Object* &self, int argc, Object** argv);
}

#endif
