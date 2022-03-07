#ifndef __myData__
#define __myData__

#include <vector>
#include <stack>

#include "myVec2.h"

namespace jps
{
	class myGridNode;
	class myData
	{
	public:
		myData();
		~myData();

		//初始化地图数据
		void initData(const std::vector<std::vector<bool>>& spaceVec, int maxX, int maxY);

		myGridNode* getGridNode(int x, int y);
		myGridNode* getGridNode(const myVec2& pos);
		//点是否可通过
		bool canPass(int x, int y);
		//点是否在地图区域内
		bool inBounds(int x, int y);
		//获取邻居节点
		std::vector<myGridNode*> getNeighbours(myGridNode* node);
	private:
		//X方向的最大下标
		int _maxIndexX;
		//Y方向的最大下标
		int _maxIndexY;
		std::stack<myGridNode*> _freeNodes,_useNodes;
		//地图空地信息【false表示有阻挡不能通过】
		std::vector<std::vector<bool>> _spaceVec;
	};
}
#endif