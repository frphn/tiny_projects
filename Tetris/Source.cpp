#include <iostream>
using namespace std;


#include <Windows.h>

wstring tetromino[7]; //storing blocks as a string , there are 7 of them

//defines playing field
//create a playing field
//defined by fieldwidth, fieldheight
//store elements of field as array of unsignedchars

int nFieldWidth = 12;//cells counted from a older version
int nFieldHeight = 18;
unsigned char *pField = nullptr; //Note: not statically allocated, rather dynamically


//windows default
//

int nScreenWidth = 80;  //console Screen size X (columns)
int nScreenHeight = 30; //console Screen size Y (rows)


//Author makes case; reason for using unsigned char is he wants 0 to represent empty space
// 1 to reprepresent a part of the shape
//2 to rep a diff shape
//including boundary wall
//
//
//note: All of our map info is stored in one array
//px = x, py = y, r = degrees of rotation; 0,1,2,3 _____ 0,90,180,270

//assets and a way to access them, however we need playing field asset

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

//Set up condition to ensure piece fits

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) //(id of tetromino,curr rotation,location(top, left cell),)
{

    //to iterate across tetromino
    for (int px = 0; px<4; px++)
       for (int py = 0; py<4; py++) 
        {
            //get index of array into tetromino
            int pi = Rotate(px, py, nRotation);

            //Get index into field
            int fi = (nPosY + py) *nFieldWidth + (nPosX + px);


            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if(nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                        return false;//fail on first hit

                }
            }
             
        }
    
    //always set to return tru by default
    return true;
}


int main()
{
    //Create assets
    //4 elements wide, 4 lines deep
    //creating a vert tetris
    //fullstop symbol to create empty space
    //capital X to represent a part of the shape
    //appending them, we create a string, but visually see what shape is
    //create other shapes
    //7 common shapes used in tetris
    //
    //not using multidimensional arrays
    //using 2d arrays
    //
    //
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

    //stroing all map info in one array 
    //initialize array for playing field
    pField= new unsigned char[nFieldWidth*nFieldHeight];
    for (int x = 0; x <nFieldWidth; x++) //Board Boundary
        for(int y = 0; y <nFieldHeight; y++)
            pField[y*nFieldWidth+x] = (x == 0 || x == nFieldWidth -1 || y == nFieldHeight-1) ? 9 : 0;  
            //left, right, bottom
            //9 is the border

    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];// defaults normally included with Windows cmmnd prompt
    for (int i = 0; i < nScreenWidth*nScreenHeight;i++) screen[i] = L' ';// create array of wchars for screenwidth, screenheight, fills with blanks   
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);//grab handle to console buffer
    SetConsoleActiveScreenBuffer(hConsole); //instead of cout, use separate command to draw to buffer
    DWORD dwBytesWritten = 0;

    // Game Logic Stuff//testing routine
    bool bGameOver = false;//Flag Game over

    int nCurrentPiece = 0;
    int nCurrentRotation =0;
    int nCurrentX = nFieldWidth/2;
    int nCurrentY = 0;

    bool bKey[4];
    bool bRotateHold = false;
    
    int nSpeed = 20;
    int nSpeedCounter = 0;
    bool bForceDown = false;
    int nPieceCount = 0;
    int nScore = 0;

    vector<int> vLines ;



    while (!bGameOver)
    { 


        //GAME TIMING========================================
        this_thread::sleep_for(50ms); // game tick 
        nSpeedCounter++;
        bForceDown = (nSpeedCounter == nSpeed);
        
        //INPUT==============================================//NOTevent based
        //sync key state
        for (int k =0; k <4; k++)
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z[k]"))) != 0;


        //GAME LOGIC=========================================//shapes falling //collision detection //scoring
     

        nCurrentX += (bKey[0] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
        nCurrentX -= (bKey[1] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
        nCurrentX += (bKey[2] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

        nCurrentRotation += (bKey[3] && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;

        if (bKey[3])
        {
            nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
            bRotateHold = true;
        }   
        else
        {
            bRotateHold = false;
        }
        
        if(bForceDown)
        {
            if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
                nCurrentY++; //It can, so do it!
            else
            {
                // Lock the current piece into the field
                for (int px = 0; px <4; px++)
                    for (int py = 0; py <4; py++)
                        if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                            pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
                
                
                nPieceCount++;
                if (nPieceCount % == 0)
                    if (nSpeed >= 10) nSpeed--;


                
                //Check for full horizontal lines
                for (int py = 0; py < 4; py++)
                    if (nCurrentY + py < nFieldWidth - 1)
                    {
                        bool bLine = true;
                        for (int px = 1; px < nFieldWidth - 1; px++)
                            bLine &= (pField[nCurrentY + py * nFieldWidth + px]) != 0;

                        if (bLine)
                        {
                            // Remove Line, set to =
                        
                            for (int px = 1; px < nFieldWidth - 1; px++)
                                pField[(nCurrentY + py) * nFieldWidth + px] = 8; 


                            vLines.push_back(nCurrentY + py);    
                        }
                    
                    }

                nScore += 25;
                if (!vLines.empty()) nScore += (1 << vLines.size())) * 100;




                //Choose next piece
                nCurrentX = nFieldWidth / 2;
                nCurrentY = 0;
                nCurrentRotation = 0;
                nCurrentPiece = rand() % 7;



                // if piece down not fit
                bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
            }


            nSpeedCounter = 0;
            
        }
        
        //RENDER OUTPUT=======================================


        // Draw Field// field draws in whole board, boundaries, empty spaces, tetris pieces as well
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y+2)*nScreenWidth + (x+2)] = L" ABCDEFG=#" [pField[y*nFieldWidth+x]];
                //offset field by 2 b/c we don't want to draw exactly in top lefthand corner
                //setting output based on characters in string
                //= 8, for line
                //# for border
                //" " empty space
                //"ABCDEFG" for terimino shapes
                // take layout for array, field array position and put into string array to display on screen
                //
                //author at this point shows deign layout of bordr
        

        // Draw Current Piece
        for (int px = 0; px <4; px++)
            for (int py = 0; py <4; py++)
                if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                    screen[(nCurrentY + py + 2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;


        // Draw Score
        swprintf_s(&screen[2*nScreenWidth + nFieldHeight + 6], 16, L"SCORE: %8d", nScore);


        if (!vLines.empty())
        {
            //Display Frame (to draw lines)
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0,0}, &dwBytesWritten)
            this_thread::sleep_for(400ms); //Delay a bit

            for (auto &v : vLines)
                for(int px = 1; px < nFieldWidth - 1; px++)
                {
                    for (int py = v; py >0; py--)
                        pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
                    pField[px] = 0;
                }

            vLines.clear();


        }


        //Display Frame

        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0,0}, &dwBytesWritten);//separate command to draw to buffer
    }

    // Game Over
    CloseHandle(hConsole);
    cout << "Game Over!! Score:" << nScore << endl;
    system("pause");
    
    return 0;
}