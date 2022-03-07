﻿
#include "myData.h"
#include "myGridNode.h"

namespace jps {


	myData::myData()
		:_maxIndexX(0)
		, _maxIndexY(0)
	{

	}

	myData::~myData()
	{
		while (!_freeNodes.empty())
		{
			auto ptr = _freeNodes.top();
			delete ptr;
			ptr = nullptr;
			_freeNodes.pop();
		}

		while (!_useNodes.empty())
		{
			auto ptr = _useNodes.top();
			delete ptr;
			ptr = nullptr;
			_useNodes.pop();
		}
	}

	void myData::initData(const std::vector<std::vector<bool>>& spaceVec, int maxX, int maxY)
	{
		_maxIndexX = maxX;
		_maxIndexY = maxY;
		_spaceVec = spaceVec;
	}

	myGridNode* myData::getGridNode(int x, int y)
	{
		if (_freeNodes.empty())
		{
			auto gridNode = new myGridNode(x,y);
			_useNodes.push(gridNode);
			return gridNode;
		}
		return nullptr;
	}

	myGridNode* myData::getGridNode(const myVec2& pos)
	{
		return this->getGridNode(pos.x, pos.y);
	}

	bool myData::canPass(int x, int y)
	{
		return this->inBounds(x, y) && _spaceVec[x][y];
	}

	bool myData::inBounds(int x, int y)
	{
		return x >= 0 && x < _maxIndexX&&
			y >= 0 && y < _maxIndexY;
	}

	static std::vector<myVec2> neighbourDirVec =
	{
		myVec2(-1, 0), // left
		myVec2(1, 0), // right
		myVec2(0, 1), // top
		myVec2(0, -1), // bottom
		// diagonal
		myVec2(-1, -1), // left top
		myVec2(-1, 1), // left bottom
		myVec2(1, -1), // right bottom
		myVec2(1, 1) // right top
	};

	std::vector<myGridNode*> myData::getNeighbours(myGridNode* node)
	{
		std::vector<myGridNode*> tmpVec;
		if (node->_parent != nullptr)
		{
			myVec2 n = node->_pos;
			myVec2 p = node->_parent->_pos;

			myVec2 dNorm = myVec2(
				(n.x - p.x) / std::max(std::abs(n.x - p.x), 1),
				(n.y - p.y) / std::max(std::abs(n.y - p.y), 1));

			// Diagonal
			if (dNorm.x != 0 && dNorm.y != 0)
			{
				if (this->canPass(n.x, n.y + dNorm.y))
				{
					tmpVec.push_back(this->getGridNode(n.x,n.y + dNorm.y));
				}
				if (canPass(n.x + dNorm.x, n.y))
				{
					tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y));
				}
				if ((canPass(n.x, n.y + dNorm.y) || canPass(n.x + dNorm.x, n.y)) && canPass(n.x + dNorm.x, n.y + dNorm.y))
				{
					tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y + dNorm.y));
				}

				if (!canPass(n.x - dNorm.x, n.y) && canPass(n.x, n.y + dNorm.y) && canPass(n.x - dNorm.x, n.y + dNorm.y))
				{
					tmpVec.push_back(this->getGridNode(n.x - dNorm.x,n.y + dNorm.y));
				}

				if (!canPass(n.x, n.y - dNorm.y) && canPass(n.x + dNorm.x, n.y) && canPass(n.x + dNorm.x, n.y - dNorm.y))
				{
					tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y - dNorm.y));
				}
			}
			else
			{
				if (dNorm.x == 0)
				{
					if (canPass(n.x, n.y + dNorm.y))
					{
						tmpVec.push_back(this->getGridNode(n.x,n.y + dNorm.y));

						if (!canPass(n.x + 1, n.y) && canPass(n.x + 1, n.y + dNorm.y))
							tmpVec.push_back(this->getGridNode(n.x + 1,n.y + dNorm.y));

						if (!canPass(n.x - 1, n.y) && canPass(n.x - 1, n.y + dNorm.y))
							tmpVec.push_back(this->getGridNode(n.x - 1,n.y + dNorm.y));
					}
				}
				else if (canPass(n.x + dNorm.x, n.y))
				{
					tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y));

					if (!canPass(n.x, n.y + 1) && canPass(n.x + dNorm.x, n.y + 1))
						tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y + 1));

					if (!canPass(n.x, n.y - 1) && canPass(n.x + dNorm.x, n.y - 1))
						tmpVec.push_back(this->getGridNode(n.x + dNorm.x,n.y - 1));
				}
			}
		}
		else
		{
			for (const myVec2 &dir: neighbourDirVec)
			{
				int propX = node->_pos.x + dir.x;
				int propY = node->_pos.y + dir.y;

				if (this->canPass(propX, propY))
				{
					tmpVec.push_back(this->getGridNode(propX, propY));
				}
			}
		}
		return tmpVec;
	}
}