#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

using namespace std;


/* Co ordinate system variables */

float OrthoHeight;
float OrthoWidth;
float WindowHeight;
float WindowWidth;
float BlockDistance;

float MoveBeginX;
float MoveBeginY;


/* Board element definiions */

//Co-Ordinate system in the Matrix
#define XCoordinate 0
#define YCoordinate 1
#define Valid       2
#define Background  2

//Colouring of each element
#define Color       2
#define ColorBlack  0
#define ColorWhite  1

//Give Unique ordering to each of the elements
#define RookLeft    0
#define KnightLeft  1
#define BishopLeft  2
#define Queen       3
#define King        4
#define BishopRight 5
#define KnightRight 6
#define RookRight   7

// Definitions for other elements
#define PawnIndex   8
#define PieceType   8
#define Properties  3


/* Board movement variables */

int ChosenPiece;
int ChosenColor;
int Turn;


/* Texture map variables */

GLuint BoardTexture;
GLuint PawnTextures[PawnIndex][Color][Background];
GLuint OtherTextures[PieceType][Color][Background];
GLuint MyTexture;
FILE* Pointer;
char* Data;
char* BoardData;

void InitializeCoordinates();

/* Class Definition */
class BoardPieces {
public:

    /* Class members */
    int Pawns[PawnIndex][Properties][Color];
    int OtherPieces[PieceType][Properties][Color];

    char OtherPiecesPath[PieceType][Color][Background][500];
    char PawnPath[PawnIndex][Color][Background][500];

    BoardPieces() {
        InitializeCoordinates();
        for(int Count = 0; Count<8; Count++) {
            strcpy(PawnPath[Count][ColorWhite][ColorWhite],"img/White Pawn White.raw");
            strcpy(PawnPath[Count][ColorBlack][ColorWhite],"img/Black Pawn White.raw");
            strcpy(PawnPath[Count][ColorWhite][ColorBlack],"img/White Pawn Black.raw");
            strcpy(PawnPath[Count][ColorBlack][ColorBlack],"img/Black Pawn Black.raw");
        }

        strcpy(OtherPiecesPath[RookLeft][ColorWhite][ColorWhite],"img/White Rook White.raw");
        strcpy(OtherPiecesPath[RookRight][ColorWhite][ColorWhite],"img/White Rook White.raw");
        strcpy(OtherPiecesPath[KnightLeft][ColorWhite][ColorWhite],"img/White Knight White.raw");
        strcpy(OtherPiecesPath[KnightRight][ColorWhite][ColorWhite],"img/White Knight White.raw");
        strcpy(OtherPiecesPath[BishopLeft][ColorWhite][ColorWhite],"img/White Bishop White.raw");
        strcpy(OtherPiecesPath[BishopRight][ColorWhite][ColorWhite],"img/White Bishop White.raw");
        strcpy(OtherPiecesPath[Queen][ColorWhite][ColorWhite],"img/White Queen White.raw");
        strcpy(OtherPiecesPath[King][ColorWhite][ColorWhite],"img/White King White.raw");

        strcpy(OtherPiecesPath[RookLeft][ColorWhite][ColorBlack],"img/White Rook Black.raw");
        strcpy(OtherPiecesPath[RookRight][ColorWhite][ColorBlack],"img/White Rook Black.raw");
        strcpy(OtherPiecesPath[KnightLeft][ColorWhite][ColorBlack],"img/White Knight Black.raw");
        strcpy(OtherPiecesPath[KnightRight][ColorWhite][ColorBlack],"img/White Knight Black.raw");
        strcpy(OtherPiecesPath[BishopLeft][ColorWhite][ColorBlack],"img/White Bishop Black.raw");
        strcpy(OtherPiecesPath[BishopRight][ColorWhite][ColorBlack],"img/White Bishop Black.raw");
        strcpy(OtherPiecesPath[Queen][ColorWhite][ColorBlack],"img/White Queen Black.raw");
        strcpy(OtherPiecesPath[King][ColorWhite][ColorBlack],"img/White King Black.raw");

        strcpy(OtherPiecesPath[RookLeft][ColorBlack][ColorBlack],"img/Black Rook Black.raw");
        strcpy(OtherPiecesPath[RookRight][ColorBlack][ColorBlack],"img/Black Rook Black.raw");
        strcpy(OtherPiecesPath[KnightLeft][ColorBlack][ColorBlack],"img/Black Knight Black.raw");
        strcpy(OtherPiecesPath[KnightRight][ColorBlack][ColorBlack],"img/Black Knight Black.raw");
        strcpy(OtherPiecesPath[BishopLeft][ColorBlack][ColorBlack],"img/Black Bishop Black.raw");
        strcpy(OtherPiecesPath[BishopRight][ColorBlack][ColorBlack],"img/Black Bishop Black.raw");
        strcpy(OtherPiecesPath[Queen][ColorBlack][ColorBlack],"img/Black Queen Black.raw");
        strcpy(OtherPiecesPath[King][ColorBlack][ColorBlack],"img/Black King Black.raw");

        strcpy(OtherPiecesPath[RookLeft][ColorBlack][ColorWhite],"img/Black Rook White.raw");
        strcpy(OtherPiecesPath[RookRight][ColorBlack][ColorWhite],"img/Black Rook White.raw");
        strcpy(OtherPiecesPath[KnightLeft][ColorBlack][ColorWhite],"img/Black Knight White.raw");
        strcpy(OtherPiecesPath[KnightRight][ColorBlack][ColorWhite],"img/Black Knight White.raw");
        strcpy(OtherPiecesPath[BishopLeft][ColorBlack][ColorWhite],"img/Black Bishop White.raw");
        strcpy(OtherPiecesPath[BishopRight][ColorBlack][ColorWhite],"img/Black Bishop White.raw");
        strcpy(OtherPiecesPath[Queen][ColorBlack][ColorWhite],"img/Black Queen White.raw");
        strcpy(OtherPiecesPath[King][ColorBlack][ColorWhite],"img/Black King White.raw");

    }

}Piece;

