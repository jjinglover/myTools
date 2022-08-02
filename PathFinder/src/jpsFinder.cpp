
#include "jpsFinder.h"
#include "myData.h"

namespace jps
{
	jpsFinder::jpsFinder()
	:_dataPtr(nullptr)
	,_goal(Vec2_DEFAULT)
	{
	
	}

	jpsFinder::jpsFinder(myData* ptr)
	:_dataPtr(ptr)
	{
		
	}

	void jpsFinder::findPath(const myVec2& start, const myVec2& goal, std::vector<myVec2>& pathVec)
	{
		_dataPtr->clearGridNodes();
		_goal = goal;

		auto startNode = _dataPtr->getGridNode(start);
		_openList.push(startNode);

		while (!_openList.empty())
		{
			auto node = _openList.top();
			_openList.pop();
			node->_closed = true;

			if (node->_pos == goal)
			{
				return this->trace(node, pathVec);
			}
			this->identitySuccessors(node);
		}
	}

	void jpsFinder::trace(myGridNode* node, std::vector<myVec2>& pathVec)
	{
		std::vector<myVec2> path;
		path.push_back(node->_pos);
		while (node->_parent != nullptr)
		{
			node = node->_parent;
			path.push_back(node->_pos);
		}
		//µ÷ÕûË³Ðò
		pathVec.assign(path.rbegin(), path.rend());
	}

	void jpsFinder::identitySuccessors(myGridNode* node)
	{
		auto vec = _dataPtr->getNeighbours(node);
		for (auto neighbour : vec)
		{
			myVec2 jumpPoint = this->jump(neighbour->_pos, node->_pos);
			if (jumpPoint != Vec2_DEFAULT)
			{
				auto jumpNode = _dataPtr->getGridNode(jumpPoint);
				if (jumpNode->_closed)
				{
					continue;
				}
				double d = this->heuristicValue(std::abs(jumpPoint.x - node->_pos.x), std::abs(jumpPoint.y - node->_pos.y));
				double ng = node->_gValue + d;
				if (!jumpNode->_opened || ng < jumpNode->_gValue)
				{
					jumpNode->_gValue = ng;
					if (!jumpNode->_hValue > 0)
					{
						jumpNode->_hValue = heuristicValue(std::abs(jumpPoint.x - _goal.x), std::abs(jumpPoint.y - _goal.y));
					}
					jumpNode->_fValue = jumpNode->_gValue + jumpNode->_hValue;
					jumpNode->_parent = node;

					if (!jumpNode->_opened)
					{
						_openList.push(jumpNode);
						jumpNode->_opened = true;
					}
				}
			}
		}
	}

	double jpsFinder::heuristicValue(int dx, int dy)
	{
		return dx < dy ? (const_sqrt2 - 1)*dx + dy : (const_sqrt2 - 1)*dy + dx;
	}

	myVec2 jpsFinder::jump(const myVec2 &current, const myVec2 &proposed)
	{
		int x = current.x;
		int y = current.y;
		int dx = current.x - proposed.x;
		int dy = current.y - proposed.y;

		if (!_dataPtr->canPass(x, y))
			return Vec2_DEFAULT;

		if (_goal == current)
			return current;

		// diagonal
		if (dx != 0 && dy != 0)
		{
			if ((_dataPtr->canPass(x - dx, y + dy) && !_dataPtr->canPass(x - dx, y)) ||
				(_dataPtr->canPass(x + dx, y - dy) && !_dataPtr->canPass(x, y - dy)))
			{
				return current;
			}

			if (this->jump(myVec2(x + dx, y), current) != Vec2_DEFAULT ||
				this->jump(myVec2(x, y + dy), current) != Vec2_DEFAULT)
			{
				return current;
			}
		}
		else
		{
			if (dx != 0)
			{
				// horizontal
				if ((_dataPtr->canPass(x + dx, y + 1) && !_dataPtr->canPass(x, y + 1)) ||
					(_dataPtr->canPass(x + dx, y - 1) && !_dataPtr->canPass(x, y - 1)))
				{
					return current;
				}
			}
			else
			{
				// vertical
				if ((_dataPtr->canPass(x + 1, y + dy) && !_dataPtr->canPass(x + 1, y)) ||
					(_dataPtr->canPass(x - 1, y + dy) && !_dataPtr->canPass(x - 1, y)))
				{
					return current;
				}
			}
		}

		if (_dataPtr->canPass(x + dx, y) || _dataPtr->canPass(x, y + dy))
		{
			return jump(myVec2(x + dx, y + dy), current);
		}
		return Vec2_DEFAULT;
	}
};
