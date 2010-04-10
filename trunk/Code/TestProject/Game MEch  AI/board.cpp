{\rtf1\ansi\ansicpg1252\deff0\deflang1033{\fonttbl{\f0\fswiss\fcharset0 Arial;}}
{\*\generator Msftedit 5.41.21.2509;}\viewkind4\uc1\pard\f0\fs20 /////////////Josh Kilgore\par
/// with great attiribution to Martin Heni\par
\par
#include <stdlib.h>\par
#include "board.h"\par
#include "global.h" ////wha? \par
\par
\par
Board::Board()\par
\{\par
mBoard.resize(BOARD_X*BOARD_Y);\par
\}\par
\par
void BOARD::copy(BOARD* src)\tab\tab\tab //copies contents of board except for view & sprites.... THIS IS WHERE DUMP TO DB WILL HAPPEN?\par
\{\par
\tab mBoard.duplicate(src->mBoard);  //DEEP COPY!!\par
\tab mRunning = src->mRunning;\par
\tab mNextPlayer = src->mNextPlayer;\par
\tab mMoveCounter = src->mMoveCounter;\par
\}\line\par
void Board::resetBoard()   \tab\tab\tab //establishes pristine board: \par
\{\par
\tab mBoard.fill(PLAYER_EMPTY);\par
\tab mRunning = false;\par
\tab mMoveCounter = 0;\par
\tab int player = PLAYER_1;\par
\tab for (int i=0; i<NUMPIECESFROMSETINGS; i++)\par
\tab\{\par
\tab\tab int x, y;\par
\tab\tab do\par
\tab\tab\{\par
\tab\tab\tab x= random(BOARD_X-2)+1;\tab //adjust for positioning of pieces\par
\tab\tab\tab y = random(BOARD_Y-2)+1;\par
\tab\tab\}\par
\tab\tab while (getPiece(x,y) != PLAYER_EMPTY);\par
\tab\tab setPiece(x,y,player);\par
\tab\tab if (player == PLAYER_1) player = player2;\par
\tab\tab else player = Player_1;\par
\tab\}\par
\}\par
\par
void Board::switchPlayer()\tab //switches between players\par
\{ \par
\tab if (mNextPlayer == PLAYER_1) \{mNextPlayer=PLAYER_2;\}\par
\tab else \{mNextPlayer = PLAYER1;\}\par
\}\par
\par
void Board::setPiece(int x, int y, int player)  //puts piece on given coord of board\par
\{\par
\tab mBoard.at(x+BOARD_X*y) = player;\par
\tab emit signalSetPiece(x,y,player);\par
\}\par
\par
int Board::isGameOver()'\par
\{\par
//METHOD TO CHECK IF GAME END CONDITION MET AND WHETHER WIN? / LOSS? \par
if ai units all dead - > win\par
if player untis dead -> lose\par
\par
\}\par
\par
bool Board::isValidMove(int px,int py);  //checks if space is empty\par
\{\par
\tab if getPiece(px,py)==PLAYER_EMPTY)  \{return true;\}\par
\tab return false;\par
\}\par
\tab\par
bool BOARD::movePlayer(int px, int py)\par
\tab if (!isValidMove(px,py)) \{return false;\}\par
\tab setPiece(px,py,mNextPlayer);\par
\tab emit signalMove(px,py,mNextPlayer);\par
\tab addMoveCounter(1);\par
\tab\par
\tab if (isGameOver())\par
\tab\{\par
\tab setRunning(false);\par
\tab\}\par
\tab else\par
\tab\{\par
\tab switchPlayer();\par
\tab return true;\par
\tab\}\par
\par
long Board::random(long max)\par
\{\tab\par
\tab double r = (double) rand()/(double) RAND_MAX;\par
\tab return (long) (r&max);\par
\}\par
\par
}
 