struct BoardStatus {
    /* Board content member variables */
    int PieceColor[8][8];
    int CurrentPiece[8][8];
}BoardStatus;


void InitializeCoordinates() {
    /* Initialization of X and Y co ordinates for all the board pieces */
    for(int Count = 0; Count<8; Count++) {

        Piece.Pawns[Count][Valid][ColorBlack] = 1;
        Piece.Pawns[Count][Valid][ColorWhite] = 1;
        Piece.OtherPieces[Count][Valid][ColorBlack] = 1;
        Piece.OtherPieces[Count][Valid][ColorWhite] = 1;

        Piece.Pawns[Count][XCoordinate][ColorBlack] = -400 + Count * 100;
        Piece.Pawns[Count][YCoordinate][ColorBlack] = 200;
        Piece.Pawns[Count][XCoordinate][ColorWhite] = -400 + Count * 100;
        Piece.Pawns[Count][YCoordinate][ColorWhite] = -300;

        Piece.OtherPieces[Count][XCoordinate][ColorBlack] = -400 + Count * 100;
        Piece.OtherPieces[Count][YCoordinate][ColorBlack] = 300;
        Piece.OtherPieces[Count][XCoordinate][ColorWhite] = -400 + Count * 100;
        Piece.OtherPieces[Count][YCoordinate][ColorWhite] = -400;
      }

}

void InitializeBoardMatrix() {
    /* Initialize first player as White */
    Turn = ColorWhite;

    int Row;
    int Column;

    /* Board content member initializations */
    for(Row = 0; Row < 8; Row++)
        for(Column = 0; Column < 8; Column++) {
            if(Row == 0) {
                BoardStatus.CurrentPiece[Row][Column] = Column + 8;
                BoardStatus.PieceColor[Row][Column] = ColorBlack;
            }

            else if(Row == 1) {
                BoardStatus.CurrentPiece[Row][Column] = Column;
                BoardStatus.PieceColor[Row][Column] = ColorBlack;
            }

            else if(Row == 6) {
                BoardStatus.CurrentPiece[Row][Column] = Column;
                BoardStatus.PieceColor[Row][Column] = ColorWhite;
            }

            else if(Row == 7) {
                BoardStatus.CurrentPiece[Row][Column] = Column + 8;
                BoardStatus.PieceColor[Row][Column] = ColorWhite;
            }

            else {
                BoardStatus.CurrentPiece[Row][Column] = -1;
                BoardStatus.PieceColor[Row][Column] = -1;
            }
        }
}

