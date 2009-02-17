#!/usr/bin/python

import sys

output = ""
# Reading <STDIN>
stdin = ""
for line in sys.stdin:
    stdin += line

# Reading base file
h = open(sys.argv[2], "rb")
if h:
    content = h.read()
    h.close()
    last_at = 0
    output = ""
    str_rpl = sys.argv[1]
    str_rpl_len = len(sys.argv[1])

    while True:
        str_at = content.find(str_rpl, last_at)
        if str_at != -1:
            output += content[last_at:str_at] + stdin
            last_at = str_at + str_rpl_len

        else:
            break
    output += content[last_at:]

print output
