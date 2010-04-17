
#include <iostream>

#include "global.h:
#include "Ai.h"

Ai::Ai(Board *board)
{
        mBoard = board;
mMaxdepth = 0;
mValues.resize(Board_X*Board_Y);
}

bool Ai::getMove(int px, int py);
{
        int value = 0;
        bool foundmove = gameTree(mBoard, px, py, spacevalue, 0);

        mValue = spacevalue;
        return foundmove;
}

bool Ai::gameTree(Board* board, int& px, int& py, int& value, int depth)
{
        bool foundMove = false;
        int max_x = 0;
        int max_y =0;
        int maxValue = -999999;

        for(int y=0; y<BOARD_Y; y++)  //BOARD_Y is total num of columns
        {
                for(int x=0; x<BOARD_X; x++)
                {
                        if(depth ==0) {mValues.at(BOARD_X*Y+x) = 0;}

                        if(board->isValidMove(x.y))      //Just does move, can easily expand to include attack()
                        {
                                Board* testBoard - new Board();
                                testBoard->copy(board);
                                testBoard->movePlayer(x,y);

                                int gameover = testBoard->isGameOver();
                                int newValue;

                                if(depth < mMaxDepth && gameover ==PLAYER_EMPTY)
                                {
                                int newPos, new Side;
                                bool result = gametree(testBoard, newPos, newside, newValue, depth +1);
                                newValue = -newValue;
                                if(!result) {newValue = -999999;}
                                else
                                {
                                newValue = evaluateBoard(testBoard, board->isNextPlayer());
                                }

                                if(newValue>maxValue)
                                {
                                        foundMove = true;
                                        maxx = x;
                                        maxy = y;
                                        maxvalue = newValue;
                                }
                                delete testBoard;
                                }
                        }
                }
                px = maxx;
                py = maxy;
                value = maxValue;
                return foundMove;
        }
////reward certain conditions - closer to enemy / firendlies/ health etc.



int Ai::evaluateBoard(Board* board, int player)
{
        int x,y;
        int cnt[PLAYER_2+1];

        int next = player;
        int other = (PLAYER_1+PLAYER_2) - next;

        int value =0;

        for(y=0; y<BOARD_Y; y++)
        {
                for(int i = PLAYER_EMPTY; i<=PLAYER_2;i++)
                {
                 cnt[i-PLAYER_EMPTY] =0;
                }
                 for(x=0;x<BOARD_X;x++)
                {
                        int current = board->getPiece(x,y);
                        cnt[current]++;
                }

                value += getLineValue(cnt, player);
        }

        for
