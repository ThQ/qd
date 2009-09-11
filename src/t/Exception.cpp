#include "t/Exception.h"

namespace t
{
   VM_CLASS__NEW(cEXCEPTION, t::Object, t::EXCEPTION_TYPE, &cOBJECT);

   Exception::Exception ()
   {
      #ifdef QD__T__EXCEPTION__HAVE_MESSAGE
      this->message = NULL;
      #endif
      this->stack_trace = NULL;
      this->type = EXCEPTION_TYPE;
      this->klass = &cEXCEPTION;
   }

   #ifdef QD__T__EXCEPTION__HAVE_MESSAGE
   Exception::Exception (String* message)
   {
      ASSERT_NOT_NULL(message);

      this->message = message;
      this->stack_trace = NULL;
      this->type = EXCEPTION_TYPE;
   }
   #endif

   #ifdef QD__T__EXCEPTION__HAVE_MESSAGE
   Exception::Exception (String* message, List* stack_trace)
   {
      ASSERT_NOT_NULL(message);
      ASSERT_NOT_NULL(stack_trace);

      this->message = message;
      this->stack_trace = stack_trace;
      this->type = EXCEPTION_TYPE;
   }
   #endif

   String*
   Exception::cast_to_string (Exception* pException)
   {
      ASSERT_NOT_NULL(pException);

      String* pResult = new String();
      #ifdef QD__T__EXCEPTION__HAVE_MESSAGE
      ASSERT_NOT_NULL(pException->message);
      pResult->value.assign(pException->message->value);
      pResult->value.append("\n");
      #endif

      return pResult;
   }

   void
   Exception::print (Exception* pException)
   {
      ASSERT_NOT_NULL(pException);

      String* pMessage = Exception::cast_to_string(pException);
      String::print(pMessage);
   }

   void
   Exception::print_line (Exception* pException)
   {
      ASSERT_NOT_NULL(pException);

      String* pMessage = Exception::cast_to_string(pException);
      String::print_line(pMessage);
   }

   #ifdef QD__T__EXCEPTION__HAVE_MESSAGE
   void
   Exception::set_message (String* pMessage)
   {
      ASSERT_NOT_NULL(pMessage);

      if (this->message != NULL)
      {
         this->message->drop();
      }
      this->message = pMessage;
      pMessage->pick();
   }
   #endif

   void
   Exception::set_stack_trace (List* pStackTrace)
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
