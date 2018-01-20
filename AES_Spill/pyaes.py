from hashlib import md5
from base64 import b64decode
from base64 import b64encode
from Crypto import Random
from Crypto.Cipher import AES
import codecs


# Padding for the input string --not
# related to encryption itself.
BLOCK_SIZE = 16  # Bytes
# pad = lambda s: s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * \
#                 chr(BLOCK_SIZE - len(s) % BLOCK_SIZE).encode()

def pad(s):
    t = (BLOCK_SIZE - len(s) % BLOCK_SIZE)
    c = chr(t).encode()
    s = s + c * t
    return s


unpad = lambda s: s[:-ord(s[len(s) - 1:])]


key = b"dujf#*(@!>012345-/:['}2345fc*$01"
iv = b'0123456789012345'
cipher = AES.new(key, AES.MODE_CBC, iv)

msg = input('Message...: ')

msg = msg.encode()

msg = pad(msg)
print(msg)
print(codecs.encode(msg, 'hex'))

ct = cipher.encrypt(msg)

print("\n Ciphertext :- \n")
print(codecs.encode(ct, 'hex'))


dec = AES.new(key, AES.MODE_CBC, iv)
pt = dec.decrypt(ct)
pt = unpad(pt)

print("\n Plaintext :- \n")
print(codecs.encode(pt, 'hex'))
print(codecs.encode(pt.decode(), 'utf8').decode())

