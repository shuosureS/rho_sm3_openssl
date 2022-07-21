#include"openssl/evp.h"
#include"openssl/rsa.h"
#include<iostream>
#define MAX 60000
using namespace std;
int sm3_openssl(const void* message, size_t len, unsigned char* hash)
{
    EVP_MD_CTX* md_ctx;
    const EVP_MD* md;

    md = EVP_sm3();
    md_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(md_ctx, md, NULL);
    EVP_DigestUpdate(md_ctx, message, len);
    EVP_DigestFinal_ex(md_ctx, hash, NULL);
    EVP_MD_CTX_free(md_ctx);
    return 0;
}

int inttohex(int aa, unsigned char* buffer)
{
    static int  i = 0;
    i = 0;
    if (aa < 16)
    {
        if (aa < 10)
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'a';
        buffer[i + 1] = '\0';
    }
    else
    {
        inttohex(aa / 16, buffer);
        i++;
        aa %= 16;
        if (aa < 10)
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'a';
    }


    return i + 1;
}


int main()
{
    unsigned char tinput[256] = "";
    int tlen;
    unsigned char tagart[32];
    unsigned char input[256] = "";
    int ilen = 0;
    unsigned char output[32];
    //可以改变q和i
    unsigned int q = 11;
    unsigned int i = 51;
    int start, end;
    start = clock();
    while (1) {

        q = (q * q + 1)%MAX ;
        ilen = inttohex(q, input);
        i = (i *i  + 1)%MAX ;
        i = (i *i  + 1)%MAX ;
        tlen = inttohex(i, tinput);
        sm3_openssl(tinput, tlen, tagart);
        sm3_openssl(input, ilen, output);

        if (output[0] == tagart[0]&& output[1] == tagart[1]&& output[2] == tagart[2]&& output[3] == tagart[3])
        {
            end = clock();
            printf("攻击成功\n");
            printf("time=%dms\n", end - start);

            break;
        }
        
    }




}