void GenerateTextures() {
    /* Load texture for the board */
    Pointer = fopen("img/Board.raw", "rb");
    fread(BoardData, 512*512*3, 1, Pointer);

    /* Generate textures and set the environment for each texture */
    glGenTextures( 1, &BoardTexture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glBindTexture( GL_TEXTURE_2D, BoardTexture );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, BoardData);

    for(int Count = 0 ; Count < 8 ; Count++ )
        for(int ForegroundColor = 0 ; ForegroundColor < 2 ; ForegroundColor++ )
            for(int BackgroundColor = 0; BackgroundColor < 2; BackgroundColor++ ) {

                Pointer = fopen(Piece.PawnPath[Count][ForegroundColor][BackgroundColor], "rb");
                fread(Data, 256*256*3, 1, Pointer);

                glGenTextures( 1, &PawnTextures[Count][ForegroundColor][BackgroundColor] );
                glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
                glBindTexture( GL_TEXTURE_2D, PawnTextures[Count][ForegroundColor][BackgroundColor]);
                glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR );
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);


                Pointer = fopen(Piece.OtherPiecesPath[Count][ForegroundColor][BackgroundColor], "rb");
                fread(Data, 256*256*3, 1, Pointer);
                fclose(Pointer);

                glGenTextures( 1, &OtherTextures[Count][ForegroundColor][BackgroundColor] );
                glBindTexture( GL_TEXTURE_2D, OtherTextures[Count][ForegroundColor][BackgroundColor] );
                glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
                glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR );
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
            }
}

void DrawBoard() {
    /* Bind texture for the board to a polygon specified by the four vertices */
    glBindTexture( GL_TEXTURE_2D, BoardTexture );
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0,1.0); glVertex2d(-400.0,-400.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-400+800.0,-400.0);
    glTexCoord2d(0.0,0.0); glVertex2d(-400+800.0,-400+800.0);
    glTexCoord2d(1.0,0.0); glVertex2d(-400,-400+800.0);
    glEnd();

}

void DrawPiece(int Count, int ForegroundColor, int BackgroundColor, float XBegin, float YBegin) {

    int XOffset = 100;
    int YOffset = 100;

    /* Bind texture for the induvidual pieces to a polygon specified by the four vertices */
    if(Count < 8)
        glBindTexture( GL_TEXTURE_2D, PawnTextures[Count][ForegroundColor][BackgroundColor] );
    else
        glBindTexture( GL_TEXTURE_2D, OtherTextures[Count-8][ForegroundColor][BackgroundColor] );

    glColor3f(1, 1, 1);
    glBegin (GL_QUADS);
    glTexCoord2d(1.0,1.0); glVertex2d(XBegin, YBegin );
    glTexCoord2d(0.0,1.0); glVertex2d(XBegin + XOffset, YBegin );
    glTexCoord2d(0.0,0.0); glVertex2d(XBegin + XOffset, YBegin + YOffset);
    glTexCoord2d(1.0,0.0); glVertex2d(XBegin, YBegin + YOffset );
    glEnd();

}

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_TEXTURE_2D );
    /* Enable textures and clear the window */
    DrawBoard();
    /* Draw the board on the screen */

    for(int Count = 0 ; Count < 8 ; Count++ ) {
        if((Piece.OtherPieces[Count][XCoordinate][ColorWhite] + Piece.OtherPieces[Count][YCoordinate][ColorWhite]) % 200 == ColorBlack) {
            if(Piece.OtherPieces[Count][Valid][ColorWhite] == 1)
                DrawPiece(Count+8, ColorWhite, ColorBlack, Piece.OtherPieces[Count][XCoordinate][ColorWhite], Piece.OtherPieces[Count][YCoordinate][ColorWhite]);
        }
        else if(Piece.OtherPieces[Count][Valid][ColorWhite] == 1)
            DrawPiece(Count+8, ColorWhite, ColorWhite, Piece.OtherPieces[Count][XCoordinate][ColorWhite], Piece.OtherPieces[Count][YCoordinate][ColorWhite]);


        if((Piece.OtherPieces[Count][XCoordinate][ColorBlack] + Piece.OtherPieces[Count][YCoordinate][ColorBlack]) % 200 == ColorBlack) {
            if(Piece.OtherPieces[Count][Valid][ColorBlack] == 1)
                DrawPiece(Count+8, ColorBlack, ColorBlack, Piece.OtherPieces[Count][XCoordinate][ColorBlack], Piece.OtherPieces[Count][YCoordinate][ColorBlack]);
        }
        else if(Piece.OtherPieces[Count][Valid][ColorBlack] == 1)
            DrawPiece(Count+8,ColorBlack,ColorWhite, Piece.OtherPieces[Count][XCoordinate][ColorBlack], Piece.OtherPieces[Count][YCoordinate][ColorBlack]);


        if((Piece.Pawns[Count][XCoordinate][ColorWhite] + Piece.Pawns[Count][YCoordinate][ColorWhite]) % 200 == ColorBlack) {
            if(Piece.Pawns[Count][Valid][ColorWhite] == 1)
                DrawPiece(Count,ColorWhite,ColorBlack, Piece.Pawns[Count][XCoordinate][ColorWhite], Piece.Pawns[Count][YCoordinate][ColorWhite]);
        }
        else if(Piece.Pawns[Count][Valid][ColorWhite] == 1)
            DrawPiece(Count,ColorWhite,ColorWhite, Piece.Pawns[Count][XCoordinate][ColorWhite], Piece.Pawns[Count][YCoordinate][ColorWhite]);


        if((Piece.Pawns[Count][XCoordinate][ColorBlack] + Piece.Pawns[Count][YCoordinate][ColorBlack]) % 200 == ColorBlack) {
            if(Piece.Pawns[Count][Valid][ColorBlack] == 1)
                DrawPiece(Count,ColorBlack,ColorBlack, Piece.Pawns[Count][XCoordinate][ColorBlack], Piece.Pawns[Count][YCoordinate][ColorBlack]);
        }
        else if(Piece.Pawns[Count][Valid][ColorBlack] == 1)
            DrawPiece(Count,ColorBlack,ColorWhite, Piece.Pawns[Count][XCoordinate][ColorBlack], Piece.Pawns[Count][YCoordinate][ColorBlack]);
    }

    /* Draw all pieces on the board */
    glFlush();

}

