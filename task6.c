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
    BIGNUM *S = BN_new();
    BIGNUM *M_prime = BN_new();

    // 1. Modulus (n) extracted from c1.pem
    BN_hex2bn(&n, "AD1E66CC7F9DE4EB7F8317273D11D9F2532037CDF00C1402EEE1CB8808D2FA7B3BC2C0007C768776DB7FCC25FA918C4B16892BD7DF0C3083EB716AA8506A13D7939A8DD192042196EE796B4E0BB1744B70AE9CAE404E3B47637689F26E686B7C6AED06A62F6D16ADC5E9E4BF44A0E1FAE1465E30621E1D9D6D0B39544685BB751B9435F739BD0AA325ABB2E551D004FBA7776B9FBEA697C672758B99B11511C2C73C09DB97EFE229AB90A50954D4C8BEC040678C4E6D2BC43BEFC9DA5E717E0EC79D409ECD122F9B428A274C7133F6BC9E11C507B904EFEE70296BFCC2A9EB399579F5A4CB382D927749581B9132E3F916C1A2FFEE8B04D7B6404459AC2F647F");

    // 2. Exponent (e) extracted from c1.pem (0x10001 -> 010001)
    BN_hex2bn(&e, "010001");

    // 3. Signature (S) extracted from c0.pem
    BN_hex2bn(&S, "2503824558e14cbd175c2030b31601ba8a6d6412f79d17027f55ab2c1229723");

    // 4. Compute M' = S^e mod n
    BN_mod_exp(M_prime, S, e, n, ctx);

    // Print decrypted signature structure
    printBN("Decrypted Signature Structure (M'):", M_prime);

    // Memory cleanup
    BN_free(n); 
    BN_free(e); 
    BN_free(S); 
    BN_free(M_prime);
    BN_CTX_free(ctx);

    return 0;
}
