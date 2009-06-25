#include "t/Exception.h"

namespace t
{
   ExceptionType* cEXCEPTION = NULL;
   //T_OBJECT* tEXCEPTION = NULL;
   //T_OBJECT* tRUNTIME_EXCEPTION = NULL;
   //T_OBJECT* tINDEX_OUT_OF_RANGE_EXCEPTION = NULL;

   Exception::Exception()
   {
      this->message = NULL;
      this->stack_trace = NULL;
      this->type = EXCEPTION_TYPE;
   }

   Exception::Exception(String* message)
   {
      ASSERT_NOT_NULL(message);

      this->message = message;
      this->stack_trace = NULL;
      this->type = EXCEPTION_TYPE;
   }

   Exception::Exception(String* message, List* stack_trace)
   {
      ASSERT_NOT_NULL(message);
      ASSERT_NOT_NULL(stack_trace);

      this->message = message;
      this->stack_trace = stack_trace;
      this->type = EXCEPTION_TYPE;
   }

   String*
   Exception::cast_to_string(Exception* pException)
   {
      ASSERT_NOT_NULL(pException);
      ASSERT_NOT_NULL(pException->message);

      String* pResult = new String();
      pResult->value.assign(pException->message->value);
      pResult->value.append("\n");

      return pResult;
   }

   void
   Exception::print(Exception* pException)
   {
      ASSERT_NOT_NULL(pException);

      String* pMessage = Exception::cast_to_string(pException);
      String::print(pMessage);
   }

   void
   Exception::print_line(Exception* pException)
   {
      ASSERT_NOT_NULL(pException);

      String* pMessage = Exception::cast_to_string(pException);
      String::print_line(pMessage);
   }

   void
   Exception::set_message(String* pMessage)
   {
      ASSERT_NOT_NULL(pMessage);

      if (this->message != NULL)
      {
         this->message->drop();
      }
      this->message = pMessage;
      pMessage->pick();
   }

   void
   Exception::set_stack_trace(List* pStackTrace)
   {
      ASSERT_NOT_NULL(pStackTrace);

      if (this->stack_trace != NULL)
      {
         this->stack_trace->drop();
      }
      this->stack_trace = pStackTrace;
      pStackTrace->pick();
   }
}
