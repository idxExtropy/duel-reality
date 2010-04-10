/////Josh Kilgore
///// Board Functions.h

//Stores current gameboard, next player.  Checks possible AI moves, 
//game over, and performs moves b/w rows and columns


#ifndef BOARDFUNC_H
#define BOARDFUNC_H

#include <qstring.h>
#include <qmemarray.h>
#include <qcanvas.h>
#include <qobject.h>

class Board.h : public Qobject   ///board func!!
{
	Q_Object
	
	public: 
		Board();
		void resetBoard();
		void copy(Board* board); //future interface to DB
		bool isRunning() {return mRunning;}
		void setRunning(bool run) {mRunning = run;} // sets to game run or not. 
		int isNextPlayer() {return mNextPlayer; } //whose turn
		void setnext Player(int player) {mNextPlayer = player;} //sets next player
		bool movePlayer (int px, int py);  //moves player // returns T if valid
		int isGameOver(); //checks game status
		bool isValid Move(int px, int py);  //checks valid moves
		void setPiece(int x, int y, int player) //***SETS PIECE AT COORDINATE AND PLAYER ASSIGNED TO!!!!!//
		int getPiece(int x, int y); // gets piece - tie to mouse click
	signals: 

		void signalSetPiece(int x,int y,int player);
		void signalMove (intx, int y, int player);

	protected:
		void switchPlayer();  //switches between players
		void addMove Counter(int amount) {mMoveCounter+=amount;}
//delete later - can i turn into action points ??
		long random(long max);  //large random #

	private:
		QmemArray<char> mBoard;
		bool mRunning; 
		int mNextPlayert;
		int mMoveCounter;
};
#endif
	
	


		
