#include <iostream>
using namespace std;


wstring tetromino[7];

//create a playing field
//defined by fieldwidth, fieldheight
//store elements of field as array of unsignedchars

int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr; //Note: not statically allocated, rather dynamically


//Author makes case; reason for using unsigned char is he wants 0 to represent empty space
// 1 to reprepresent a part of the shape
//2 to rep a diff shape
//including boundary wall
//
//
//note: All of our map info is stored in one array
//px = x, py = y, r = degrees of rotation

int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
        case 0: return py * 4 + px;         // 0 degrees
        case 1: return 12 + py  - (px*4);   // 90 degrees
        case 2: return 15 - (py*4) - px;    // 180 degrees
        case 3: return 3 - py +(px*4);      // 270 degrees
    }
    return 0; //returns appropriate index given the equations for rotations
}


int main()
{
    // Create assets

    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");


    //initialize array for playing field
    pField= new unsigned char[nFieldWidth*nFieldHeight];
    for (int x = 0; x <nFieldWidth; x++) //Board Boundary
        for(int y = 0; y <nFieldHeight; y++)
            pField[y*nFieldWidth+x] = (x == 0 || x == nFieldWidth -1 || y == nFieldHeight-1) ? 9 : 0;  


    return 0;
}