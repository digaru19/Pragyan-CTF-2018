#!/usr/bin/python3

import sys
import codecs
import random
import time
from string import ascii_letters

KEY_LENGTH = 1024

n_str = '''
    00:b9:61:cd:4d:b6:cc:a2:c5:ec:44:d1:e6:69:e5:
    2b:85:05:74:a5:57:5c:09:3a:a7:40:d2:23:a7:b4:
    2a:48:ed:3d:47:8a:c3:e9:10:c7:93:d2:9f:da:13:
    f2:3c:ec:d0:0b:d0:ac:bd:cd:b7:0a:b1:f6:d5:e9:
    82:1b:85:15:3f:39:81:f2:07:cf:5f:a2:0f:cd:f5:
    e4:e4:32:b1:d3:fb:b3:b0:12:d7:d2:70:40:0d:5c:
    67:c9:9a:ba:eb:2f:f3:c0:8e:5b:29:c8:07:b1:24:
    3a:29:73:87:ff:06:44:3c:09:77:db:f2:f2:84:a9:
    48:d4:5c:16:96:eb:a4:59:bf
    '''

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    else:
        return x % m

def get_number(s):
    s = s.replace('\n','').replace(':','').replace(' ','')
    s = s.encode()
    s = codecs.decode(s, 'hex')
    num = int.from_bytes(s, 'big')
    return num

def execute():
    n = get_number(n_str)
    e = 65537
    # print("N is :- " + str(n))
    
    msg_text = input("Enter message :- ")

    if(len(msg_text) > KEY_LENGTH // 8):
        print("Message too big")
        print("Message length should be smaller than {} characters\n".format(KEY_LENGTH // 8))
        exit()

    msg = int.from_bytes(msg_text.encode(), byteorder='little')

    c1 = pow(msg,e,n)
    ciphertext = codecs.encode(c1.to_bytes(KEY_LENGTH // 8, byteorder='little'), 'hex')
        
    print("\nEncrypted message :- ")
    print(ciphertext.decode())
    print()

if __name__ == '__main__':
    execute()