void ResetGame() {
    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Reinitialize board members and X and Y coordinates for the pieces */
    InitializeBoardMatrix();
    BoardPieces();
    MyDisplay();
}

void MyReshape(int Width, int Height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(Width<=Height) {
        glOrtho(-500, 500, -500 * (double)Height/Width, 500 * (double)Height/Width,-100,100);
        OrthoWidth = 1000;
        OrthoHeight = 1000 * (double)Height/Width;
    }
    else {
        glOrtho(-500* (double)Width/Height, 500* (double)Width/Height, -500, 500,-100,100);
        OrthoWidth = 1000 * (double)Width/Height;
        OrthoHeight = 1000;
    }
    glMatrixMode(GL_MODELVIEW);
    /* Set the ortho coordinates based on the current window height and width */

    WindowWidth = Width;
    WindowHeight = Height;
    BlockDistance = 100 * Height/OrthoHeight;
    glViewport(0, 0, Width, Height);
    glutPostRedisplay();
    /* Redisplay re-mapped window */

}

void WindowInitializations() {
    glClearColor(0,0,0,1);
    /* Allocate memory for textures */
    Data = (char*) malloc (256*256*3);
    BoardData = (char*) malloc (512*512*3);
}

/* Map board X and Y coordinates to the corresponding Row and Column */
int MapRow(float CoordinateY) {
    return (abs(300-(int)CoordinateY))/100 ;
}

int MapColumn(float CoordinateX) {
    return (abs(-400-(int)CoordinateX))/100;
}

void FindPiece(int X, int Y) {
    /* Determine chosen piece based on the mouse click coordinates */
    ChosenPiece = BoardStatus.CurrentPiece[MapRow(Y)][MapColumn(X)];
    ChosenColor = BoardStatus.PieceColor[MapRow(Y)][MapColumn(X)];
}

