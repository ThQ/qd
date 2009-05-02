#include "vm/ClassTable.h"

namespace NS_VM
{
   ClassTable::ClassTable()
   {
      this->items = NULL;
      this->item_count = 0;
   }

   ClassTable::~ClassTable()
   {
      for (ULong i = 0 ; i < item_count ; ++i)
      {
         delete this->items[i];
         this->items[i] = NULL;
      }
      free(this->items);
      this->items = NULL;
      this->item_count = 0;
   }

   void
   ClassTable::append(t::Class* cls)
   {
      ASSERT(cls != NULL, "Cannot append a NULL t::Class*.\n");

      ClassTableEntry* entry = new ClassTableEntry();
      entry->set_class(cls);
      this->append(entry);
   }

   void
   ClassTable::append(ClassTableEntry* entry)
   {
      /*INTERNAL(
         "ClassTable[@%lu] : append entry with class <%s>... ",
         (ULong)this,
         ((Class*)entry.cls)->name.c_str()
      );*/

      #ifdef __DEBUG__
      if (this->has(((t::Class*)entry->cls)->name))
      {
         FATAL(
            "ClassTable[@%lu] : <%s> already declared.",
            (ULong)this,
            ((t::Class*)entry->cls)->name.c_str()
         );
         abort();
      }
      #endif

      // @TODO: Find a better way than systematic resizing (linked list?)
      this->item_count ++;
      this->items = (ClassTableEntry**)REALLOC(this->items, sizeof(ClassTableEntry*) * this->item_count);
      ASSERT_REALLOC(this->items);
      this->items[this->item_count - 1] = entry;

      /*INTERNAL_APD("OK\n");*/
   }

   bool
   ClassTable::append_method_to(t::Class* cls, t::Function* func)
   {
      //INTERNAL("ClassTable::append_method_to(Class*(@%lu), Function*(@%lu))\n", (ULong)cls, (ULong)func);
      t::Object::assert_not_null(cls);
      t::Object::assert_not_null(func);

      bool result = false;
      long index = this->find(cls);

      if (index != - 1)
      {
         if (this->items[index]->functions.has(func) == false)
         {
            /*INTERNAL(
               "<svm::ClassTable(@%lu): Appending <svm::Function(@%lu)[name=\"%s\"] to <svm::Class(@%lu)>[name=\"%s\"] @ %lu : %lu + 1...\n",
               (ULong)this,
               (ULong)func,
               func->name.c_str(),
               (ULong)cls,
               cls->name.c_str(),
               index,
               this->items[index].functions.count()
            );*/

            this->items[index]->functions.append(func);

            //INTERNAL("OK (%lu methods now)\n", this->items[index].functions.count());
         }
         #ifdef _DEBUG_
         else
         {
            long func_index = this->items[index]->functions.find(func->name);
            ASSERT(func_index != -1, "Function must be findable at this point.");

            WARNING(
               "<t::Class*(@%lu)> has already a <svm::Function*(@%lu)> named <%s> at index %ld, along with: \n",
               (ULong)cls,
               (ULong)func,
               this->items[index]->functions.functions[func_index]->function->name.c_str(),
               func_index
            );
            this->items[index]->functions.list();
         }
         #endif
         result = true;
      }
      #ifdef _DEBUG_
      else
      {
         WARNING(
            "<t::Class*(@%lu)> [name=\"%s\"] not found.\n",
            (ULong)this,
            cls->name.c_str()
         );
      }
      this->assert_validity();
      #endif

      //INTERNAL("/ ClassTable::append_method_to(Class*(@%lu), Function*(@%lu))\n", (ULong)cls, (ULong)func);


      return result;
   }

   #ifdef _DEBUG_
   void
   ClassTable::assert_validity()
   {
      for (ULong i = 0 ; i < this->item_count ; ++i)
      {
         this->items[i]->functions.assert_validity();
      }
   }

   #endif

   /*bool
   ClassTable::declare_fields(t::Class* cls, ULong field_count, svm::Variable** fields)
   {
      bool result = false;
      long class_index = this->find(cls);
      if (class_index != -1)
      {
         ClassTableEntry e = this->items[class_index];
         e.fields.set_fields(field_count, fields);
         result = true;
      }
      return result;
   }
   */

   ULong
   ClassTable::count()
   {
      return this->item_count;
   }

   t::Object*
   ClassTable::declare_class(const char* class_name)
   {
      t::Object* cls = t::Class::build(class_name);
      this->append((t::Class*)cls);
      return cls;
   }

   t::Object*
   ClassTable::declare_class(const char* class_name, t::Object* parent_class)
   {
      t::Class::assert(parent_class);

      t::Object* cls = t::Class::build(class_name, parent_class);
      this->append((t::Class*)cls);
      return cls;
   }

   t::Object*
   ClassTable::declare_class(const char* class_name, const char* parent_class_name)
   {
      std::string s_class_name;
      std::string s_parent_class_name;
      s_class_name.assign(class_name);
      s_parent_class_name.assign(parent_class_name);
      t::Object* result = NULL;
      long class_index = this->find(s_parent_class_name);
      if (class_index != -1)
      {
         result = this->declare_class(class_name, this->items[class_index]->cls);
      }

      t::Object::assert_not_null(result);

      return result;
   }

