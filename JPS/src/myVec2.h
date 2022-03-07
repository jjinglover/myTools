#ifndef __myVec2__
#define __myVec2__

namespace jps
{
	class myVec2
	{
	public:
		int x;
		int y;
		myVec2()
		{
			x = 0;
			y = 0;
		}
		myVec2(int ix, int iy)
		{
			x = ix;
			y = iy;
		}

		friend bool operator ==(const myVec2 &left, const myVec2 &right)
		{
			return left.x == right.x && left.y == right.y;
		}

		friend bool operator !=(const myVec2 & left, const myVec2 &right)
		{
			return !(left == right);
		}

	};
	//Ä¬ÈÏ×ø±êÖµ
	static myVec2 Vec2_DEFAULT = myVec2(-1, -1);
};
#endif