#ifndef __myData__
#define __myData__

#include <vector>
#include <stack>

#include "myVec2.h"

namespace jps
{
#define MAP_MAX_WIDTH 2048
#define MAP_MAX_HEIGHT 2048

	class myGridNode;
	class myData
	{
	public:
		myData();
		~myData();

		//设置地图大小，并初始化空地数据
		void setMapSize(int width, int height);

		myGridNode* getGridNode(int x, int y);
		myGridNode* getGridNode(const myVec2& pos);
		//点是否可通过
		bool canPass(int x, int y);
		//点是否在地图区域内
		bool inBounds(int x, int y);
		//跟新阻挡点信息
		void updateWall(int x, int y, bool isWall);
		//获取邻居节点
		std::vector<myGridNode*> getNeighbours(myGridNode* node);
	private:
		//X方向的最大下标
		int _maxIndexX;
		//Y方向的最大下标
		int _maxIndexY;
		std::stack<myGridNode*> _freeNodes,_useNodes;
		//地图空地信息【false表示有阻挡不能通过】
		bool _spaceArr[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];
	};
}
#endif