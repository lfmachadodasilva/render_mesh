#ifndef MD5_H
#define MD5_H

#define HASH_LENGTH        16
#define HASH_STRING_LENGTH 32

# ifdef __cplusplus
extern "C" {
# endif

typedef struct {
	unsigned int buf[4];
	unsigned int bits[2];
	unsigned char in[64];
} MD5Context;

void MD5Init(MD5Context *context);
void MD5Update(MD5Context *context, unsigned char const *buf, unsigned len);
void MD5Final(unsigned char digest[16], MD5Context *context);
void MD5Transform(unsigned int buf[4], unsigned int const in[16]);
char *MD5FinalString(MD5Context *ctx);

# ifdef __cplusplus
}
# endif

#endif
