
#include <iostream>
#include <string>
#include "include/mbedtls/md5.h"

void hexifyLower(char *obuf, const unsigned char *ibuf, int len)
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

void hexifyUpper(char *obuf, const unsigned char *ibuf, int len)
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

int main(int argc, char* argv[])
{
	if (argc==2) {
		auto fp = fopen(argv[1], "r");
		if (fp)
		{
			fseek(fp,0, SEEK_END);
			int sz = ftell(fp);
			fseek(fp,0, SEEK_SET);

			int len = sz * sizeof(char);
			char *buff = (char *)(malloc(len));
			memset(buff, 0, len);
			fread(buff, sz, 1, fp);
			fclose(fp);

			unsigned char outArr[16] = { 0 };
			mbedtls_md5_ret((const unsigned char *)buff, sz, outArr);
			free(buff);

			char outBuff[33] = { 0 };
			hexifyLower(outBuff, outArr, 16);
			std::cout << outBuff << std::endl;
			hexifyUpper(outBuff, outArr, 16);
			std::cout << outBuff << std::endl;
		}
	}
	system("pause");
	return 0;
}



