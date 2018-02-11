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
  
  char plainText[2048/8]; //key length : 2048
  
  char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAyMxVJI8VCrbKP7+q/JuQ\n"\
    "DmWeHj0MproEJNkhATR3hdCK7+X2Gh7tMpURP5hj51yRre23TwMWlWKLJqh0qid5\n"\
    "LJYtLLkn53nk1etKdGkWbYVvGciHBZjbiXgXLzscl2nysNF6zjBfcF4Sma1IcsEP\n"\
    "EFbMDs9yfBZQZ0Of+8UVA6Qk76+FEGkhzlvrn5GzchIxAtLmmIJVrN/ryri5r6wk\n"\
    "wYlnJ06dJ4qTHIe2e4xfKdZRnn9UEXcb4eFDoSsCK4o+Drzw3ZOYEzqlYWKgYQAJ\n"\
    "zWjw4GSzXCTRpxFK1SHzpUTZpagQhE+mTJPji5wzCAMLDbdq9elvKveCKSVzlIcF\n"\
    "JQIDAQAB\n"\
    "-----END PUBLIC KEY-----\n";

    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
    "MIIEpAIBAAKCAQEAyMxVJI8VCrbKP7+q/JuQDmWeHj0MproEJNkhATR3hdCK7+X2\n"\
    "Gh7tMpURP5hj51yRre23TwMWlWKLJqh0qid5LJYtLLkn53nk1etKdGkWbYVvGciH\n"\
    "BZjbiXgXLzscl2nysNF6zjBfcF4Sma1IcsEPEFbMDs9yfBZQZ0Of+8UVA6Qk76+F\n"\
    "EGkhzlvrn5GzchIxAtLmmIJVrN/ryri5r6wkwYlnJ06dJ4qTHIe2e4xfKdZRnn9U\n"\
    "EXcb4eFDoSsCK4o+Drzw3ZOYEzqlYWKgYQAJzWjw4GSzXCTRpxFK1SHzpUTZpagQ\n"\
    "hE+mTJPji5wzCAMLDbdq9elvKveCKSVzlIcFJQIDAQABAoIBAQCSC+SFobgpQcga\n"\
    "09qWvsLpZcm6rqasAbIP5wlVagbhAkx7rmPwnbviRX/1JG7NkYu32KWyR0m+v5z8\n"\
    "MhwgwnMlFdmnpMg8WXEykl9mCiUw5ZNoSmzCimprMziRtsnV606EguhyXcac4R9g\n"\
    "PSPrqzW8qZTj1MitLkGuygXrxm3BZfEfi2MIyIVgduqQSoOP+3+LCTnfjSPJMW7M\n"\
    "bsDgEfDIfEnbvdyvND/3U39uDywhvYKvzNAQi8A0BFdu698iNUeSor0hiurc4XoL\n"\
    "/hITtps/seUdz/ZOCenAzVnR63ClDnpokAiaeOCvhy56haW+Og3oonMbVQUR+Jg4\n"\
    "WS9eq/FBAoGBAOrQpRnfYqM21RJSFwQ0MgSIiNXE1QlRWcj78+cjyLVG0fArvhlt\n"\
    "iM1DglC1vmJHG+cbG+N+8sK/oFHgCWBiolTt6DhUPNgJjff7Xup4WfArSulpBdo7\n"\
    "uHllEEZ2asW784sapWR/uaP09u/KrveeuEQiQMOqCHWduHG1FVdurlwxAoGBANrq\n"\
    "BlxeJWbB3e7OLf+nJPJcEfsrIFAkWcfBYeI9gXBmm9jrrgdvQ8bI1OWkurN1muTO\n"\
    "KRbHjBVLMjc824CjFt9OTrRQTYxTUHLUZUh6kGtUP5HMVpUJzRYaunBUArP0DYGG\n"\
    "nAteu/DXuVHQ1W2dw4zYB+AtcWdrAVgqzO5EhB81AoGAIokzbz26vTSoW/x05Cpl\n"\
    "HOOT9JTxnGA5q2TbN6i8sWTMJd3ZJNZGY6JFPWetq7i3suL61BfszpXul3wzBNkc\n"\
    "9Q7Us8w38rJdDhcLm8K9v6QubWwD71gPRtOFdEegZprBNDlkEAb1H9c8poIR/9t5\n"\
    "UJQVIHIWsm3THe47SFPAE1ECgYEAxwCm96C970OdNFFJj3WqKId58RGrNi9VTjmF\n"\
    "edzfpgYg9niIo0mKG1LF9lxhPHJUdFrVD1gnB9Rrubsg7zdSu3y8Hz5AwKecIkbi\n"\
    "K5j/YBIeF7PhoWpffRCfGy3Dp0LcZDqx78QWpUH1vWJSImugMJDR2AB3bsPfXP7L\n"\
    "fG3cjWECgYBzqK4Loy8MdcecOHRgO8YKrjUJaAfrE0ti0xszvlirruODaHwcE73L\n"\
    "uOXMtMqQNrcZfpaJyQ844FmcERp8jSqHGKvC7Zp992Z53CxpKusPRbemuCBnB2o6\n"\
    "kCJNiqNP7QCPFBLWPnc1TvNvJJEwLuz5dKWrb8LHJykoGHkyv4RDwg==\n"\
    "-----END RSA PRIVATE KEY-----\n";

