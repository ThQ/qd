#ifndef ENGINE_H
#define ENGINE_H


#include <fstream>
#include <math.h>
#include <string>
#include <unicode/unistr.h>

#include "t/Array.h"
#include "t/Block.h"
#include "t/Bool.h"
#include "t/Class.h"
#include "vm/ClassTable.h"
#include "t/Exception.h"
#include "t/Float.h"
#include "t/Function.h"
#include "vm/FunctionTable.h"
#include "vm/Heap.h"
#include "vm/HeapObject.h"
#include "t/Int.h"
#include "vm/IntUtil.h"
#include "t/List.h"
#include "vm/ListUtil.h"
#include "t/Map.h"
#include "t/Object.h"
#include "vm/OpCode.h"
#include "vm/Parser.h"
#include "vm/Stack.h"
#include "t/String.h"
#include "vm/UserObject.h"
#include "t/UnicodeString.h"
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

namespace NS_VM
{
   class Engine
   {
      public: t::Block** blocks;
      public: UInt block_count;
      public: ClassTable classes;
      public: t::Block* current_block;
      public: FunctionTable functions;
      public: Heap heap;
      public: Stack stack;

      public: Engine();
      public: ~Engine();
      public: void append_block(t::Block* block);
      public: svm::Object* build_traceback();
      public: t::Object* call(std::string method_name, UInt argc, t::Object**& argv);
      public: t::Object* call_object(std::string method_name, UInt argc, t::Object**& argv);
      public: bool check_arguments(t::Function* f, UInt argc, t::Object**& argv);
      public: bool check_arguments(int argc, ...);
      public: void clear_arguments(UInt& argc, t::Object**& argv);
      public: void clear_blocks();
      public: void exit();
      public: t::Block* find_nearest_exception_handler();
      public: t::Block* get_block(std::string name);
      public: void import_swap(t::Block* block);
      public: static void make_empty_object_array(t::Object**& obj, UInt count);
      public: void run_block(t::Block* block, bool add_to_stack = true);
      // [!opcodes:prototypes]
      public: void run_file(const char* file_path);
      public: void throw_exception(t::Object* exception);
   };

   typedef Object*(*MethodPointer)(int argc, t::Object** argv);
   typedef Object*(*ClassMethodPointer)(Engine* engine, t::Object* &self, int argc, t::Object** argv);
}

#endif
