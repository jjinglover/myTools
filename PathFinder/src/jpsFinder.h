#ifndef __jpsFinder__
#define __jpsFinder__

#include <vector>
#include <queue>
#include "myVec2.h"
#include "myGridNode.h"

namespace jps
{
	class myData;
	class jpsFinder
	{
	public:
		jpsFinder();
		jpsFinder(myData *ptr);
		//jps寻路
		void findPath(const myVec2& start, const myVec2 &goal, std::vector<myVec2> &pathVec);
	private:
		void trace(myGridNode* node, std::vector<myVec2>& pathVec);
		//获取后继节点
		void identitySuccessors(myGridNode* node);
		//计算两点之间的路径消耗
		double heuristicValue(int dx, int dy);
		myVec2 jump(const myVec2& current, const myVec2& proposed);
	private:
		std::priority_queue<myGridNode*, std::vector<myGridNode*>, myGridNodeCmp> _openList;
		myData* _dataPtr;
		myVec2 _goal;
		//对角线消耗
		const double const_sqrt2 = 1.42;
	};
}

#endif