
#ifndef __Crypto__
#define __Crypto__

#include <string>
#include "include/mbedtls/md.h"
#include "include/mbedtls/base64.h"
#define CY_BUFF_SIZE 256

class Crypto
{
public:
	static void hexifyLower(char* obuf, const unsigned char* ibuf, unsigned int len);
	static void hexifyUpper(char* obuf, const unsigned char* ibuf, unsigned int len);
	//根据类型获取HMAC
	static std::string getHMAC(mbedtls_md_type_t type, const char* message, const char* key, unsigned char* out, unsigned int* outLen);

	static std::string getMD5Str(const char* message, unsigned int len);
};
#endif // !__Crypto__

