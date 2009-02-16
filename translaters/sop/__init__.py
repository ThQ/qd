import ConfigParser

class Translater:
   opcodes = None

   def load_opcodes(self, file_path):
      self.opcodes = ConfigParser.ConfigParser()
      self.opcodes.read(file_path)

      
   def read_file(self, file_path):
      content = ""      
      hfile = open(file_path, "r")
      if hfile != None:
         content = hfile.read()
      else:
         content = None
      return content

   def translate(self, content):
      return content

   def translate_file(self, file_path):
      content = self.read_file(file_path)
      if content != None:
         return self.translate(content)

   def warning(self, lineno, message):
      print "#" + lineno, "|", message + "\n"
