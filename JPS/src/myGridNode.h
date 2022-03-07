
#ifndef __myGridNode__
#define __myGridNode__

#include "myVec2.h"

namespace jps
{
	class myGridNode
	{
	public:
		myGridNode() 
		: _hValue(0)
		, _fValue(0)
		, _gValue(0)
		, _opened(true)
		, _closed(false)
		, _parent(nullptr)
		{
		}
		myGridNode(int x, int y)
		: myGridNode(myVec2(x, y))
		{
		}

		myGridNode(myVec2 pos)
		{
			_pos = pos;
		}

		double _hValue;
		double _fValue;
		double _gValue;
		bool _opened;
		bool _closed;
		myGridNode *_parent;
		myVec2 _pos;
	};
};

#endif