
#include "Crypto.h"
#include "include/mbedtls/md5.h"
#include "include/mbedtls/md.h"

void Crypto::hexifyLower(char* obuf, const unsigned char* ibuf, unsigned int len)
{
	unsigned char l, h;
	while (len != 0)
	{
		h = (*ibuf) / 16;
		l = (*ibuf) % 16;

		if (h < 10)
			*obuf++ = '0' + h;
		else
			*obuf++ = 'a' + h - 10;

		if (l < 10)
			*obuf++ = '0' + l;
		else
			*obuf++ = 'a' + l - 10;

		++ibuf;
		len--;
	}
}

void Crypto::hexifyUpper(char* obuf, const unsigned char* ibuf, unsigned int len)
{
	unsigned char l, h;
	while (len != 0)
	{
		h = (*ibuf) / 16;
		l = (*ibuf) % 16;

		if (h < 10)
			*obuf++ = '0' + h;
		else
			*obuf++ = 'A' + h - 10;

		if (l < 10)
			*obuf++ = '0' + l;
		else
			*obuf++ = 'A' + l - 10;

		++ibuf;
		len--;
	}
}

std::string Crypto::getHMAC(mbedtls_md_type_t type, const char* message, const char* key,
	unsigned char* out, unsigned int* outLen)
{
	//根据类型获取处理摘要信息
	const mbedtls_md_info_t* info = mbedtls_md_info_from_type(type);

	mbedtls_md_context_t ctx;
	//初始化ctx
	mbedtls_md_init(&ctx);
	//绑定ctx与info
	mbedtls_md_setup(&ctx, info, 1);
	//sets the HMAC key
	mbedtls_md_hmac_starts(&ctx, (unsigned char*)key, strlen(key));
	//sets the HMAC message
	mbedtls_md_hmac_update(&ctx, (unsigned char*)message, strlen(message));
	unsigned char hBuff[CY_BUFF_SIZE] = { 0 };
	mbedtls_md_hmac_finish(&ctx, hBuff);

	//获取数据信息的长度
	const int len = mbedtls_md_get_size(info);
	//记录HMAC计算出的原始数据
	memcpy(out, hBuff, len);
	//记录HMAC计算原始数据的长度
	*outLen = len;

	char strBuff[CY_BUFF_SIZE] = { 0 };
	hexifyLower(strBuff, hBuff, len);
	//释放资源
	mbedtls_md_free(&ctx);
	return strBuff;
}

std::string Crypto::getMD5Str(const char* message, unsigned int len)
{
	unsigned char outBuff[16] = { 0 };
	mbedtls_md5((const unsigned char*)message, len, outBuff);
	char strBuff[CY_BUFF_SIZE] = { 0 };
	hexifyLower(strBuff, outBuff, len);
	return strBuff;
}