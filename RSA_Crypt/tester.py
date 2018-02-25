
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
p_str = '''
    00:ee:e0:12:a5:34:9c:f5:b6:cb:80:9e:fe:36:2e:
    55:d5:d4:e0:f2:21:c2:95:4d:fa:83:36:03:93:58:
    63:22:a9:89:c2:af:6e:02:84:f0:49:5f:db:70:25:
    1f:13:e2:58:c7:a9:63:b1:1f:f5:dc:e3:dd:a7:1c:
    69:fa:7f:78:23
    '''
q_str = '''
    00:c6:ac:00:5b:88:98:6a:bc:c2:fd:b6:50:76:4f:
    f6:b3:f9:f1:d8:f3:db:36:85:3d:dc:41:a5:ad:5b:
    88:91:26:50:2a:23:a2:19:88:ef:f2:6b:fd:4e:02:
    49:f7:07:f0:87:f3:c4:5a:d2:ec:a6:05:12:16:36:
    61:0e:34:03:b5
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
    e = 65537
    n = get_number(n_str)
    p = get_number(p_str)
    q = get_number(q_str)
    phi = (p-1) * (q-1)
    d = modinv(e, phi)

    msg_text = input("Enter encrypted message :- ")

    if(len(msg_text)) > KEY_LENGTH / 4:
        print("Message too big")
        exit()

    try:
        t = codecs.decode(msg_text.encode(), 'hex')
    except:
        print("Given encrypted text is not a valid hex input")
        exit()

    msg = int.from_bytes(t, byteorder='little')

    c2 = pow(2, e, n)
    c3 = (c2 * msg) % n

    d_enc = c3.to_bytes(KEY_LENGTH // 8, byteorder='little')
    print(codecs.encode(d_enc, 'hex').decode())

    print("\nEnter decrypted message (2t) :- ")
    msg_text = input()

    if(len(msg_text)) > KEY_LENGTH / 4:
        print("Message too big")
        exit()

    try:
        t = codecs.decode(msg_text.encode(), 'hex')
    except:
        print("Given encrypted text is not a valid hex input")
        exit()

    msg = int.from_bytes(t, byteorder='little')
    dec = msg // 2

    dec_msg = dec.to_bytes(KEY_LENGTH // 8, byteorder='little').decode()

    print("\n\nDecrypted message :- ")
    print(dec_msg)

if __name__ == '__main__':
    execute()