int MoveValid(float DestinationX, float DestinationY) {
    int Temp;

    /* If the piece is moving out of the board */
    if( DestinationX < -400 || DestinationX > 300 || DestinationY < -400 || DestinationY > 300 )
        return 0;

    /* If attacking a piece of the same color */
    if( BoardStatus.PieceColor[MapRow(DestinationY)][MapColumn(DestinationX)] == BoardStatus.PieceColor[MapRow(MoveBeginY)][MapColumn(MoveBeginX)] )
        return 0;

    /* Check move validity for pawns of color white */
    if( ChosenPiece < 8 && ChosenColor == ColorWhite ) {
        if( (MapRow(DestinationY) == MapRow(MoveBeginY) -1) && DestinationX == MoveBeginX && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] == -1 )
            return 1;

        else if( (MapRow(DestinationY) == MapRow(MoveBeginY) -2) && DestinationX == MoveBeginX && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] == -1
                && MapRow(MoveBeginY) == 6 )
            return 1;

        else if ((MapRow(DestinationY) == MapRow(MoveBeginY) -1) && abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) == 1
                 && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] != -1 )
            return 1;

        else return 0;

    }

    /* Check move validity for pawns of color black */
    if( ChosenPiece < 8 && ChosenColor == ColorBlack ) {
        if( (MapRow(DestinationY) == MapRow(MoveBeginY) +1) && DestinationX == MoveBeginX && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] == -1 )
            return 1;

        else if( (MapRow(DestinationY) == MapRow(MoveBeginY) +2) && DestinationX == MoveBeginX && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] == -1
                && MapRow(MoveBeginY) == 1 )
            return 1;

        else if ((MapRow(DestinationY) == MapRow(MoveBeginY) +1) && abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) == 1
                 && BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] != -1 )
            return 1;

        else return 0;

    }

    /* Move validity for a Rook */
    if( ChosenPiece == RookLeft + 8 || ChosenPiece == RookRight + 8 ) {
        if( (MapRow(DestinationY) - MapRow(MoveBeginY)) * (MapColumn(DestinationX) - MapColumn(MoveBeginX)) != 0)
            return 0;

        else if( MapRow(DestinationY) - MapRow(MoveBeginY) == 0 ) {
            if( MapColumn(DestinationX) - MapColumn(MoveBeginX) > 0 ) {
                for(Temp = MapColumn(MoveBeginX) + 1; Temp < MapColumn(DestinationX); Temp++ )
                    if(BoardStatus.CurrentPiece[MapRow(MoveBeginY)][Temp] != -1)
                        return 0;

            }

            else{    
            	for(Temp = MapColumn(MoveBeginX) - 1; Temp > MapColumn(DestinationX); Temp-- )
                	if(BoardStatus.CurrentPiece[MapRow(MoveBeginY)][Temp] != -1)
                    	return 0;
            }
        }

        else if( MapColumn(DestinationX) - MapColumn(MoveBeginX) == 0 ) {
            if( MapRow(DestinationY) - MapRow(MoveBeginY) > 0 ) {
                for(Temp = MapRow(MoveBeginY) + 1; Temp < MapRow(DestinationY); Temp++ )
                    if(BoardStatus.CurrentPiece[Temp][MapColumn(MoveBeginX)] != -1)
                        return 0;
            }

            else {
                for(Temp = MapRow(MoveBeginY) -1 ; Temp > MapRow(DestinationY); Temp-- ) {
                    if(BoardStatus.CurrentPiece[Temp][MapColumn(MoveBeginX)] != -1)
                        return 0;
                }
            }
        }

        else return 1;
    }

    /* Move validity for a Knight */
    if( ChosenPiece == KnightLeft + 8 || ChosenPiece == KnightRight + 8 ) {
        if( (MapRow(DestinationY)-MapRow(MoveBeginY)) * (MapColumn(DestinationX)-MapColumn(MoveBeginX)) != 0
           && abs(MapRow(DestinationY)-MapRow(MoveBeginY)) + abs(MapColumn(DestinationX)-MapColumn(MoveBeginX)) == 3 )
            return 1;

        else return 0;
    }

    /* Move validity for a Bishop */
    if( ChosenPiece == BishopLeft + 8 || ChosenPiece == BishopRight + 8 ){
        if( abs(MapRow(DestinationY) - MapRow(MoveBeginY)) == abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) ){
            int TempX;
            int TempY;
            int DeltaX;
            int DeltaY;

            if( MapRow(DestinationY) - MapRow(MoveBeginY) > 0 ) { TempX =  MapRow(MoveBeginY) + 1; DeltaX = 1; }
            else { TempX = MapRow(MoveBeginY) -1 ; DeltaX = -1; }
            if( MapColumn(DestinationX) - MapColumn(MoveBeginX) > 0 ) { TempY = MapColumn(MoveBeginX) + 1; DeltaY = 1; }
            else { TempY = TempY = MapColumn(MoveBeginX) - 1; DeltaY = -1; }


            for ( ; abs(TempX - MapRow(DestinationY)) > 0 && abs(TempY - MapColumn(DestinationX)) > 0 ; TempX = TempX + DeltaX, TempY = TempY + DeltaY )
                if(BoardStatus.CurrentPiece[TempX][TempY] != -1)
                    return 0;

            return 1;

        }
        else return 0;
    }

    /* Move validity for a King */
    if( ChosenPiece == King + 8 ) {
        if( abs(MapRow(DestinationY) - MapRow(MoveBeginY)) + abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) == 1 )
            return 1;
        if( abs(MapRow(DestinationY) - MapRow(MoveBeginY)) + abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) == 2 &&
           abs(MapRow(DestinationY) - MapRow(MoveBeginY)) * abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) != 0 )
            return 1;

        return 0;
    }

    /* Move validity for a Queen */
    if( ChosenPiece == Queen + 8 ) {
        if( abs(MapRow(DestinationY) - MapRow(MoveBeginY)) * abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) == 0 ) {
            if( MapRow(DestinationY) - MapRow(MoveBeginY) == 0 ) {
                if( MapColumn(DestinationX) - MapColumn(MoveBeginX) > 0 ) {
                    for(Temp = MapColumn(MoveBeginX) + 1; Temp < MapColumn(DestinationX); Temp++ )
                        if(BoardStatus.CurrentPiece[MapRow(MoveBeginY)][Temp] != -1)
                            return 0;
                }

                else {
                    for(Temp = MapColumn(MoveBeginX) - 1; Temp > MapColumn(DestinationX); Temp-- )
                        if(BoardStatus.CurrentPiece[MapRow(MoveBeginY)][Temp] != -1)
                            return 0;
                }
            }

            else if( MapColumn(DestinationX) - MapColumn(MoveBeginX) == 0 ) {

                if( MapRow(DestinationY) - MapRow(MoveBeginY) > 0 ) {
                    for(Temp = MapRow(MoveBeginY) + 1; Temp < MapRow(DestinationY); Temp++ )
                        if(BoardStatus.CurrentPiece[Temp][MapColumn(MoveBeginX)] != -1)
                            return 0;
                }

                else {
                    for(Temp = MapRow(MoveBeginY) -1 ; Temp > MapRow(DestinationY); Temp-- ) {
                        if(BoardStatus.CurrentPiece[Temp][MapColumn(MoveBeginX)] != -1)
                            return 0;
                    }
                }
            }

            return 1;

        }

        else if( abs(MapRow(DestinationY) - MapRow(MoveBeginY)) == abs(MapColumn(DestinationX) - MapColumn(MoveBeginX)) ) {
            int TempX;
            int TempY;
            int DeltaX;
            int DeltaY;

            if( MapRow(DestinationY) - MapRow(MoveBeginY) > 0 ) { TempX =  MapRow(MoveBeginY) + 1; DeltaX = 1; }
            else { TempX = MapRow(MoveBeginY) -1 ; DeltaX = -1; }
            if( MapColumn(DestinationX) - MapColumn(MoveBeginX) > 0 ) { TempY = MapColumn(MoveBeginX) + 1; DeltaY = 1; }
            else { TempY = TempY = MapColumn(MoveBeginX) - 1; DeltaY = -1; }


            for ( ; abs(TempX - MapRow(DestinationY)) > 0 && abs(TempY - MapColumn(DestinationX)) > 0 ; TempX = TempX + DeltaX, TempY = TempY + DeltaY )
                if(BoardStatus.CurrentPiece[TempX][TempY] != -1)
                    return 0;

            return 1;
        }
        return 0;
    }
    return 1;
}

