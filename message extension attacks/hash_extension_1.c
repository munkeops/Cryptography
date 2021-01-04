#include <stdio.h>
#include <openssl/md5.h>

int main(int argc, const char *argv[])
{
    MD5_CTX c,c2,c3;
    unsigned char buffer[MD5_DIGEST_LENGTH];
    int i;
    
    MD5_Init(&c2);
    MD5_Update(&c2, "544", 3);
    MD5_Update(&c2, "rohannedungadi",14);
    //                 "\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    //                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    //                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    //                 "\x00\x00\x00\x00"
    //                 "\x50\x00\x00\x00\x00\x00\x00\x00"
    //                 , 64);
    MD5_Final(buffer, &c2);
    printf("original hash :\n");
    for (i = 0; i < 16; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n");



    // printf("7627f8b562724d10247c107ae2195bb1\n");
// 67e1cd407e8072d87e3feda06bc84bfa
// printf("1b11bc4fa8a4eddbeb02f7094bc950a2\n");

    MD5_Init(&c);
    MD5_Update(&c, "544", 3);
    MD5_Update(&c, "rohannedungadi"
                    "\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                    "\x88\x00\x00\x00\x00\x00\x00\x00"
                    "17XJ1A0544", 70);
    MD5_Final(buffer, &c);
    printf("appended hash :\n");
    for (i = 0; i < 16; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n");



    MD5_Init(&c3);
    MD5_Update(&c3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 64);

    c3.A = htonl(0x1b11bc4f); /* <-- This is the hash we already had */
    c3.B = htonl(0xa8a4eddb);
    c3.C = htonl(0xeb02f709);
    c3.D = htonl(0x4bc950a2);

    printf("after extension attack : \n");
    MD5_Update(&c3, "17XJ1A0544", 9); /* This is the appended data. */
    MD5_Final(buffer, &c3);
    for (i = 0; i < 16; i++) {
    printf("%02x", buffer[i]);
    }
    printf("\n");
    // printf("%d\n",MD5_DIGEST_LENGTH);
    return 0;
}