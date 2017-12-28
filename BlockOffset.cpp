#include "Shape.h"

Shape::BlockOffset::BlockOffset()
{
	int type;
	int form;

	type = (int)Type::J;

	//   [0]
	//	 [1]
	//[2][3]
	form = 0;
	data[type][form][0] = { +1,+1 };
	data[type][form][1] = { +1,+0 };
	data[type][form][2] = { +0,-1 };
	data[type][form][3] = { +1,-1 };

	//[0]
	//[1][2][3]
	form = 1;
	data[type][form][0] = { -1,+0 };
	data[type][form][1] = { -1,-1 };
	data[type][form][2] = { +0,-1 };
	data[type][form][3] = { +1,-1 };

	//[0][1]
	//[2]
	//[3]
	form = 2;
	data[type][form][0] = { -1,+1 };
	data[type][form][1] = { +0,+1 };
	data[type][form][2] = { -1,+0 };
	data[type][form][3] = { -1,-1 };

	//[0][1][2]
	//      [3]
	form = 3;
	data[type][form][0] = { -1,+1 };
	data[type][form][1] = { +0,+1 };
	data[type][form][2] = { +1,+1 };
	data[type][form][3] = { +1,+0 };



	type = (int)Type::L;

	//[0]
	//[1]
	//[2][3]
	form = 0;
	data[type][form][0] = { -1,+1 };
	data[type][form][1] = { -1,+0 };
	data[type][form][2] = { -1,-1 };
	data[type][form][3] = { +0,-1 };

	//[1][2][3]
	//[0]
	form = 1;
	data[type][form][0] = { -1,+0 };
	data[type][form][1] = { -1,+1 };
	data[type][form][2] = { +0,+1 };
	data[type][form][3] = { +1,+1 };

	//[0][1]
	//   [2]
	//	 [3]
	form = 2;
	data[type][form][0] = { +0,+1 };
	data[type][form][1] = { +1,+1 };
	data[type][form][2] = { +1,+0 };
	data[type][form][3] = { +1,-1 };

	//      [3]
	//[0][1][2]
	form = 3;
	data[type][form][0] = { -1,-1 };
	data[type][form][1] = { +0,-1 };
	data[type][form][2] = { +1,-1 };
	data[type][form][3] = { +1,+0 };


	type = (int)Type::Z;

	//[0][1]
	//   [2][3]
	// form 0, form 2
	data[type][0][0] = data[type][2][0] = { -1,+1 };
	data[type][0][1] = data[type][2][1] = { +0,+1 };
	data[type][0][2] = data[type][2][2] = { +0,+0 };
	data[type][0][3] = data[type][2][3] = { +1,+0 };

	//   [0]
	//[1][2]
	//[3]
	// form 1, form 3
	data[type][1][0] = data[type][3][0] = { +0,+1 };
	data[type][1][1] = data[type][3][1] = { -1,+0 };
	data[type][1][2] = data[type][3][2] = { +0,+0 };
	data[type][1][3] = data[type][3][3] = { -1,-1 };


	type = (int)Type::l;

	//[0]
	//[1]
	//[2]
	//[3]
	//form 0, form 2
	data[type][0][0] = data[type][2][0] = { +0,+2 };
	data[type][0][1] = data[type][2][1] = { +0,+1 };
	data[type][0][2] = data[type][2][2] = { +0,+0 };
	data[type][0][3] = data[type][2][3] = { +0,-1 };

	//[0][1][2][3]
	//form 1, form 3
	data[type][1][0] = data[type][3][0] = { -1,-1 };
	data[type][1][1] = data[type][3][1] = { +0,-1 };
	data[type][1][2] = data[type][3][2] = { +1,-1 };
	data[type][1][3] = data[type][3][3] = { +2,-1 };


	type = (int)Type::O;

	//[2][3]
	//[0][1]
	//fomr 0,1,2,3
	data[type][0][0] = data[type][1][0] = data[type][2][0] = data[type][3][0] = { -1,-1 };
	data[type][0][1] = data[type][1][1] = data[type][2][1] = data[type][3][1] = { +0,-1 };
	data[type][0][2] = data[type][1][2] = data[type][2][2] = data[type][3][2] = { -1,+0 };
	data[type][0][3] = data[type][1][3] = data[type][2][3] = data[type][3][3] = { +0,+0 };

	type = (int)Type::S;

	//   [0][1]
	//[2][3]
	// form 0, form 2
	data[type][0][0] = data[type][2][0] = { +0,+0 };
	data[type][0][1] = data[type][2][1] = { +1,+0 };
	data[type][0][2] = data[type][2][2] = { -1,-1 };
	data[type][0][3] = data[type][2][3] = { +0,-1 };

	//[0]
	//[1][2]
	//   [3]
	// form 1, form 3
	data[type][1][0] = data[type][3][0] = { -1,+1 };
	data[type][1][1] = data[type][3][1] = { -1,+0 };
	data[type][1][2] = data[type][3][2] = { +0,+0 };
	data[type][1][3] = data[type][3][3] = { +0,-1 };

	type = (int)Type::T;

	//   [0]
	//[1][2][3]
	form = 0;
	data[type][form][0] = { +0,+0 };
	data[type][form][1] = { -1,-1 };
	data[type][form][2] = { +0,-1 };
	data[type][form][3] = { +1,-1 };

	//[0]
	//[1][2]
	//[3]
	form = 1;
	data[type][form][0] = { -1,+1 };
	data[type][form][1] = { -1,+0 };
	data[type][form][2] = { +0,+0 };
	data[type][form][3] = { -1,-1 };

	//[1][2][3]
	//   [0]
	form = 2;
	data[type][form][0] = { +0,+0 };
	data[type][form][1] = { -1,+1 };
	data[type][form][2] = { +0,+1 };
	data[type][form][3] = { +1,+1 };

	//   [0]
	//[1][2]
	//   [3]
	form = 3;
	data[type][form][0] = { +1,+1 };
	data[type][form][1] = { +0,+0 };
	data[type][form][2] = { +1,+0 };
	data[type][form][3] = { +1,-1 };
}
