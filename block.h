#ifndef BLOCK_H
# define BLOCK_H

# define UPLEFT 113
# define UP 119
# define UPRIGHT 101
# define LEFT 97
# define STILL 115
# define RIGHT 100
# define DOWNLEFT 122
# define DOWN 120
# define DOWNRIGHT 99
# define ROTATERCLOCK 106
# define ROTATETWICE 107
# define GBOARD_WIDTH 20
# define GBOARD_HEIGHT 20
# define GBOARD_ORIGIN_X 4
# define GBOARD_ORIGIN_Y 2


# include <stdio.h>
# include <windows.h>
# include <time.h>
# include <conio.h>

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
char blockModel[][4][4] =
{
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },  
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },   
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0} },
 
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },  
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0} },   
    {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },
 
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },  
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0} },
 
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0} },  
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0} },
 
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },  
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },   
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },   
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },
 
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },  
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },  
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} }, 
 
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },  
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0} },
    {  
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },  
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0} },
};

int block_id;
int speed;

int DetectCollision(int posX, int posY, char blockModel[4][4]);
void DrawGameBoard(void);
void ProcessKeyInput(void);
void RemoveCursor(void);
void ShiftRight(void);
void ShiftLeft(void);
void BlockUp(void);
int BlockDown(void);
void ReverseRotateBlock(void);
void RotateTwiceBlock(void);
void DeleteBlock(char blockInfo[4][4]);
void ShowBlock(char blockInfo[4][4]);
void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);

#endif