
set -e 

openssl genrsa -out private.pem $1

openssl rsa -in private.pem -pubout -out public.pem

openssl rsa -in private.pem -text -noout > key.info

