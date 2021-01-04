#include <stdio.h>
#include <openssl/sha.h>


int main(int argc, const char *argv[])
{
    SHA256_CTX c,c2,c3;
    unsigned char buffer[SHA256_DIGEST_LENGTH];
    int i;
    
    SHA256_Init(&c2);
    SHA256_Update(&c2, "544", 3);
    SHA256_Update(&c2, "rohannedungadi",14);
    SHA256_Final(buffer, &c2);
    printf("H(544||rohannedungadi) :\n");
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n\n");

    SHA256_Init(&c);
    SHA256_Update(&c, "544", 3);
    SHA256_Update(&c, "rohannedungadi"
                    "\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x00\x00\x00\x00\x00\x00\x00\x88"
                    "17XJ1A0544", 70);
    SHA256_Final(buffer, &c);
    printf("H(544||rohannedungadi||17xj1a0544) (seen) :\n");
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n\n");

// 11e99a98 75379759 30c69a34 eebfdb56 2dada5b3 af8e3aa7 588cd210 50747b42

    SHA256_Init(&c3);
    SHA256_Update(&c3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 64);


    c3.h[0] = 0x11e99a98; /* <-- This is the hash we already had */
    c3.h[1] = 0x75379759;
    c3.h[2] = 0x30c69a34;
    c3.h[3] = 0xeebfdb56;
    c3.h[4] = 0x2dada5b3;
    c3.h[5] = 0xaf8e3aa7;
    c3.h[6] = 0x588cd210;
    c3.h[7] = 0x50747b42;



    printf("H(544||rohannedungadi||17xj1a0544) (attacked) :\n");
    SHA256_Update(&c3, "17XJ1A0544", 9); /* This is the appended data. */
    SHA256_Final(buffer, &c3);
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    printf("%02x", buffer[i]);
    }
    printf("\n");

    return 0;
}