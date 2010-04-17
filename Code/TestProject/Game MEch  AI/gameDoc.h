//////blah*JOSH KILGORE*/
//BASIC AI DOCUMENT gameDoc.h
//V 0.1


////Basic version of a gamedoc class which will run much of the nuts and bolts of the game
//////including: initializing game object, setting level, starting/ending game, testing for
/////valid moves, wnding turn, inputs, AI movement 


#ifndef GAMEDOC_H
#define GAMEDOC_H

#include <qobject.h>
#include <qwidget.h>
#include <qstring.h>
#include <qtimer.h>
#include <qmemarray.h>
#include <board.h>  		//Local map

class gameView;

class gameDoc : public QObject
{
	Q_OBJECT

public:
	gameDoc(QWidget* parent);	//constructor 
	~gameDoc	//Destructor;
	void initDocument(gameView* view); 	//initialize doc obj - makes connections
	void setLevel(int Level) {mLevel = level;}	//sets game level
	void startBattle();			//initializr board, pieces, player
	void endBattle();			//removes pieces from board
	bool isRunning();			// is game running?
	bool isValidMove(int px, int py);	//determines if a move is valid
	int  nextPlayer();			// turn
	bool isMouseInput();			// I/O method
	bool isAIInput();			// is player AI?
	bool movePlayer(int px int py);		// moves player unit to x/y, false if not a valid move, true if valid
	
public slots: 
	void startAiMove();			//moves AI unit

signals:
	void signalBattleOver();	//game over
	void signalNewMove();	
	void signalAIInfo(int,QmemArray<int>);  /demo

private: 
	Board* mBoard;		//board(RENAME?)
	int PlayerDevice[2]	// player input methods
	int mLevel;		//recursion level
	Qtimer* mTimer;		//AI timer
};

#endif