void DisplayMessage(const char* String) {
    glEnable(GL_BLEND);
    glBlendFunc (GL_ONE,GL_ONE);
    float Counter;
    char* Pointer = (char*)malloc(50);
    strcpy(Pointer, String);
    int Count;
    int Length = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*) String);
    /* Generate a semi transparent polygon for a warning message */

    glEnable(GL_POLYGON_SMOOTH);
    for(Counter = 0; Counter <= 0.8; Counter = Counter + 0.1 ) {
        glColor3f(Counter, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-400, -150);
        glVertex2f(400, -150);
        glVertex2f(400, 150);
        glVertex2f(-400, 150);
        glEnd();

        /* Display contents of the warning message */
        glColor3f(Counter, Counter, Counter);
        glRasterPos2f(-OrthoWidth * Length / (2 * WindowWidth), -OrthoHeight * 6 / WindowHeight);
        for(Count = 0; Pointer[Count] != '\0'; Count++ )
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Pointer[Count]);

        glFlush();
        usleep(50000);
    }

    glFlush();
    usleep(1000000);
    free(Pointer);
    glColor3f(1, 1, 1);
    glutPostRedisplay();
    glDisable(GL_BLEND);
}

void IfGameOver() {
    if( Piece.OtherPieces[King][Valid][ColorWhite] == 0 ) {
        /* Black Wins */
        DisplayMessage("Black Wins!");
        sleep(2);
        ResetGame();

    }

    if( Piece.OtherPieces[King][Valid][ColorBlack] == 0 ) {
        /* White Wins */
        DisplayMessage("White Wins!");
        sleep(2);
        ResetGame();
    }
}

