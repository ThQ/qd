#include "svm/FunctionTable.h"

namespace svm
{
   FunctionTable::FunctionTable()
   {
      this->functions = NULL;
      this->function_count = 0;
   }

   FunctionTable::~FunctionTable()
   {
      /*
      if (this->functions != NULL)
      {
         free(this->functions);
      }
      */
   }

   // TODO: Way too REALLOC intensive
   void
   FunctionTable::append(Function* func)
   {
      //INTERNAL("FunctionTable(@%lu)::append(Function*) @%lu\n", (ULong)this, this->function_count);
      SVM_ASSERT_NOT_NULL(func);

      FunctionTableEntry* entry = new FunctionTableEntry(func);
      SVM_ASSERT_FUNCTION(entry->function);
      ++ this->function_count;
      this->functions = (FunctionTableEntry**)REALLOC(this->functions, sizeof(FunctionTableEntry*) * this->function_count);
      ASSERT_REALLOC(this->functions);
      ASSERT_NOT_NULL(this->functions);

      this->functions[this->function_count - 1] = entry;
      //INTERNAL("/ FunctionTable(@%lu)::append(Function*)\n", (ULong)this);
   }

   void
   FunctionTable::append(FunctionTableEntry* entry)
   {
      ++ this->function_count;
      /*
      #ifdef _SHOW_INTERNAL_
      INTERNAL("FunctionTable[@%d]::append(FunctionTableEntry[", this)
      String::print_unicode_string(entry.function->name);
      printf("]) : @%d\n", this->function_count - 1);
      #endif
      */
      this->functions = (FunctionTableEntry**)REALLOC(this->functions, sizeof(FunctionTableEntry*) * this->function_count);
      ASSERT_REALLOC(this->functions);
      ASSERT_NOT_NULL(this->functions);
      this->functions[this->function_count - 1] = entry;
      //DEBUG("FunctionTable[@%d]::append(FunctionTableEntry) : DONE\n", this);
   }

   #ifdef _DEBUG_
   void
   FunctionTable::assert_validity()
   {
      for (ULong i = 0 ; i < this->function_count ; ++ i)
      {
         SVM_ASSERT_NOT_NULL(this->functions[i]->function);
         this->functions[i]->function->assert_validity();
      }
   }
   #endif

   ULong
   FunctionTable::count()
   {
      return (this->function_count);
   }

   long
   FunctionTable::find(std::string name)
   {
      //DEBUG("FunctionTable::find(UnicodeString) : %d methods\n", this->function_count);
      long result = -1;
      for (ULong i = 0 ; i < this->function_count ; ++i)
      {
         //DEBUG("Is <%s> ?= <%s> ?\n", this->functions[i]->signature.c_str(), name.c_str());
         if (this->functions[i]->signature.compare(name) == 0)
         {
            result = i;
            break;
         }
      }
      return result;
   }

   long
   FunctionTable::find(Function* func)
   {
      long result = -1;
      for (ULong i = 0 ; i < this->function_count ; ++i)
      {
         if (this->functions[i]->function == func)
         {
            result = i;
            break;
         }
      }

      return result;
   }

   Function*
   FunctionTable::get(std::string name)
   {
      long index = this->find((std::string)name);
      Function* result = NULL;
      if (index != -1)
      {
         result = this->functions[index]->function;
      }
      #ifdef _SHOW_WARNING_
      else
      {
         WARNING("<method:%s> not found.\n", name.c_str());
      }
      #endif
      return result;
   }

   bool
   FunctionTable::has(std::string name)
   {
      return (this->find((std::string)name) != -1);
   }

   bool
   FunctionTable::has(Function* func)
   {
      return (this->find(func) != -1);
   }

   #ifdef _DEBUG_
   void
   FunctionTable::list()
   {
      DEBUG("Listing functions (%lu) in FunctionTable @%lu :\n", this->function_count, (ULong)this);
      for (ULong i = 0 ; i < this->function_count ; ++i)
      {
         svm::Function* func = (svm::Function*)this->functions[i]->function;
         DEBUG(
            "#%lu : [name=\"%s\", references=%d, pointer=%lu, parameters=",
            i,
            this->functions[i]->signature.c_str(),
            this->functions[i]->function->references,
            (ULong)func
         );

         for (ULong j = 0 ; j < this->functions[i]->function->arguments_count ; ++j)
         {
            if (j != 0)
            {
               printf(", ");
            }
            printf("%s", ((svm::Class*)func->arguments[j]->cls)->name.c_str());
         }
         printf("].\n");
      }
   }
   #endif
}
