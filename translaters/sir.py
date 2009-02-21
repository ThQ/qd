import ConfigParser
import getopt
import re
import sys


def initialize(opcodes_ini_file):
      res_string = '"[^"]*?"'
      res_positive_int = "\d+"
      res_int = "-?" + res_positive_int
      res_positive_float = res_positive_int + "\.(?:" + res_positive_int + ")?"
      res_float = "-?" + res_positive_float
      res_heap_object = "\$" + res_positive_int
      res_namespace = "[a-zA-Z]+"
      res_method = "[a-zA-Z0-9_]+"
      res_indent = "(?: |\t)+"
      res_whitespace = " "
      res_whitespaces = "(?:" + res_whitespace + ")+"
      res_content = res_string
      res_parameter = res_whitespaces + "(?:"
      res_parameter += "(?:" + res_string + ")"
      res_parameter += "|(?:" + res_int + ")"
      res_parameter += "|(?:" + res_float + ")"
      res_parameter += "|(?:" + res_heap_object + ")"
      res_parameter += ")"
      res_parameters = "(?:" + res_parameter + ")+"
      res_comment = res_whitespaces + "#[^\n\r]*"
      res_opcode = "^(?:" + res_indent + ")?"
      res_opcode += "(" + res_namespace + ")"
      res_opcode += "\s*:\s*"
      res_opcode += "(" + res_method + ")"
      res_opcode += "(?:,(" + res_content + "))?"
      res_opcode += "(" + res_parameters + ")?"
      res_opcode += "(" + res_comment + ")?"
      res_opcode += "$"
      Translater.re_empty_line = re.compile("(?:" + res_comment + ")?")
      Translater.re_opcode = re.compile(res_opcode)

      Translater.opcodes_ini = ConfigParser.ConfigParser()
      Translater.opcodes_ini.read(opcodes_ini_file)

class Translater:
   re_opcode = None
   re_empty_line = None
   opcodes_ini = None

   def __init__(self):
      self.has_error = False

   def log_error(self, lineno, message):
      print "Line", str(lineno), "| Error:", message
      self.has_error = True

   def translate(self, source_path):
      s = ""
      hfile = open(source_path, "r")
      content = hfile.read()
      lines = content.splitlines()
      hfile.close()

      i_line = 0
      for line in lines:
         i_line += 1
         line = line.strip()
         if line != "":
            matches = self.re_opcode.match(line)
            if matches != None:
               s += self.translate_line(i_line, line, matches.groups())
            elif self.re_empty_line.match(line) != None:
               pass
            else:
               self.log_error(i_line, "Invalid line <" + line + ">")
      return s

   def translate_line(self, lineno, line, groups):
      s = ""
      ns = "NS_" + groups[0].upper()
      opc = groups[0].upper() + "_" + groups[1].upper()

      if not Translater.opcodes_ini.has_option("opcodes", ns):
         self.log_error(lineno, "Opcode namespace <" + ns + "> not found.")
      else:
         if not Translater.opcodes_ini.has_option("opcodes", opc):
            self.log_error(lineno, "Opcode <" + opc + "> not found.")
         else:
            s = Translater.opcodes_ini.get("opcodes", ns)
            s += Translater.opcodes_ini.get("opcodes", opc)
            if groups[2] != None:
               s += ":" + groups[2]
            if groups[3] != None:
               s += groups[3]
            s += "\n"


      return s


if __name__ == "__main__":
   args = getopt.getopt(sys.argv[1:], "")
   options = args[0]
   files = args[1]

   if len(files) >= 2:
      initialize(files[0])
      translater = Translater()
      sop = translater.translate(files[1])
      if len(files) == 3:
         hfile = open(files[2], "w+")
         if hfile != None:
            hfile.truncate(0)
            hfile.seek(0)
            hfile.write(sop)
            hfile.close()

      if translater.has_error:
         sys.exit(1)
      else:
         print sop
