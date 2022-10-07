#include "block.h"

int main(void) {
    RemoveCursor();
    speed = 10;
    curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X) / 2;
    curPosY = GBOARD_ORIGIN_Y;
    srand((unsigned int)time(NULL));
    block_id = (rand() % 7) * 4;

    DrawGameBoard();
    GameBoardInfo();

    ShowBlock(blockModel[block_id]);
    while (1){
        if (IsGameOver())
            break ;
        while(1) {
            if (!BlockDown()) {
                AddBlockToBoard();
                curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X) / 2;
                curPosY = GBOARD_ORIGIN_Y;
                srand((unsigned int)time(NULL));
                block_id = (rand() % 7) * 4;
                SetCurrentCursorPos(curPosX, curPosY);
                ShowBlock(blockModel[block_id]);
                break ;
            }
            ProcessKeyInput();
        }
    }
    SetCurrentCursorPos(12, 0);
    puts("Game Over!!");
    getchar();
    return (0);
}

int IsGameOver(void) {
    if (!DetectCollision(curPosX, curPosY, blockModel[block_id])) {
        return (1);
    }
    return (0);
}

void AddBlockToBoard(void) {
    int x, y, arrCurX, arrCurY;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            arrCurX = (curPosX - GBOARD_ORIGIN_X) / 2;
            arrCurY = curPosY - GBOARD_ORIGIN_Y;
            
            if (blockModel[block_id][y][x] == 1)
                gameBoardInfo[arrCurY + y][arrCurX + x] = 1;
        }
    }
}

int DetectCollision(int posX, int posY, char blockModel[4][4]) {
    int x, y;
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;
    int arrY = posY - GBOARD_ORIGIN_Y;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            if ((gameBoardInfo[arrY + y][arrX + x] == 1) && (blockModel[y][x] == 1))
                return (0);
        }
    }
    return (1);
}

void GameBoardInfo(void) {
    int y, x;

    for (y = 0; y < GBOARD_HEIGHT; y++){
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH / 2] = 1;
    }

    for (x = 0; x < GBOARD_WIDTH + 2; x++){
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }
}

void DrawGameBoard(void) {
    int y, x;
    
    for (y = 0; y <= GBOARD_HEIGHT; y++){
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
            printf("¦¦");
        else
            printf("¦¢");
    }

    for (x = 0; x < GBOARD_WIDTH; x++){
        printf("¦¡");
    }

    for (y = 0; y <= GBOARD_HEIGHT; y++){
        SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, GBOARD_ORIGIN_Y + GBOARD_HEIGHT -y);
        if (y == 0)
            printf("¦¥");
        else
            printf("¦¢");
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
    if (!DetectCollision(curPosX, curPosY + 1, blockModel[block_id]))
        return;

    int key;

    for (int i = 0; i < 25; i++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key) {
            case SPACE :
                for (int j = 0; j < 30; j++) {
                    BlockDown();
                }
                break ;
            case LEFT :
                ShiftLeft();
                break ;
            case RIGHT :
                ShiftRight();
                break ;
            case UP :
                ReverseRotateBlock();
                break ;
            }
        }
        Sleep(speed);
    }
}

void ShiftRight(void) {
    if (!DetectCollision(curPosX + 2, curPosY, blockModel[block_id])) {
        return;
    }
    DeleteBlock(blockModel[block_id]);
    curPosX += 2;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}

void ShiftLeft(void) {
    if (!DetectCollision(curPosX - 2, curPosY, blockModel[block_id])) {
       return;
    }
    DeleteBlock(blockModel[block_id]);
    curPosX -= 2;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}

int BlockDown(void) {
    if (!DetectCollision(curPosX, curPosY + 1, blockModel[block_id])) {
      return (0);
    }
    DeleteBlock(blockModel[block_id]);
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
    return (1);
}

void ReverseRotateBlock(void) {
    int block_base = (block_id / 4) * 4;
    int block_rotated = block_base + (block_id + 1) % 4;

    if (!DetectCollision(curPosX, curPosY, blockModel[block_rotated])) {
        return;
    }
    DeleteBlock(blockModel[block_id]);
    block_id = block_rotated;
    
    ShowBlock(blockModel[block_id]);
}

void RotateTwiceBlock(void) {
    ReverseRotateBlock();
    ReverseRotateBlock();
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
    int y, x;
    COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);

            if (blockInfo[y][x] == 1) {
                printf("¡á");
            }
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
