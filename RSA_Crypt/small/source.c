#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
 
// int padding = RSA_PKCS1_PADDING;
int padding = RSA_NO_PADDING;

RSA * createRSA(unsigned char * key,int public)
{
    RSA *rsa= NULL;
    BIO *keybio ;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL)
    {
        printf( "Failed to create key BIO");
        return 0;
    }
    if(public)
    {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
    }
    else
    {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
    }
    if(rsa == NULL)
    {
        printf( "Failed to create RSA");
    }
 
    return rsa;
}
 
int public_encrypt(unsigned char * data,unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA(key,1);
    int data_len = RSA_size(rsa);
    printf("\nData size :- %d\n", data_len);
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}
int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA(key,0);
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
  
void printLastError(char *msg)
{
    char * err = malloc(130);;
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    printf("%s ERROR: %s\n",msg, err);
    free(err);
}
 
int main(){

    int maxLen = 4;
  
  char plainText[32/8]; //key length : 2048
  
  char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
    "MCAwDQYJKoZIhvcNAQEBBQADDwAwDAIFAMSEaukCAwEAAQ==\n"\
    "-----END PUBLIC KEY-----\n";

    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
    "MC4CAQACBQDEhGrpAgMBAAECBCh2FrkCAwDzXwIDAM63AgMAuTcCAwC9hwIDAMVJ\n"\
    "-----END RSA PRIVATE KEY-----\n";

memset(plainText, 0, maxLen);

printf("Enter plaintext :- ");
gets(plainText);
printf("Plaintext :- \n");
BIO_dump_fp (stdout, (const char *)plainText, maxLen);

unsigned char  encrypted[4098]={};
unsigned char decrypted[4098]={};

int encrypted_length= public_encrypt(plainText,publicKey,encrypted);
if(encrypted_length == -1)
{
    printLastError("Public Encrypt failed ");
    exit(0);
}
else
    printf("Encrypted length :- %d\n\n", encrypted_length);

BIO_dump_fp (stdout, (const char *)encrypted, encrypted_length);

int decrypted_length = private_decrypt(encrypted, encrypted_length,privateKey, decrypted);
if(decrypted_length == -1)
{
    printLastError("Private Decrypt failed ");
    exit(0);
}
printf("\n\n Decrypted :- \n");
BIO_dump_fp (stdout, (const char *)decrypted, decrypted_length);
printf("\n\n Decrypted Text = %s\n",decrypted);
 
}