int IfUnderCheck() {
    int Count;
    int CheckValue = 0;
    float DestinationX = Piece.OtherPieces[King][XCoordinate][ColorBlack];
    float DestinationY = Piece.OtherPieces[King][YCoordinate][ColorBlack];

    /* Determine if the White King is under Check */
    for( Count = 0; Count < 8 ; Count++ ) {
        MoveBeginX = Piece.Pawns[Count][XCoordinate][ColorWhite];
        MoveBeginY = Piece.Pawns[Count][YCoordinate][ColorWhite];

        FindPiece(MoveBeginX, MoveBeginY);
        if( Piece.Pawns[Count][Valid][ColorWhite]==1 && MoveValid(DestinationX,DestinationY) == 1) { 
        	CheckValue = 1; 
        	break; 
        }

        MoveBeginX = Piece.OtherPieces[Count][XCoordinate][ColorWhite];
        MoveBeginY = Piece.OtherPieces[Count][YCoordinate][ColorWhite];

        FindPiece(MoveBeginX, MoveBeginY);
        if( Piece.OtherPieces[Count][Valid][ColorWhite] == 1 && MoveValid(DestinationX,DestinationY) == 1) { 
        	CheckValue = 1; 
        	break; 
        }
    }

    DestinationX = Piece.OtherPieces[King][XCoordinate][ColorWhite];
    DestinationY = Piece.OtherPieces[King][YCoordinate][ColorWhite];

    /* Determine if the Black King is under Check */
    for( Count = 0; Count < 8 ; Count++ ) {
        MoveBeginX = Piece.Pawns[Count][XCoordinate][ColorBlack];
        MoveBeginY = Piece.Pawns[Count][YCoordinate][ColorBlack];

        FindPiece(MoveBeginX, MoveBeginY);
        if( Piece.Pawns[Count][Valid][ColorBlack] == 1 && MoveValid(DestinationX,DestinationY) == 1)
        { CheckValue = CheckValue ? 3 : 2; break; }

        MoveBeginX = Piece.OtherPieces[Count][XCoordinate][ColorBlack];
        MoveBeginY = Piece.OtherPieces[Count][YCoordinate][ColorBlack];

        FindPiece(MoveBeginX, MoveBeginY);
        if( Piece.OtherPieces[Count][Valid][ColorBlack] == 1 && MoveValid(DestinationX,DestinationY) == 1)
        { CheckValue = CheckValue ? 3 :2 ; break; }
    }

    return CheckValue;
}

void WarningFunction(int CheckValue) {
    if( CheckValue == 0 )
        return;
    if( CheckValue == 1 )
        DisplayMessage("Black under check!");
    if( CheckValue == 2 )
        DisplayMessage("White under check!");
    if( CheckValue == 3 )
        DisplayMessage("Both players under check!");
}

void MovePiece(float DestinationX, float DestinationY) {
    if( MapRow(DestinationY) == MapRow(MoveBeginY) && MapColumn(DestinationX) == MapColumn(MoveBeginX) )
        return;
    if(ChosenPiece == -1 && ChosenColor == -1)
        return;
    if(MoveValid(DestinationX, DestinationY) != 1)
        return;
    if(ChosenColor != Turn)
        return;
    /* Check if move is in turn and a valid piece is chosen */

    if( BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] != -1 ) {
        if(BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] < 8)
            Piece.Pawns[BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)]][Valid][BoardStatus.PieceColor[MapRow(DestinationY)][MapColumn(DestinationX)]] = 0;
        else
            Piece.OtherPieces[BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] - 8][Valid][BoardStatus.PieceColor[MapRow(DestinationY)][MapColumn(DestinationX)]] = 0;
    }

    if(ChosenPiece < 8) {
        Piece.Pawns[ChosenPiece][XCoordinate][ChosenColor] = DestinationX;
        Piece.Pawns[ChosenPiece][YCoordinate][ChosenColor] = DestinationY;
    }

    else {
        Piece.OtherPieces[ChosenPiece - 8][XCoordinate][ChosenColor] = DestinationX;
        Piece.OtherPieces[ChosenPiece - 8][YCoordinate][ChosenColor] = DestinationY;
    }

    BoardStatus.CurrentPiece[MapRow(DestinationY)][MapColumn(DestinationX)] = ChosenPiece;
    BoardStatus.PieceColor[MapRow(DestinationY)][MapColumn(DestinationX)] = ChosenColor;
    /* Validate board members to their corresponding values */
    BoardStatus.CurrentPiece[MapRow(MoveBeginY)][MapColumn(MoveBeginX)] = -1;
    BoardStatus.PieceColor[MapRow(MoveBeginY)][MapColumn(MoveBeginX)] = -1;
    Turn = 1 - Turn;
    /* Swap player */

    MyDisplay();
    IfGameOver();
    WarningFunction(IfUnderCheck());
}

void ShowValidMoves() {
    if(ChosenColor != Turn ) return;

    float TempX;
    float TempY;

    /* Iterate through every block on the board  and check if a piece's move is valid */
    for(TempX = -400; TempX < 400; TempX+=100)
        for(TempY = -400; TempY < 400; TempY+=100)
            if(MoveValid(TempX,TempY) == 1) {

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE);
                glColor3f(0,0,1);

                glBegin(GL_POLYGON);
                glVertex2i(TempX,TempY);
                glVertex2i(TempX+100,TempY);
                glVertex2i(TempX+100,TempY+100);
                glVertex2i(TempX,TempY+100);
                glEnd();

                glDisable(GL_BLEND);

            }

    glFlush();


}

