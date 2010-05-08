#include "mechanics.h"

mechanics::mechanics(QObject *parent) :
    QObject(parent)
{
}
void mechanics::move(unit *UP, int x, int y)
{
    if(isValidMove(UP->ap, x,y,UP->mr))
    {
        UP->h=x;
        UP->v=y;
        UP->ap-=UP->mr;
    }
}

bool mechanics::isValidMove(int a, int b, int c, int d)
{
    if(a>=d)
    {
        return true;
    }
    return false;
}
