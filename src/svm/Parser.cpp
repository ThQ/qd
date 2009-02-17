#include "svm/Parser.h"

namespace svm
{
   // TODO: Stop intensive REALLOC'ing
   UInt
   Parser::parse_arguments(std::string content, ULong start, ULong end, svm::Object**& argv)
   {
      INTERNAL("Parser::parse_arguments\n");
      UShort step = 0;
      std::string buff = "";
      UInt argc = 0;

      for (UInt i = start ; i < end ; ++ i)
      {
         char c = content[i];
         switch (step)
         {
            case 0:
               if (c == '"')
               {
                  step = 1;
               }
               else if (c == '@')
               {
                  step = 2;
               }
               else if (c == '$')
               {
                  step = 3;
               }
               else if (c == '-' || (c >= '0' && c <= '9'))
               {
                  step = 4;
                  --i;
               }
               else if (c == 'F'  || c== 'T')
               {
                  ++ argc;
                  argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
                  if (c == 'F') argv[argc - 1] = svm::False;
                  else argv[argc - 1] = svm::True;
                  SVM_PICK(argv[argc - 1]);
                  INTERNAL("<Bool> argument found: %d.\n", c == 'T');
               }
               else if (c == 'N')
               {
                  ++argc;
                  argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
                  ASSERT_REALLOC(argv);
                  SVM_PICK(svm::Null);
                  argv[argc - 1] = svm::Null;
                  INTERNAL("<Null> argument found.\n");
               }
               break;

            case 1:
               if (c == '"')
               {
                  ++ argc;
                  argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
                  svm::Object* obj = svm::String::build(buff);
                  SVM_PICK(obj);
                  argv[argc - 1 ] = obj;
                  buff = "";
                  step = 0;
                  INTERNAL("<String> argument found: \"%s\".\n", buff.c_str());
               }
               else
               {
                  buff.append(&c, 1);
               }
               break;

            case 2:
               ++ argc;
               argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
               argv [ argc - 1 ] = svm::HeapObject::build(FALSE, c - 48);
               SVM_PICK(argv[argc - 1]);
               step = 0;
               break;

            case 3:
               ++ argc;
               argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
               argv [ argc - 1 ] = svm::HeapObject::build(TRUE, c - 48);
               step = 0;
               break;


            case 4:
               if (c == ' ' || c == '\n')
               {
                  long len = buff.length();
                  long num = 0;
                  bool negative;
                  if ((negative = buff.find("-") != std::string::npos))
                  {
                     --len;
                  }

                  for (int i = 0 ; i < len ; ++ i)
                  {
                     num += (buff[buff.length() - 1 - i] - 48) * pow(10, i);
                  }
                  if (negative)
                  {
                     num = num * -1;
                  }
                  ++argc;
                  argv = (svm::Object**)REALLOC(argv, sizeof(svm::Object*) * argc);
                  argv [ argc - 1 ] = svm::Int::build(num);
                  SVM_PICK(argv[argc - 1]);
                  step = 0;
                  buff = "";
               }
               else
               {
                  buff += c;
               }
               break;
         }
      }

      INTERNAL("Parser::parse_arguments\n");

      return argc;
   }

   ULong
   Parser::parse_line(svm::OpCode* opc, std::string content, ULong start, ULong end)
   {
      INTERNAL("Parser::parse_line from %lu to %lu.\n", start, end);
      ULong result = start;
      if (end > start + 1)
      {
         opc->type = content[start];
         opc->method = content[start + 1];
         result += 2;
      }
      else
      {
         opc->type = OPC_NS_NIL;
      }

      INTERNAL("/ Parser::parse_line.\n");
      return result;
   }

   ULong
   Parser::parse_lines(std::string content, svm::Block**& blocks)
   {
      INTERNAL("Parser::parse_lines : %s.\n", content.c_str());

      blocks = NULL;
      ULong block_count = 0;
      ULong block_rooms = 0;
      UInt block_step = 10;
      UInt at = 0;
      UInt last_at = 0;
      svm::Block* block = NULL;

      //svm::OpCode* previous_opcode = NULL;
      while ((at = content.find('\n', (size_t)last_at)) != std::string::npos)
      {
         svm::OpCode* opc = new svm::OpCode();
         last_at = Parser::parse_line(opc, content, last_at, at);
         opc->content.clear();

         if (last_at + 3 <= at && content[last_at] == ':' && content[last_at+1]=='"')
         {
            last_at += 2;
            for(; last_at < at ; ++ last_at)
            {
               if (content[last_at] != '"')
               {
                  opc->content.append(&(content[last_at]), 1);
               }
               else
               {
                  ++last_at;
                  break;
               }
            }
         }
         opc->argc = Parser::parse_arguments(content, last_at, at + 1, opc->argv);

         INTERNAL(
            "<opcode:%c%c> [%d arguments] found in content[%d:%d].\n",
            opc->type,
            opc->method,
            opc->argc,
            last_at,
            at
         );

         ASSERT_NOT_NULL(opc);
         if (opc->type == OPC_NS_BLOCK && opc->method == OPC_BLOCK_NEW)
         {
            INTERNAL("<block:%s> found.\n", opc->content.c_str())

            //previous_opcode = NULL;

            block = new svm::Block();
            SVM_PICK(block);
            block->name = opc->content;
            block->argc = opc->argc;
            block->argv = opc->argv;

            block_count ++;

            if (block_rooms < block_count)
            {
               block_rooms += block_step;
               blocks = (svm::Block**)REALLOC(blocks, sizeof(svm::Block*) * block_rooms);
            }

            blocks[block_count - 1] = block;

            delete opc;
         }
         else
         {
            SVM_ASSERT_NOT_NULL(block);
            block->append(opc);
         }

         last_at = at + 1;
      }
      /*if (block->first_opcode != NULL)
      {
         block->last_opcode = previous_opcode;
      }*/

      INTERNAL("/ Parser::parse_lines\n");
      return block_count;
   }
}

