#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *S_valid = BN_new();
    BIGNUM *S_corrupt = BN_new();
    BIGNUM *M_prime1 = BN_new();
    BIGNUM *M_prime2 = BN_new();

    BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
    BN_hex2bn(&e, "010001");

    // Original valid signature S
    BN_hex2bn(&S_valid, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");

    // Corrupted signature (last byte 2F changed to 3F)
    BN_hex2bn(&S_corrupt, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");

    // Verification step: M' = S^e mod n
    BN_mod_exp(M_prime1, S_valid, e, n, ctx);
    BN_mod_exp(M_prime2, S_corrupt, e, n, ctx);

    printBN("Decrypted Valid Signature   (M'):", M_prime1);
    printBN("Decrypted Corrupt Signature (M'):", M_prime2);

    BN_free(n); BN_free(e); BN_free(S_valid); BN_free(S_corrupt);
    BN_free(M_prime1); BN_free(M_prime2); BN_CTX_free(ctx);
    return 0;
}
