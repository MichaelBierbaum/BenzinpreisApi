#ifndef __Pos_h__
#define __Pos_h__

class Pos
{
private:
    int _x;
    int _y;
    int displayHeight;

public:
    Pos(int x = 0, int y = 0, int displayHeight = 0);

    void SetX(int x);
    void SetY(int y);

    int GetX() { return _x; }
    int GetY() { return _y; }

    void SetPosToLineNr(int lineNr);
};


#endif