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


class Board:public QObject   ///board func!!
{
	Q_Object
	
	public: 
		Board();
		void copy(Board* board); 		
		void resetBoard();
		bool isRunning() {return mRunning;}
		void setRunning(bool run) {mRunning = run;} // sets to game run or not. 
		int isNextPlayer() {return mNextPlayer; } //whose turn
		void setnextPlayer(int player) {mNextPlayer = player;} //sets next player
		bool movePlayer (int px, int py);  //moves player // returns T if valid
		int isGameOver(); //checks game status
		bool isValidMove(int px, int py);  //checks valid moves
                void setPiece(int x, int y, int player); //***SETS PIECE AT COORDINATE AND PLAYER ASSIGNED TO!!!!!//
		int getPiece(int x, int y); // 
	signals: 

		void signalSetPiece(int x,int y,int player);
		void signalMove (intx, int y, int player);

	protected:
		void switchPlayer();  //switches between players
                void addMoveCounter(int amount) {mMoveCounter+=amount;}
		long random(long max);  //large random #

	private:
		QmemArray<char> mBoard;
		bool mRunning; 
		int mNextPlayer;
		int mMoveCounter;
};
#endif
	
	


		
