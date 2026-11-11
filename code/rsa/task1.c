#include <stdio.h>
#include <openssl/bn.h>

// Helper function to convert a BIGNUM structure to a hex string and print it
void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a); // Convert big number to hex
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);         // Free dynamically allocated string memory
}

int main() {
    // BN_CTX holds temporary variables used internally by OpenSSL big number APIs
    BN_CTX *ctx = BN_CTX_new();

    // Allocate memory for big number variables
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *p_minus_1 = BN_new();
    BIGNUM *q_minus_1 = BN_new();
    BIGNUM *phi = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *one = BN_new();

    // Assign hex values provided in the lab assignment to variables p, q, and e
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0188C3");
    BN_dec2bn(&one, "1"); // Set constant value 1

    // Calculate phi(n) = (p - 1) * (q - 1)
    BN_sub(p_minus_1, p, one);              // p_minus_1 = p - 1
    BN_sub(q_minus_1, q, one);              // q_minus_1 = q - 1
    BN_mul(phi, p_minus_1, q_minus_1, ctx); // phi = (p - 1) * (q - 1)

    // Step 2: Calculate private key d 
    // BN_mod_inverse computes the modular multiplicative inverse of e mod phi
    BN_mod_inverse(d, e, phi, ctx);

    // Print the derived private key
    printBN("Derived Private Key (d):", d);

    // Free memory to prevent leaks
    BN_free(p); BN_free(q); BN_free(e);
    BN_free(p_minus_1); BN_free(q_minus_1);
    BN_free(phi); BN_free(d); BN_free(one);
    BN_CTX_free(ctx);

    return 0;
}
