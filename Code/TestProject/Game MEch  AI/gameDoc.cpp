
#include <stdlib.h>
#include <qtimer.h>

#include <gameDoc.h>
//others

#define INPUT_MOUSE 1
#define INPUT_AI 2

gameDoc::gameDoc(QWidget* parent)		//constructor
	:QObject(parent)
{
	mPlayerDevice[0] = INPUT_MOUSE;
	mPlayerDevice[1] = INPUT_AI;
	mLevel = 0;				// will get loaded with selected or iterated

	mTimer = new QTimer();
	connect(mTimer, SIGNAL (timeout()),	//connect timeer to AI movement
	this, SLOT(AiMove);
}

gameDoc::~gameDoc()
{
	delete mBoard;
	delete mTimer;
}

void gameDoc::initDocument(gameView* view)
{
mBoard = new board();
endGame();

connect(this, SIGNAL(signalGameOver()),
	view, SLOT(gameOver()));

connect(mBoard, SIGNAL(signalsetPiece(int, int, int)),
	view, SLOT(setUnit(int, int, int)));

connect(mBoard, SIGNAL(signalMove(int int int)),
	view, SLOT(markMove(int, int, int)));

connect(this, SIGNAL(signalAIInfo(int, QMemArray<int>)),
	view, SLOT(int, QMemeArray<int>)));
}

void gameDoc::startGame();
{
	endGame();		//clear old
	
	mBoard->setRunning(true);
	mBoard->setNextPlayer(Player1);		//Player 1 always starts, else set to random?, possuble replace w/ player ID
	emit signalNewMove();
}

void gameDoc::endGame()			//removes all pieces form board
{
	mTimer->stop();
	mBoard->resetBoard();
}


bool gmaeDoc::isRunning()
{
	return mBoard->isRunning();

}


int gameDoc::nextPlayer();
{
	return mBoard->nextPlayer();
}

bool gameDoc::isMouseInput()
{	
	if(!isRunning()) {return false;}
	if(mPlayerDevice[nextPlayer()-PLAYER_1]==INPUT_MOUSE){return true;}
	return false;
}

bool gameDoc::isAiInput()
{
	if(!isRunning()) {return false;}
	if(mPlayerDevice[nextPlayer()-PLAYER_1]==INPUT_AI){return true;}
	return false;
}

bool gameDoc::movePlayer(int px, int py);			//moves player, if move isn't possible - returns false
{
	emit signalNewMove();
	bool result = mBoard->movePlayer(px,py);
	if (mBoard->isGameOver()) {emit signalGameOver();}

	if(isAIInput()&&isRunning())				//checks if AI  and game are still running
	{
	mTimer->start(2*1000, true);				//if yes starts move
	}
	
	emit signalNewMove();
	return result;
	}	

bool gameDoc::isValidMove(int px,int py)		//checks validity of move
	{
	return mBoard->isValidMove(px,py);
	}

void gameDoc::startAiMove()
	{
	int px,py;
	myAI ai(mBoard);			//creates AI!!!! :) LOL OMG 1111 DPS LFG 25 VOA 5600GS!!!
	ai.setLevel(mLevel);
	bool result = ai.getMove (px,py);
	if (result) {movePlayer(px,py);}
	int value = ai.value();			//determines value of move spot ie. is it a good move?
	QMemArray<int> values = ai.moveValues();
	emit signalAIInfo(value, values);

	if (mBoard->isGameOver() emit SignalGameOver();
	}
















