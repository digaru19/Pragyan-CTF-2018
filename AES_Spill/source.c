#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

// Messages :-
char ciphertext_msg[] = "\n The encrypted message for the given plaintext is :- \n";

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

void read_AES_key(char *s) {
    FILE *file = fopen("key.aes", "rb");
    if(file == NULL)
        return;
    fgets(s,33,file);
    s[32] = 0;
    fclose(file);
    // printf("Key is :- %s \n", s);
}

void read_AES_IV(char *s) {
    FILE *file = fopen("iv.aes", "rb");
    if(file == NULL)
        return;
    fgets(s,17,file);
    s[16] = 0;
    fclose(file);
    // printf("IV is :- %s \n", s);
}

void clear_buf(char *s, int size) {
    memset(s, 0, size);
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;
  int plaintext_len;

  char iv[20];
  char key[40];
  read_AES_key(key);
  read_AES_IV(iv);

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

int encrypt(unsigned char *plaintext, int plaintext_len)
{
  EVP_CIPHER_CTX *ctx;

  int len;
  int ciphertext_len;
  int decryptedtext_len;
  char ciphertext[128];
  char key[40];
  char iv[20];

  clear_buf(key,40);
  clear_buf(iv,20);

  read_AES_key(key);
  read_AES_IV(iv);

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  /* Do something useful with the ciphertext here */
  printf(ciphertext_msg);
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

  unsigned char decryptedtext[128];

  decryptedtext_len = decrypt(ciphertext, ciphertext_len, decryptedtext);
  decryptedtext[decryptedtext_len] = '\0';
  printf("\nDecrypted text is:\n");
  printf("%s\n\n", decryptedtext);
  
  clear_buf(key,40);
  clear_buf(iv,20);

  return ciphertext_len;
}

int main (void)
{

  /* Message to be encrypted */
  // unsigned char *plaintext =
  //               (unsigned char *)"The quick brown fox jumps over the lazy dog";

  printf("Enter message :- ");
  unsigned char plaintext[128];
  scanf("%s", plaintext);
  plaintext[127] = 0;

  printf("\nYour message is :- \n");
  printf(plaintext);
  printf("\n\n");

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  
  encrypt(plaintext, strlen(plaintext));

  return 0;
}
