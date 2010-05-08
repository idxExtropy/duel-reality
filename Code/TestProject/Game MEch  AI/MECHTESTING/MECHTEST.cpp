#include "stdio.h"
#include "iostream"
#include "mechanics.h"
#include "globalls.h"

using namespace std;


//void move(unit *UP, int x, int y);
bool isValidMove(int a, int b, int c, int d);

int main()
{
    mechanics mymech;
    unit *UP;
    unit bob;
    bob.h=3;
    bob.v=3;
    bob.ap=10;
    bob.mr=3;
    cout<<bob.h<<bob.v<<bob.ap<<'\n';
    UP = &bob;
    mymech.move(UP,4,4);
    cout<<bob.h<<bob.v<<bob.ap;
    return 0;
}



