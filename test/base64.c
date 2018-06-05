#include "base64.h"

int base64_decode(char *text, unsigned char *dst, int numBytes )
{
    const char* cp;
    int space_idx = 0, phase;
    int d, prev_d = 0;
    unsigned char c;
    space_idx = 0;
    phase = 0;
    for ( cp = text; *cp != '\0'; ++cp ) {
        d = DecodeMimeBase64[(int) *cp];
        if ( d != -1 ) {
            switch ( phase ) {
                case 0:
                    ++phase;
                    break;
                case 1:
                    c = ( ( prev_d << 2 ) | ( ( d & 0x30 ) >> 4 ) );
                    if ( space_idx < numBytes )
                        dst[space_idx++] = c;
                    ++phase;
                    break;
                case 2:
                    c = ( ( ( prev_d & 0xf ) << 4 ) | ( ( d & 0x3c ) >> 2 ) );
                    if ( space_idx < numBytes )
                        dst[space_idx++] = c;
                    ++phase;
                    break;
                case 3:
                    c = ( ( ( prev_d & 0x03 ) << 6 ) | d );
                    if ( space_idx < numBytes )
                        dst[space_idx++] = c;
                    phase = 0;
                    break;
            }
            prev_d = d;
        }
    }
    return space_idx;
}
int base64_encode(char *text, int numBytes, char **encodedText)
{
    unsigned char input[3]  = {0,0,0};
    unsigned char output[4] = {0,0,0,0};
    int   index, i, j, size;
    char *p, *plen;
    plen           = text + numBytes - 1;
    size           = (4 * (numBytes / 3)) + (numBytes % 3? 4 : 0) + 1;
    (*encodedText) = (char*)malloc(size);
    j              = 0;
    for  (i = 0, p = text;p <= plen; i++, p++) {
        index = i % 3;
        input[index] = *p;
        if (index == 2 || p == plen) {
            output[0] = ((input[0] & 0xFC) >> 2);
            output[1] = ((input[0] & 0x3) << 4) | ((input[1] & 0xF0) >> 4);
            output[2] = ((input[1] & 0xF) << 2) | ((input[2] & 0xC0) >> 6);
            output[3] = (input[2] & 0x3F);
            (*encodedText)[j++] = MimeBase64[output[0]];
            (*encodedText)[j++] = MimeBase64[output[1]];
            (*encodedText)[j++] = index == 0? '=' : MimeBase64[output[2]];
            (*encodedText)[j++] = index <  2? '=' : MimeBase64[output[3]];
            input[0] = input[1] = input[2] = 0;
        }
    }
    (*encodedText)[j] = '\0';
    return size;
}
int main(int argc, char* argv[])
{
    //    char* plain_text = "Å×½ºÆ®Test`1234567890-=\[];',./";
    char* b64encoded_text = NULL;
    //    printf("plain text\n");
    //    printf("%s\n\n", plain_text);
    int fd;
    if ((fd = open("obama.jpg", O_RDONLY)) == 0) {
        fprintf(stderr, "fopen error obama.jpg\n");
        exit(1);
    }
    char tmp[1024] = { 0, };
    char *b64encoded_test = NULL;

    int nread = read(fd, tmp, sizeof(tmp)); 
    printf("%s\n\n", tmp);

    int len_b64_encoded = base64_encode(tmp, strlen(tmp)+1, &b64encoded_text);
    printf("b64 encoded text\n");
    printf("%s\n\n", b64encoded_text);
    // base 64 ¿¿¿
    // ¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿
    // ¿¿ ¿¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿¿.
    unsigned char *dst = (unsigned char*)malloc(1000);
    int len_b64 = base64_decode(b64encoded_text,dst,1000);
    printf("b64 decoded tex\n");
    printf("%s\n\n", dst);

    int fd2;
    if ((fd2 = open("test.jpg", O_RDWR | O_CREAT, 0644)) == 0) {
        fprintf(stderr, " make file error\n");
        exit(1);
    }
    
    
    if(dst != NULL) 
        free(dst);
    write(fd2, dst, strlen(dst));

    if(b64encoded_text != NULL)
        free(b64encoded_text);



}


//http://www.iamcorean.net/125 [I'm MK!]*/
