#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "block.h"

int block_id;

void RemoveCursor(void);
void ShiftRight(void);
void ShiftLeft(void);
void BlockDown(void);
void RotateBlock(void);
void DeleteBlock(char blockInfo[4][4]);
void ShowBlock(char blockInfo[4][4]);
void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);

int main(void) {
    srand((unsigned int)time(NULL));
    block_id = rand() % 28;

    COORD curPos = GetCurrentCursorPos();

    curPos.X = 20;
    curPos.Y = 10;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    RemoveCursor();

    BlockDown();
    Sleep(500);
    ShiftRight();
    Sleep(500);
    RotateBlock();
    Sleep(500);
    BlockDown();
    Sleep(500);
    ShiftLeft();
    Sleep(500);
    BlockDown();
    Sleep(500);
    getchar();
    return (0);
}

void RemoveCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void ShiftRight(void) {
    COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.X += 2;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}

void ShiftLeft(void) {
    COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.X -= 2;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}

void BlockDown(void) {
    COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.Y += 1;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}

void RotateBlock(void) {
    int block_base;

    DeleteBlock(blockModel[block_id]);
    if (block_id % 4 == 3) block_id -= 1;
    else block_id += 1;
    ShowBlock(blockModel[block_id]);
}

void DeleteBlock(char blockInfo[4][4]) {
    int y, x;
    COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);

            if (blockInfo[y][x] == 1) {
                printf("  ");
            }
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void ShowBlock(char blockInfo[4][4]) {
    int x, y;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);

            if (blockInfo[y][x] == 1) {
                printf("бс");
            }
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void SetCurrentCursorPos(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void) {
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}