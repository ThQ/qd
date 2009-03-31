#include "t/Exception.h"

namespace NS_TYPE
{
   T_OBJECT* tEXCEPTION = NULL;
   T_OBJECT* tRUNTIME_EXCEPTION = NULL;
   T_OBJECT* tINDEX_OUT_OF_RANGE_EXCEPTION = NULL;

   Exception::Exception()
   {
      this->message = String::build("");
      this->set_class(NS_TYPE::tEXCEPTION);
      this->references = 0;
   }

   T_OBJECT*
   Exception::build()
   {
      return (T_OBJECT*) new Exception();
   }

   T_OBJECT*
   Exception::build(T_OBJECT* message)
   {
      T_STRING::assert(message);

      Exception* result = new Exception();
      Exception::set_message(result, message);

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Exception::cast_to_string(T_OBJECT* error)
   {
      T_STRING::assert(error);

      T_STRING* message = (T_STRING*)((Exception*)error)->message;

      T_STRING* result = new T_STRING();
      result->value.append(message->value);
      result->value.append("\n");

      return (T_OBJECT*)result;
   }

   void
   Exception::print(T_OBJECT* error)
   {
      Exception::assert(error);
      T_OBJECT* msg = Exception::cast_to_string(error);
      String::print(msg);
   }

   T_OBJECT*
   Exception::set_message(T_OBJECT* error, T_OBJECT* message)
   {
      T_OBJECT::assert_not_null(error);
      T_OBJECT::assert_not_null(message);

      T_OBJECT::drop_safe(((Exception*)error)->message);
      T_OBJECT::pick(message);
      ((Exception*)error)->message = message;

      return message;
   }

   T_OBJECT*
   Exception::set_stack_trace(T_OBJECT* obj, T_OBJECT* stack_trace)
   {
      Exception::assert(obj);
      T_LIST::assert(stack_trace);

      Exception* exception = (Exception*)obj;
      T_OBJECT::drop_safe(exception->stack_trace);
      T_OBJECT::pick(stack_trace);
      exception->stack_trace = stack_trace;

      return stack_trace;
   }
}
