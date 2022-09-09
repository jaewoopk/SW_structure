#include <stdio.h>
#include <windows.h>

char blockModel[][4][4] = {
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    }
};

void ShowBlock(char blockInfo[4][4]);
void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);

int main(void) {
    SetCurrentCursorPos(0, 0);
    ShowBlock(blockModel[0]);

    SetCurrentCursorPos(10, 0);
    ShowBlock(blockModel[1]);
    
    SetCurrentCursorPos(0, 6);
    ShowBlock(blockModel[2]);

    SetCurrentCursorPos(10, 6);
    ShowBlock(blockModel[3]);

    getchar();
    return (0);
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