import re
import sop

class Translater (sop.Translater):
   re_line = None
   re_int = None
   re_float = None
   re_string = None
   re_argument = None
   re_bool = None

   def initialize(self):
      res_positive_int = "\d+"
      res_int = "-?" + res_positive_int
      res_positive_float = res_positive_int + "\.(?:" + res_positive_int + ")?"
      res_float = "-?" + res_positive_float
      res_string = '"[^"\\r\\n]*?"'
      res_bool = 'T|F'
      res_null = 'N'
      res_argument = "(?:"
      res_argument += "(?:" + res_int + ")"
      res_argument += "|(?:" + res_float + ")"
      res_argument += "|(?:" + res_string + ")"
      res_argument += "|(?:" + res_bool + ")"
      res_argument += "|(?:" + res_null + ")"
      res_argument += ")"
      res_arguments = "(?:" + res_argument + "(?:\s*,\s+" + res_argument + ")*)?"
      res_method = "[a-zA-Z][a-zA-Z0-9_]*"
      res_line = "^\s*(" + res_argument + ")\.(" + res_method + ")\((" + res_arguments + ")\)\s+->\s+(" + res_argument + ")\s*$"

      self.re_int = re.compile(res_int)
      self.re_float = re.compile(res_float)
      self.re_string = re.compile(res_string)
      self.re_bool = re.compile(res_bool)
      self.re_argument = re.compile("(" + res_argument + ")")
      self.re_line = re.compile(res_line)

   def get_argument_type(self, arg):
      tp = ""
      if self.re_int.match(arg) != None:
         tp = "system.Int"
      elif self.re_float.match(arg) != None:
         tp = "system.Float"
      elif self.re_string.match(arg) != None:
         tp = "system.String"
      elif self.re_bool.match(arg) != None:
         tp = "system.Bool"
      return tp

   def get_comparison_method(self, tp):
      s = ""
      if tp == "system.Int":
         s = self.get_method("i", "equals")
      elif tp == "system.String":
         s = self.get_method("s", "equals")
      elif tp == "system.Float":
         s = self.get_method("f", "equals")
      elif tp == "system.Bool":
         s = self.get_method("b", "equals")
      return s

   def get_method(self, namespace, met):
      result = ""
      ns = "NS_" + namespace.upper()
      method = namespace.upper() + "_" + met.upper()
      if self.opcodes.has_option("opcodes", ns) and self.opcodes.has_option("opcodes", method):
         result = self.opcodes.get("opcodes", ns) + self.opcodes.get("opcodes", method)
      else:
         self.warning("?", "No method found for namespace <" + namespace + ">(" + ns + ") and method <" + met + ">(" + method + ").")
      return result

   def split_arguments(self, arguments):
      args = []

      base = arguments
      while True:
         match = self.re_argument.search(base)
         if match != None:
            base = base[match.lastindex + 1:]
            arg = (match.groups()[0], self.get_argument_type(match.groups()[0]))
            args.append(arg)
         else:
            break
      return args

   def translate(self, content):
      s = ""
      lines = content.splitlines()
      s = self.get_method("block", "new") + ':"MAIN"\n'
      for line in lines:
         line = line.strip()
         if line != "":
            s += self.translate_line(line)
      s += self.get_method("block", "new") + ':"on_failure"\n'
      s += self.get_method("s", "print") + ' "F"\n'
      s += self.get_method("block", "new") + ':"on_success"\n'
      s += self.get_method("s", "print") + ' "."\n'

      return s

   def translate_line(self, line):
      result = ""
      match = self.re_line.match(line)
      if match != None:
         groups = match.groups()
         args = self.split_arguments(groups[2])
         opc_method = groups[1]
         opc_args = ""
         obj_type = self.get_argument_type(groups[0])
         result_type = self.get_argument_type(groups[3])

         opc_method += "," + obj_type
         opc_args += " " + groups[0]
         for arg in args:
            opc_method += "," + arg[1]
            opc_args += " " + arg[0]

         result += self.get_method("o", "call") + ':"' + opc_method + '"' + opc_args + "\n"
         result += self.get_comparison_method(result_type) + " $0 " + groups[3] + "\n"
         result += self.get_method("jump", "if_else") + ' $0 "on_success" "on_failure"\n'

      else:
         self.warning("?", "Invalid line : " + line)
      return result
