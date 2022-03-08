// PathFinder.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "src/myData.h"
#include "src/myVec2.h"
#include "src/jpsFinder.h"
#define MAX_SIDE_LEN 100

int main()
{
	std::vector<std::vector<bool>> dataV;
	std::vector<bool> tmpV;
	for (size_t i = 0; i < MAX_SIDE_LEN; i++)
	{
		tmpV.clear();
		for (size_t j = 0; j < MAX_SIDE_LEN; j++)
		{
			tmpV.push_back(true);
		}
		dataV.push_back(tmpV);
	}

	auto data = new jps::myData();
	data->initData(dataV, MAX_SIDE_LEN, MAX_SIDE_LEN);

	int t0 = clock();
	std::vector<jps::myVec2> pathVec;
	jps::jpsFinder(data).findPath(jps::myVec2(0, 0), jps::myVec2(MAX_SIDE_LEN - 1, MAX_SIDE_LEN - 2), pathVec);
	int t1 = clock() - t0;
	delete data;

	getchar();
	return 0;
}