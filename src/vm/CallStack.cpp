#include "vm/CallStack.h"

namespace vm
{
   CallStack::CallStack()
   {
      this->frame_count = 0;
   }

   CallStack::~CallStack()
   {
      while (this->last_frame != NULL)
      {
         vm::Frame* pFrameToDelete = this->last_frame;
         this->last_frame = this->last_frame->parent_frame;
         delete pFrameToDelete;
      }
   }

   void
   CallStack::append(vm::Frame* pFrame)
   {
      ASSERT_NOT_NULL(pFrame);
      pFrame->parent_frame = this->last_frame;
      this->last_frame = pFrame;
      ++ this->frame_count;
   }

   void
   CallStack::pop()
   {
      if (this->frame_count > 0)
      {
         -- this->frame_count;
         vm::Frame* pTopFrame = this->last_frame->parent_frame;
         delete this->last_frame;
         this->last_frame = pTopFrame;
      }
   }

   void
   CallStack::print()
   {
      printf("StackTrace:\n");
      vm::Frame* pFrame = this->last_frame;
      u3 i = 0;
      while (pFrame != NULL)
      {
         printf(
               "#%" PRTF_u3 "\n%s [%s:%" PRTF_u3 "]",
               i,
               pFrame->block->get_name(),
               pFrame->block->get_file_name(),
               pFrame->block->get_line_number()
         );

         ++ i;
         pFrame = pFrame->parent_frame;
      }
   }
}
