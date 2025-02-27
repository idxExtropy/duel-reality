/////////////Josh Kilgore
/// 
#include <stdlib.h>
#include "board.h"
#define BOARD_X 10
#define BOARD_Y 10
#define NUMPIECESFROMSETTINGS 6
#define PLAYER_EMPTY 0
#define PLAYER_1 1
#define PLAYER_2 2



Board::Board()

mBoard.resize(BOARD_X*BOARD_Y);

void Board::copy(Board* src) //copies contents of board except for view & sprites
{
 	mBoard.duplicate(src->mBoard);  //DEEP COPY!!
	 mRunning = src->mRunning;
	 mNextPlayer = src->mNextPlayer;
	 mMoveCounter = src->mMoveCounter;
}

void Board::resetBoard()    //establishes pristine board: \par
{
	mBoard.fill(PLAYER_EMPTY);
	mRunning = false;
	mMoveCounter = 0;
	int player = PLAYER_1;
	for (int i=0; i<NUMPIECESFROMSETINGS; i++)
	int x, y;
	 do
	{
		x= random(BOARD_X-2)+1; //adjust for positioning of pieces
		y = random(BOARD_Y-2)+1;
	 }
	 while (getPiece(x,y) != PLAYER_EMPTY);
	setPiece(x,y,player);
	if (player == PLAYER_1) player = player2;
	else player = Player_1;
}


void Board::switchPlayer() //switches between players
{
	if (mNextPlayer == PLAYER_1) {mNextPlayer=PLAYER_2;}
	else {mNextPlayer = PLAYER1;}
}


void Board::setPiece(int x, int y, int player)  //puts piece on given coord of board
{
    mBoard.at(x+BOARD_X*y) = player;   //re-do for grid layout [mapgrid]
	emit signalSetPiece(x,y,player);
}


int Board::getPiece(int x, int y)
{
  return mBoard.at(x+BOARD_X*y);     //redo for grid layout, possible include returning owning player for isGameOver()
}

int Board::isGameOver()
{
        //METHOD TO CHECK IF GAME END CONDITION MET AND WHETHER WIN? / LOSS?
    //if both have units remaining: return 0
    //if ai units all dead - > win : return 1
    //if player untis dead -> lose : return 2
    for (int i=0;i<MAX_GRID_DIMENSION;i++)
    {
        for(int j =0; j<MAX_GRID_DIMENSION; j++)
        {
            if(mapGrid[i][j].isUnit)
                return0;  ///placeholder, starbcks closing. priority tommorrow.
        }

}


bool Board::isValidMove(int px,int py)  //checks if space that player desires to move to is empty
{
        if( getPiece(px,py)==PLAYER_EMPTY)
        {
            return true;
        }
	return false;
}

bool BOARD::movePlayer(int px, int py)
{
	if (!isValidMove(px,py)) {return false;}
	setPiece(px,py,mNextPlayer);	
	emit signalMove(px,py,mNextPlayer);
	addMoveCounter(1);

	if (isGameOver())
	{
 		setRunning(false);
	}
 	else
	{	
		switchPlayer();
	 return true;
        }
    }

long Board::random(long max)
{
	double r = (double) rand()/(double) RAND_MAX;
	 return (long) (r&max);
}

}
