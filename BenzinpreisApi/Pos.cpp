#include "Pos.h"


//displayHeight = u8g2.getDisplayHeight()
Pos::Pos(int x, int y, int displayHeight)
{
    this->displayHeight = displayHeight;
    SetX(x);
    SetY(y);
}

void Pos::SetX(int x)
{
    if (x < 0 || x > displayHeight)
        return;

    _x = x;
}

void Pos::SetY(int y)
{
    if (y < 0 || y > displayHeight)
        return;

    _y = y;
}

void Pos::SetPosToLineNr(int lineNr)
{
    SetX(0);
    SetY(10 + 10 * lineNr);
}
