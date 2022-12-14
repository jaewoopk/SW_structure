#include "block.h"

int main(void) {
    int key;
    srand((unsigned int)time(NULL));
    block_id = rand() % 28;
    speed = 20;
    COORD curPos = GetCurrentCursorPos();
    RemoveCursor();

    DrawGameBoard();

    curPos.X = GBOARD_WIDTH;
    curPos.Y = GBOARD_ORIGIN_Y;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
    while(1) {
        ProcessKeyInput();
    }
    getchar();
    return (0);
}


void DrawGameBoard(void) {
    int x, y;
    
    for (y = 0; y <= GBOARD_HEIGHT; y++){
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH / 2] = 1;
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y+y);
        if (y == GBOARD_HEIGHT)
            printf("??");
        else
            printf("??");
    }

    for (x = 0; x < GBOARD_WIDTH + 2; x++){
        printf("??");
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }

    for (y = 0; y <= GBOARD_HEIGHT; y++){
        SetCurrentCursorPos(GBOARD_ORIGIN_X+ GBOARD_WIDTH + 2, GBOARD_ORIGIN_Y+GBOARD_HEIGHT -y);
        if (y == 0)
            printf("??");
        else
            printf("??");
    }
}

void RemoveCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
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

void ProcessKeyInput(void) {
    int key;
    BlockDown();

    for (int i = 0; i < 20; i++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key) {
            case LEFT :
                ShiftLeft();
                break;
            case RIGHT :
                ShiftRight();
                break;
            case UP :
                ReverseRotateBlock();
                break;
            }
        }
        Sleep(speed);
    }
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

int BlockDown(void) {
    if (!DetectCollision(curPos.X, curPos.Y + 1, blockModel[block_id])) {
        return (0);
    }
    DeleteBlock(blockModel[block_id]);
    curPosY += 1;
    SetCurrentCursorPos(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
    return (1);
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
                printf("??");
            }
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
