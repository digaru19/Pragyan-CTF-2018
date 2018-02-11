from hashlib import md5
from base64 import b64decode
from base64 import b64encode
from Crypto import Random
from Crypto.Cipher import AES
import codecs

BLOCK_SIZE = 16  # Bytes

def pad(s):
    t = (BLOCK_SIZE - len(s) % BLOCK_SIZE)
    c = chr(t).encode()
    s = s + c * t
    return s


unpad = lambda s: s[:-ord(s[len(s) - 1:])]

dump = ['33414141', '785e2866', '29234141', '51634c3d', \
         '402f4142', '2f2b2d74', '607e3a3c', '41416d76']

def get_BE_from_LE(s):
    print("Converting " + s)
    l = []
    for i in range(4):
        l.append(s[2*i] + s[2*i+1])
    l = l[::-1]
    return ''.join(l)

def get_key_from_dump():
    key = b''
    for i in dump:
        t = get_BE_from_LE(i).encode()
        h = codecs.decode(t, 'hex')
        key = key + h
    print("Key is :- " + key.decode())
    print("Key length :- " + str(len(key)))
    return key

# key = b"dujf#*(@!>012345-/:['}2345fc*$01"
key = get_key_from_dump()
iv = b'5689784512657848'
cipher = AES.new(key, AES.MODE_CBC, iv)

# msg = input('Message...: ')
# msg = msg.encode()

# msg = pad(msg)
# print(msg)
# print(codecs.encode(msg, 'hex'))

# ct = cipher.encrypt(msg)

# print("\n Ciphertext :- \n")
# print(codecs.encode(ct, 'hex'))

f = open('encrypted', 'r')

ct = f.read()
print(ct)
ct = codecs.decode(ct.encode(), 'hex')
print(ct)

dec = AES.new(key, AES.MODE_CBC, iv)
pt = dec.decrypt(ct)
pt = unpad(pt)

print("\n Plaintext :- \n")
print(codecs.encode(pt, 'hex'))
print(codecs.encode(pt.decode(), 'utf8').decode())

