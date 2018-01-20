

import struct
import codecs

s = '%$7x'

t = s[::-1]

print t

c = codecs.encode(t, 'hex')

print c

