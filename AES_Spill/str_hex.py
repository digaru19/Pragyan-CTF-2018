

import struct
import codecs

s = '%7$x'

s = '%12$s\n' # '%17$s\n'

print s
t = s[::-1]
print t

c = codecs.encode(s, 'hex')

print c
print "\n"

for i in range(len(c)/4+1):
    print c[4*i:4*(i+1)]

