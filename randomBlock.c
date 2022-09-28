#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "block.h"

void DeleteBlock(char blockInfo[4][4]);
void ShowBlock(char blockInfo[4][4]);
void SetCurrentCursorPos(int x, int y);
void RandomlyMoving(void);
void TypeMoving(COORD *curPos, int ch_type);
COORD GetCurrentCursorPos(void);

int main(void) {
    for (int i = 0; i < 10; i++) {
        RandomlyMoving();
    }
    printf("It's end!");
    getchar();
    return (0);
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
                printf("��");
            }
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void RandomlyMoving(void) {
    srand((unsigned int)time(NULL));
    int block_id = (rand() % 7) * 4;
    int choose_type = (rand() % 8);
    COORD curPos = GetCurrentCursorPos();
    curPos.X = (rand() % 40) * 2;
    curPos.Y = (rand() % 40);
    for (int i = 0; i < 10; i++) {
        SetCurrentCursorPos(curPos.X, curPos.Y);
        ShowBlock(blockModel[block_id + (i % 4)]);
        Sleep(500);
        DeleteBlock(blockModel[block_id + (i % 4)]);
        TypeMoving(&curPos, choose_type);
    }

}

void TypeMoving(COORD *curPos, int ch_type) {
    switch (ch_type) {
    case 0 :
        curPos->Y -= 1;
        break ;
    case 1 :
        curPos->X += 2;
        curPos->Y -= 1;
        break ;
    case 2 :
        curPos->X += 2;
        break ;
    case 3 :
        curPos->X += 2;
        curPos->Y += 1;
        break ;
    case 4 :
        curPos->Y += 1;
        break ;
    case 5 :
        curPos->X -= 2;
        curPos->Y += 1;
        break ;
    case 6 :
        curPos->X -= 2;
        break ;
    default :
        curPos->X -= 2;
        curPos->Y -= 1;
    }
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