
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
		, _opened(false)
		, _closed(false)
		, _parent(nullptr)
		{
		}
		myGridNode(int x, int y)
		: _hValue(0)
		, _fValue(0)
		, _gValue(0)
		, _opened(false)
		, _closed(false)
		, _parent(nullptr)
		,_pos(myVec2(x, y))
		{
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