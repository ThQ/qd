#ifndef MODULES_SYSTEM_LIST_H

include(`../../module.m4')

#include "t/CoreFunction.h"
#include "t/List.h"
#include "vm/Engine.h"

#define MODULES_SYSTEM_LIST_H
#define MODULE_SYSTEM_LIST

namespace modules
{
   namespace system
   {
      class List
      {
         public: static SVM_METHOD(construct)
         {
            t::Object* l = t::List::build();
            return l;
         }

         public: static SVM_CLASS_METHOD(get_item)
         {
            ASSERT(argc == 2, "system.List.get_item : 2 parameters. (Not %d)", argc);
            t::List::assert(argv[0]);
            t::List::assert(argv[1]);

            t::Object* result = t::List::get_item(argv[0], ((t::Int*)argv[1])->value);

            return result;
         }

         public: static SVM_CLASS_METHOD(pop)
         {
            ASSERT(argc == 2, "system.List.pop : 2 parameters. (Not %d)", argc);
            t::List::assert(argv[0]);
            t::Int::assert(argv[1]);

            t::Object* result = t::List::pop(argv[0], ((t::Int*)argv[1])->value);

            return result;
         }

         public: static SVM_CLASS_METHOD(push)
         {
            ASSERT(argc == 2, "system.List.push : 2 parameters. (Not %d)\n", argc);
            t::List::assert(argv[0]);
            SVM_ASSERT_NOT_NULL(argv[1]);

            t::List::append(argv[0], argv[1]);

            return t::gNULL;
         }

         public: static SVM_CLASS_METHOD(set_item)
         {
            ASSERT(argc == 3, "system.List.set_item : 3 parameters. (Not %d)\n", argc);
            t::List::assert(argv[0]);
            t::Int::assert(argv[1]);

            t::Object* result = t::List::set_item(argv[0], ((t::Int*)argv[1])->value, argv[2]);

            return result;
         }

         public: static void declare_methods(vm::Engine& engine)
         {
            SVM_ASSERT_NOT_NULL(t::tLIST);
            SVM_ASSERT_NOT_NULL(t::tINT);

            FUNCTION(`system.List.__construct__', construct)
            PARAM(`self', t::tLIST)
            RETURNS(t::tLIST)

            METHOD(t::tLIST, `get_item', get_item)
            PARAM(`self', t::tLIST)
            PARAM(`index', t::tINT)
            RETURNS(t::tOBJECT)

            METHOD(t::tLIST, `pop', pop)
            PARAM(`self', t::tLIST)
            PARAM(`num', t::tINT)
            RETURNS(t::tOBJECT)

            METHOD(t::tLIST, `push', push)
            PARAM(`self', t::tLIST)
            PARAM(`obj', t::tOBJECT)
            RETURNS(t::tOBJECT)

            METHOD(t::tLIST, `set_item', set_item)
            PARAM(`self', t::tLIST)
            PARAM(`index', t::tINT)
            PARAM(`obj', t::tOBJECT)
            RETURNS(t::tOBJECT)
         }

         public: static void finalize()
         {
            ASSERT_NULL(t::tLIST);
         }

         public: static void initialize(vm::Engine& engine)
         {
            t::tLIST = engine.classes.declare_class("system.List", t::tOBJECT);
            t::Class::assert(t::tLIST);
            t::Object::pick(t::tLIST);
         }

         public: static void tear_down(vm::Engine& engine)
         {
            t::Object::drop(t::tLIST);
         }
      };

   }
}

#endif
