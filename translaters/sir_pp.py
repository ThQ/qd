import sys

class CommandHandler:
   def __init__(self, preprocessor):
      self.output = ""
      self.pp = preprocessor

   def get_output(self):
      return self.output

   def initialize(self, at, args):
      return False

   def put_command(self, at, command, args):
      return -1

   def put_string(self, at, string):
      return ""


class AtHandler (CommandHandler):
   def initialize(self, at, args):
      return False


class DefineHandler (CommandHandler):
   def initialize(self, at, args):
      space_pos = args.find(" ")
      name = ""
      value = ""
      if space_pos != -1:
         name = args[0:space_pos].strip()
         value = args[space_pos + 1:].strip()
      else:
         name = args.strip()
         value = ""

      if name != "":
         self.pp.define_variable(at, name, value)
      else:
         self.pp.warn(at, "Define does not actually define anything.")

      return False


class UndefineHandler (CommandHandler):
   def initialize(self, at, args):
      space_pos = args.find(" ")
      name = ""
      value = ""
      if space_pos != -1:
         name = args[0:space_pos].strip()
         value = args[space_pos + 1:].strip()
      else:
         name = args.strip()
         value = ""

      if name != "":
         self.pp.undefine_variable(at, name)
      else:
         self.pp.warn(at, "Undefine must be passed a variable name.")

      return False

class IfDefHandler (CommandHandler):
   def __init__(self, pp):
      CommandHandler.__init__(self, pp)
      self.log = False
      self.variable_name = ""
      self.ifs = 0

   def initialize(self, at, args):
      self.variable_name = args
      if self.variable_name in self.pp.variables:
         self.log = True

      return True

   def put_command(self, at, command, args):
      result = -1
      if command == "else":
         if self.ifs == 0:
            self.log = not self.log
         result = 1
      elif command == "ifdef":
         if self.log:
            result = 0
         else:
            result = 1
            self.ifs += 1
      elif command == "endif":
         if self.log:
            result = -1
         else:
            result = 1
            self.ifs -= 1
      else:
         if self.log:
            result = 0
         else:
            result = 1
      ##print self, "put_command", command, "| result=", result, "| log=", self.log
      return result

   def put_string(self, at, string):
      if self.log:
         return string + "\n"
      else:
         return ""

class SirPreprocessor:
   def __init__(self):
      self.handler = None
      self.handlers = []
      self.variables = {}

   def define_variable(self, at, name, value):
      if not name in self.variables:
         self.variables[name] = value
      else:
         self.warn(at, "Redefining variable [" + name + "].")

   def get_handler(self, name):
      h = None
      if name == "define":
         h = DefineHandler(self)
      elif name == "ifdef":
         h = IfDefHandler(self)
      elif name == "undefine":
         h = UndefineHandler(self)
      elif name == "at":
         h = AtHandler(self)
      return h

   def preprocess(self, file_path):
      file = open(file_path, "r")
      if file != None:
         content = file.read()
         file.close()
         return self.preprocess_string(content)
      else:
         return ""

   def preprocess_string(self, content):
      output = ""
      lines = content.splitlines()
      lineno = 1
      for line in lines:
         line = line.strip()
         if line.startswith("@@"):
            line = "%% at " + line[2:]

         if line.startswith("%% "):
            space_pos = line.find(" ", 4)
            command = ""
            args = ""
            if space_pos != -1:
               command = line[3:space_pos]
               args = line[space_pos + 1:]
            else:
               command = line[3:]

            if self.handler != None:
               todo = self.handler.put_command(lineno, command, args)
               if todo == -1 :
                  if len(self.handlers) > 0:
                     self.handlers.pop()
                  if len(self.handlers) > 0:
                     self.handler = self.handlers[-1]
                  else:
                     self.handler = None
               elif todo == 0:
                  self.handler = self.get_handler(command)
                  if self.handler != None:
                     if self.handler.initialize(lineno, args):
                        self.handlers.append(self.handler)
                     else:
                        self.handler = None
                  else:
                     self.warn(lineno, "Unknown command [" + command + "].")
            else:
               self.handler = self.get_handler(command)
               if self.handler != None:
                  if self.handler.initialize(lineno, args):
                     self.handlers.append(self.handler)
                  else:
                     self.handler = None
               else:
                  self.warn(lineno, "Unknown command [" + command + "].")


         else:
            new_line = ""
            if self.handler != None:
               new_line += self.handler.put_string(lineno, line)
            else:
               new_line += line + "\n"
            output += self.replace_variables(new_line)

         lineno += 1

      return output

   def replace_variables(self, content):
      result = ""
      last_at = 0
      tag_start = "{{"
      tag_start_len = len(tag_start)
      tag_end = "}}"
      tag_end_len = len(tag_end)
      while True:
         var_start = content.find(tag_start, last_at)
         if var_start != -1:
            var_end = content.find(tag_end, var_start)
            if var_end != -1:
               result += content[last_at:var_start]
               var_name = content[var_start + tag_start_len:var_end].strip()
               if var_name in self.variables:
                  result += self.variables[var_name]
               else:
                  print self.variables
                  self.warn("?", "Unknown variable [" + var_name + "].")
         else:
            break;
         last_at = var_end + tag_end_len
      result += content[last_at:]
      return result

   def undefine_variable(self, at, name):
      if name in self.variables:
         self.variables.pop(name)

   def warn(self, lineno, msg):
      sys.stderr.write("[SirPP] Warning @" + str(lineno) + ": " + msg + "\n")

if __name__ == "__main__":
   if len(sys.argv) >= 2:
      pp = SirPreprocessor()
      sir = pp.preprocess(sys.argv[1])
      print sir,