   t::Object*
   ClassTable::declare_method(t::Class* cls, t::CoreFunction* func)
   {
      this->append_method_to(cls, (t::Function*)func);

      return func;
   }

   t::Object*
   ClassTable::declare_method(t::Class* cls, t::UserFunction* func)
   {
      this->append_method_to(cls, (t::Function*)func);

      return func;
   }

   t::Object*
   ClassTable::declare_method(t::Object* cls, t::Object* func)
   {
      //INTERNAL("> opcode::declare_method(Object*(Class*)(@%lu), Object*(Function*)(@%lu))\n", (ULong)cls, (ULong)func);
      t::Class::assert(cls);
      t::Function::assert(func);

      this->append_method_to((t::Class*)cls, (t::Function*)func);
      //INTERNAL("< opcode::declare_method(Object*(Class*)(@%lu), Object*(Function*)(@%lu))\n", (ULong)cls, (ULong)func);

      return func;
   }

   t::Object*
   ClassTable::declare_method(t::Class* cls, t::Object* func)
   {
      t::Function::assert(func);

      #ifdef _DEBUG_
      if (!this->has(cls))
      {
         WARNING("Cannot find class <%s>.\n", cls->name.c_str());
      }
      if (this->has_method(cls, (t::Function*)func))
      {
         WARNING("Method <%s> already declared.\n", ((t::Function*)func)->name.c_str());
      }
      #endif

      this->append_method_to(cls, (t::Function*)func);

      #ifdef _SHOW_INTERNAL_
      /*svm::Function* f = (svm::Function*)func;
      INTERNAL(
         "opcode::class_methods += <svm::Function:%s>[argument_count=%d]",
         f->name.c_str(),
         f->arguments_count
      );
      */
      #endif

      return func;
   }

   /*t::Object*
   ClassTable::declare_function(t::Object* func)
   {
      SVM_ASSERT_NOT_NULL(func);

      this->append((svm::Function*)func);
      ++ opcode::method_count;
      opcode::methods = (t::Object**)realloc(opcode::methods, sizeof(t::Object*) * opcode::method_count);
      ASSERT_REALLOC(opcode::methods);
      opcode::methods[opcode::method_count - 1] = func;
      SVM_PICK(func);

      #ifdef _DEBUG_
      svm::Function* f = (svm::Function*)func;
      INTERNAL("opcode::methods += <");
      svm::String::print_unicode_string(&f->name);
      printf(">(<arguments_count:%u>)\n", f->arguments_count);
      #endif

      return func;
   }
   */

   long
   ClassTable::find(Class* cls)
   {
      long result = -1;
      for (ULong i = 0 ; i < this->item_count ; ++i)
      {
         if (this->items[i]->cls == cls)
         {
            result = i;
            break;
         }
      }
      return result;
   }

   long
   ClassTable::find(std::string name)
   {
      long result = -1;
      for (ULong i = 0 ; i < this->item_count ; ++i)
      {
         if (this->items[i]->cls->name.compare(name) == 0)
         {
            result = i;
            break;
         }
      }
      return result;
   }

   t::Class*
   ClassTable::get(std::string name)
   {
      long index = this->find(name);
      t::Class* result = NULL;
      if (index != -1)
      {
         result = this->items[index]->cls;
      }

      t::Object::assert_not_null(result);
      return result;
   }

   t::Function*
   ClassTable::get_method(std::string class_name, std::string func_name)
   {
      t::Class* cls = this->get(class_name);
      return this->get_method(cls, func_name);
   }

   t::Function*
   ClassTable::get_method(t::Class* cls, std::string func)
   {
      t::Function* result = NULL;
      while (result == NULL)
      {
         long index = this->find(cls);
         if (index != - 1)
         {
            result = this->items[index]->functions.get(func);
         }
         #if _SHOW_WARNINGS_
         else
         {
            WARNING("Cannot find class <%s>.\n", cls->name.c_str());
            break;
         }
         #endif
         if (result == NULL && cls->parent_class != NULL)
         {
            cls = (t::Class*)cls->parent_class;
         }
         else
         {
            break;
         }
      }

      t::Object::assert_not_null(result);

      return result;
   }

   bool
   ClassTable::has(std::string name)
   {
      return this->find(name) != -1;
   }

   bool
   ClassTable::has(t::Class* cls)
   {
      return this->find(cls) != -1;
   }

   bool
   ClassTable::has_method(t::Class* cls, std::string name)
   {
      bool result = false;
      long index = this->find(cls);
      if (index != -1)
      {
         index = this->items[index]->functions.find(name);
      }
      return result;
   }

   bool
   ClassTable::has_method(t::Class* cls, t::Function* func)
   {
      bool result = false;
      long index = this->find(cls);
      if (index != -1)
      {
         index = this->items[index]->functions.find(func);
      }
      return result;
   }

   #ifdef _DEBUG_
   void
   ClassTable::list(bool show_functions=false)
   {
      DEBUG("ClassTable[@%lu] : Listing classes (%lu)\n", (ULong)this, this->count());
      for (ULong i = 0 ; i < this->count() ; ++i)
      {
         DEBUG("#%lu : ", i);
         DEBUG_APD("%s\n", ((Class*)this->items[i]->cls)->name.c_str());
         if (show_functions)
         {
            this->items[i]->functions.list();
         }
      }
   }
   #endif
}
