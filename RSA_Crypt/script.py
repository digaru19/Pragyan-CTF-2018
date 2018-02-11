from rsa import *

pub_key_file = open('public.pem', 'rb').read()
pri_key_file = open('private.pem', 'rb').read()

pub_key = PublicKey.load_pkcs1_openssl_pem(pub_key_file)
pri_key = PrivateKey.load_pkcs1(pri_key_file)



