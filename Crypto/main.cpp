
#include <iostream>
#include "Crypto.h"

void testHMAC_SHA1(const char* msg, const char* key)
{
	const int len = CY_BUFF_SIZE;
	unsigned int outLen = 0;
	unsigned char* out = (unsigned char*)malloc(len);
	memset(out, 0, len);
	auto sha1Str = Crypto::getHMAC(MBEDTLS_MD_SHA1, msg, key, out, &outLen);
	std::cout << "HMAC-SHA1:\n" << sha1Str.c_str() << std::endl;

	unsigned char buff[len] = { 0 };
	size_t olen = 0;
	mbedtls_base64_encode(buff, len, &olen,(const unsigned char *)sha1Str.c_str(), sha1Str.size());
	std::cout << "上面结果进行Base64编码:\n" << buff << std::endl;

	memset(buff, 0, len);
	mbedtls_base64_encode(buff, len, &olen,(unsigned char *)out, outLen);
	std::cout << "HMAC-SHA1原始二进制数据进行Base64编码:\n" << buff << std::endl;

	free(out);
}

int main(int argc, char* argv[])
{
	testHMAC_SHA1("a", "a");
	system("pause");
	return 0;
}




