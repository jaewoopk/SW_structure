#include "block.h"

int main(void) {
    int key;
    srand((unsigned int)time(NULL));
    block_id = rand() % 28;

    COORD curPos = GetCurrentCursorPos();

    curPos.X = 20;
    curPos.Y = 10;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    RemoveCursor();
    ShowBlock(blockModel[block_id]);

    while (1) {
        while (!_kbhit()) {
        }
        key = _getch();
        switch (key) {
            case UPLEFT :
                BlockUp();
                ShiftLeft();
                break ;
            case UP :
                BlockUp();
                break ;
            case UPRIGHT :
                BlockUp();
                ShiftRight(); 
                break ;
            case LEFT :
                ShiftLeft();
                break ;
            case STILL :
                break ;
            case RIGHT :
                ShiftRight();
                break ;
            case DOWNLEFT :
                BlockDown();
                ShiftLeft();
                break ;
            case DOWN :
                BlockDown();
                break ;
            case DOWNRIGHT :
                BlockDown();
                ShiftRight();
                break ;
            case ROTATERCLOCK :
                ReverseRotateBlock();
                break ;
            case ROTATETWICE :
                RotateTwiceBlock();
        }
    }
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

void BlockUp(void) {
     COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.Y -= 1;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}

int BlockDown(void) {
    COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.Y += 1;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
    return (0);
}

void ReverseRotateBlock(void) {
    int block_senior;

    DeleteBlock(blockModel[block_id]);
    block_senior = block_id - block_id % 4;
    block_id = block_senior + (block_id + 3) % 4;
    ShowBlock(blockModel[block_id]);
}

void RotateTwiceBlock(void) {
    int block_senior;

    DeleteBlock(blockModel[block_id]);
    block_senior = block_id - block_id % 4;
    block_id = block_senior + (block_id + 2) % 4;
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
                printf("��");
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