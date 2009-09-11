import dis

def loop_func(fucker):
   for i in range(0, 10000):
      print i

def if_func():
   if True:
      print "True","yes"
   else:
      print "False","yes"

dis.dis(loop_func)
print "----NEXT------"
dis.dis(if_func)