memset(plainText, 0, 256);

// printf("Enter plaintext :- ");
// gets(plainText);
plainText[255] = 27;
printf("Plaintext :- \n");
BIO_dump_fp (stdout, (const char *)plainText, 256);

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

unsigned char  dummy[256]={0xb3, 0xc0, 0x0f, 0xd1, 0xef, 0xee, 0xe4, 0x4d, 0x53, 0xe9,
                            0xf6, 0x90, 0x4b, 0xcd, 0xf0, 0xbd, 0x3b, 0xf3, 0x15, 0x4e,
                            0x9e, 0x35, 0xc0, 0x63, 0x4d, 0xc2, 0x28, 0x8a, 0x48, 0x58,
                            0x75, 0x12, 0x0b, 0x99, 0xd2, 0xb7, 0xf4, 0x39, 0xa2, 0x54,
                            0x6f, 0xb6, 0x77, 0x32, 0x6a, 0xdf, 0x4a, 0xf1, 0x28, 0x1b,
                            0x54, 0xf9, 0x88, 0xe3, 0x63, 0x2c, 0x1a, 0xd6, 0xf2, 0x3f,
                            0xa3, 0x5c, 0xc6, 0x8e, 0x15, 0x5b, 0x83, 0x90, 0x59, 0x21,
                            0x2d, 0xa7, 0x33, 0x72, 0xd1, 0x8e, 0xf9, 0x4c, 0xd2, 0x27,
                            0x1e, 0xc3, 0x03, 0x0e, 0x51, 0x6f, 0x34, 0x2d, 0x07, 0xa5,
                            0xbc, 0x19, 0xba, 0xec, 0x58, 0x99, 0x5b, 0x5f, 0x89, 0x18,
                            0xf3, 0xbf, 0xcc, 0xc4, 0x53, 0x55, 0x4b, 0x8b, 0x9d, 0x14,
                            0xfd, 0x09, 0xde, 0xaf, 0x09, 0x1b, 0x24, 0xa9, 0x6a, 0x60,
                            0x99, 0x2e, 0xfe, 0x1d, 0x40, 0x94, 0xee, 0x89, 0x8c, 0xdc,
                            0x26, 0x1f, 0x7b, 0xc0, 0xb4, 0x04, 0x6c, 0xcf, 0x05, 0x54,
                            0x38, 0xe2, 0x80, 0x04, 0x5e, 0x8d, 0x68, 0x99, 0x00, 0x40,
                            0x6d, 0x82, 0x91, 0xe2, 0x92, 0x18, 0xe0, 0x3e, 0xf5, 0x0e,
                            0x8c, 0x7f, 0xa4, 0x23, 0xec, 0x53, 0x93, 0x45, 0x16, 0x28,
                            0xfd, 0xa1, 0xed, 0x4b, 0x66, 0xff, 0x72, 0x5f, 0xe6, 0x7e,
                            0x2d, 0xad, 0x11, 0x04, 0xfe, 0x45, 0x90, 0xac, 0xfc, 0x2b,
                            0xab, 0xfe, 0x23, 0xb8, 0xe0, 0x1a, 0x95, 0x2d, 0x34, 0xb7,
                            0x8f, 0x38, 0x07, 0xbe, 0xf5, 0x61, 0x0e, 0xe8, 0x99, 0xe8,
                            0x62, 0x67, 0x2d, 0xa9, 0xeb, 0x98, 0xa2, 0x92, 0x70, 0xec,
                            0xe1, 0x95, 0x6b, 0x75, 0x16, 0x03, 0x24, 0x7d, 0x86, 0x18,
                            0xc7, 0x1b, 0x5b, 0xae, 0xd0, 0x70, 0x08, 0x0b, 0xb8, 0xff,
                            0x3a, 0x93, 0xe7, 0x83, 0xd7, 0x80, 0xdc, 0x4a, 0xac, 0x11,
                            0x18, 0xb0, 0x9c, 0x2a, 0x7b, 0x63 };

int decrypted_length = private_decrypt(dummy,256,privateKey, decrypted);
if(decrypted_length == -1)
{
    printLastError("Private Decrypt failed ");
    exit(0);
}
printf("\n\n Decrypted :- \n");
BIO_dump_fp (stdout, (const char *)decrypted, decrypted_length);
// printf("\n\n Decrypted Text = %s\n",decrypted);
 
}

