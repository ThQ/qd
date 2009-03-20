#include "svm/Exception.h"

namespace svm
{
   Object* exception_type = NULL;
   Object* runtime_exception_type = NULL;
   Object* index_out_of_range_exception_type = NULL;

   Exception::Exception()
   {
      this->message = String::build("");
      this->set_class(exception_type);
      this->references = 0;
   }

   Object*
   Exception::build()
   {
      return (Object*) new Exception();
   }

   Object*
   Exception::build(Object* message)
   {
      SVM_ASSERT_STRING(message);

      Exception* result = new Exception();
      Exception::set_message(result, message);

      return (Object*)result;
   }

   Object*
   Exception::cast_to_string(Object* error)
   {
      SVM_ASSERT_STRING(error);

      String* result = new String();
      result->value.append(((String*)((Exception*)error)->message)->value);
      result->value.append("\n");

      return (Object*)result;
   }

   bool
   Exception::check(Object* error)
   {
      SVM_ASSERT_EXCEPTION(error);
      return error->cls == exception_type;
   }

   void
   Exception::print(Object* error)
   {
      SVM_ASSERT_EXCEPTION(error);
      Object* msg = Exception::cast_to_string(error);
      String::print(msg);
   }

   Object*
   Exception::set_message(Object* error, Object* message)
   {
      SVM_ASSERT_NOT_NULL(error);
      SVM_ASSERT_NOT_NULL(message);

      if (((Exception*)error)->message != NULL)
      {
         SVM_DROP(((Exception*)error)->message);
      }
      SVM_PICK(message);
      ((Exception*)error)->message = message;

      return message;
   }

   Object*
   Exception::set_stack_trace(Object* exception, Object* stack_trace)
   {
      SVM_ASSERT_EXCEPTION(exception);
      SVM_ASSERT_LIST(stack_trace);

      if (((Exception*)exception)->stack_trace != NULL)
      {
         SVM_DROP(((Exception*)exception)->stack_trace);
      }
      SVM_PICK(stack_trace);
      ((Exception*)exception)->stack_trace = stack_trace;

      return stack_trace;
   }
}