void MyMouse(int Button, int State, int X, int Y) {
    /* Determine source X and Y coordinates */
    if(Button == GLUT_LEFT && State == GLUT_DOWN) {
        MoveBeginX = ( -OrthoWidth/2 + OrthoWidth * (double)X / WindowWidth );
        if (MoveBeginX < 0) MoveBeginX = (int)((MoveBeginX - 100) / 100) * 100;
        else MoveBeginX = (int)(MoveBeginX / 100) * 100;

        MoveBeginY = OrthoHeight/2 - (OrthoHeight * Y / (double)WindowHeight);
        if (MoveBeginY < 0) MoveBeginY = (int)((MoveBeginY - 100) / 100) * 100;
        else MoveBeginY = (int)(MoveBeginY / 100) * 100;

        FindPiece(MoveBeginX, MoveBeginY);
        ShowValidMoves();
    }

    /* Determine destination X and Y coordinates */
    if(Button == GLUT_LEFT && State == GLUT_UP) {

        float DestinationX = ( -OrthoWidth/2 + OrthoWidth * (double)X / WindowWidth );
        if (DestinationX < 0) DestinationX = (int)((DestinationX - 100) / 100) * 100;
        else DestinationX = (int)(DestinationX / 100) * 100;

        float DestinationY = OrthoHeight/2 - (OrthoHeight * Y / (double)WindowHeight);
        if (DestinationY < 0) DestinationY = (int)((DestinationY - 100) / 100) * 100;
        else DestinationY = (int)(DestinationY / 100) * 100;

        MovePiece(DestinationX, DestinationY);

    }
}

void MyPassiveMouse(int X, int Y) {
    MyDisplay();

    X = ( -OrthoWidth/2 + OrthoWidth * (double)X / WindowWidth );
    if (X < 0) X = (int)((X - 100) / 100) * 100;
    else X = (int)(X / 100) * 100;

    Y = OrthoHeight/2 - (OrthoHeight * Y / (double)WindowHeight);
    if (Y < 0) Y = (int)((Y - 100) / 100) * 100;
    else Y = (int)(Y / 100) * 100;

    if(!(X >= -400 && Y >= -400 && X <= 390 && Y <= 390)) return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glColor3f(0,0,1);

    /* Draw a custom cursor during passive mouse movememnt */
    for(int Count = 0 ; Count <=10 ; Count++ ) {
        glBegin(GL_LINE_LOOP);
        glVertex2i(X+Count,Y+Count);
        glVertex2i(X+100-Count,Y+Count);
        glVertex2i(X+100-Count,Y+100-Count);
        glVertex2i(X+Count,Y+100-Count);
        glVertex2i(X+Count,Y+Count);
        glEnd();
    }

    glDisable(GL_BLEND);
    glFlush();

}

void CleanUp() {
    /* Deletes all generated pointers */
    glDeleteTextures(1, &BoardTexture);
    for(int Count = 0; Count < 8; Count ++)
        for(int ForegroundColor = 0 ; ForegroundColor < 2 ; ForegroundColor++ )
            for(int BackgroundColor = 0; BackgroundColor < 2; BackgroundColor++ )
            {
                glDeleteTextures(1, &PawnTextures[Count][ForegroundColor][BackgroundColor]);
                glDeleteTextures(1, &OtherTextures[Count][ForegroundColor][BackgroundColor]);
            }

    /* Frees all allocated resources */
    free(BoardData);
    free(Data);
    fclose(Pointer);
}

void MyMenu(int Identifier) {
    /* Various routines for Menu options on Right Click */
    switch (Identifier) {
        case 1: 
        	glutFullScreen(); 
        	break;
        case 2: 
        	glutReshapeWindow(500, 500); 
        	break;
        case 3: 
        	ResetGame();  
        	break;
        case 4: 
        	CleanUp(); 
        	exit(0);
    }
}

int main(int argc, char** argv) {
    /* Creation of main window */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Chess v2.1");

    /* Custom initializations */
    WindowInitializations();
    InitializeBoardMatrix();
    GenerateTextures();

    /* Registering event callback routines */
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouse);
    glutCreateMenu(MyMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Full Screen", 1);
    glutAddMenuEntry("Windowed Mode", 2);
    glutAddMenuEntry("Reset game", 3);
    glutAddMenuEntry("Exit", 4);
    glutPassiveMotionFunc(MyPassiveMouse);

    /* Entering GLUT's loop */
    glutMainLoop();

    return 0;
}
