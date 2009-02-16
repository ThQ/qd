import dirt
import getopt
import sys


args = getopt.getopt(sys.argv[1:], "")
options = args[0]
files = args[1]

if len(files) >= 2:
   translater = dirt.Translater()
   translater.initialize()
   translater.load_opcodes(files[0])
   content = translater.translate_file(files[1])
   if len(files) == 3:
      hfile = open(files[2], "w+")
      if hfile != None:
         hfile.truncate(0)
         hfile.seek(0)
         hfile.write( content)
         hfile.close()
   else:
      print content
