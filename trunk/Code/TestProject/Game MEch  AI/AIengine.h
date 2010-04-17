///JOSH Kilgore
// Basic Ai engine:
//ideally, uses game tree to make decisions about moves.



#ifndef AI_H
#endef AI_H

#include <qmemarray.h>
#include "board.h"

class Ai
{

public: 
	Ai(Board* board);
	bool getMove(int px, int py);
	void setLevel(int level) {mMaxDepth = level;}
	int spacevalue() {return mValue;}
protected: 
	bool gameTree(Board* board, int& px, int &py, int& spacevalue, int depth);
	int evaluateBoard( Board* board, int player);
	int getLineValue(int cnt[], int player);

private:
	Board* mBoard;
	int mMaxDepth;
	int mValue;
	QMemArray<int> mValues;
};
#endif

/////////////////////////////////////////////////////////////////////////
/
