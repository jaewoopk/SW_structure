#include "block.h"

int main(void) {
    speed = 20;
    stage = 1;
    speedcount = FALSE;
    RemoveCursor();
    PrintScore();
    curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X);
    curPosY = GBOARD_ORIGIN_Y;
 /* srand((unsigned int)time(NULL));
    block_id = (rand() % 7) * 4;*/
    DrawGameBoard();
    GameBoardInfo();

    //ShowBlock(blockModel[block_id]);
    while (1) {
        if (IsGameOver())
            break;
        keyChecking();
        while (1) {
            if (!BlockDown()) {
                if (block_id == 20) {
                    BlockDestroyUp();
                    PrintScore();
                    curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X);
                    curPosY = GBOARD_ORIGIN_Y;
                    //srand((unsigned int)time(NULL));
                    //block_id = (rand() % 7) * 4;
                    SetCurrentCursorPos(curPosX, curPosY);
                    break;
                }
                else if (block_id == 24) {
                    DestroyBlock();
                    RemoveFillUpLine();
                    PrintScore();
                    curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X);
                    curPosY = GBOARD_ORIGIN_Y;
                    SetCurrentCursorPos(curPosX, curPosY);
                    break;
                }
                AddBlockToBoard();
                RemoveFillUpLine();
                PrintScore();
                curPosX = (GBOARD_WIDTH + GBOARD_ORIGIN_X);
                curPosY = GBOARD_ORIGIN_Y;
                //srand((unsigned int)time(NULL));
                //block_id = (rand() % 7) * 4;
                SetCurrentCursorPos(curPosX, curPosY);
                //ShowBlock(blockModel[block_id]);
                break;
            }
            ProcessKeyInput();
        }
    }
    SetCurrentCursorPos(12, 0);
    puts("Game Over!!");
    getchar();
    return (0);
}

void DestroyBlock(void) {
    DeleteBlock(blockModel[block_id]);
    if (curPosY < GBOARD_ORIGIN_Y + GBOARD_HEIGHT - 2) {
        gameBoardInfo[curPosY - 1][curPosX / 2 - 2] = 0;
        gameBoardInfo[curPosY - 1][curPosX / 2 - 1] = 0;
        gameBoardInfo[curPosY - 1][curPosX / 2] = 0;
        gameBoardInfo[curPosY][curPosX / 2 - 1] = 0;
        gameBoardInfo[curPosY][curPosX / 2] = 0;
    }
    else {
        gameBoardInfo[curPosY - 1][curPosX / 2 - 2] = 0;
        gameBoardInfo[curPosY - 1][curPosX / 2 - 1] = 0;
        gameBoardInfo[curPosY - 1][curPosX / 2] = 0;
    }
}

void BlockDestroyUp(void) {
    while (curPosY >= GBOARD_ORIGIN_Y + 2) {
        DeleteBlock(blockModel[block_id]);
        curPosY -= 1;
        SetCurrentCursorPos(curPosX, curPosY);
        ShowBlock(blockModel[block_id]);
        Sleep(30);
    }
    DeleteBlock(blockModel[block_id]);
}

void keyChecking(void) {
    int key;

    key = _getch();
    switch (key) {
    case ZERO :
        block_id = 0;
        break ;
    case ONE:
        block_id = 4;
        break;
    case TWO:
        block_id = 8;
        break;
    case THREE:
        block_id = 12;
        break;
    case FOUR:
        block_id = 16;
        break;
    case FIVE:
        block_id = 20;
        break;
    case SIX:
        block_id = 24;
        break;
    }
}
void PrintScore(void) {
    SetCurrentCursorPos(30, 10);
    printf("Score : %d", score);

    SetCurrentCursorPos(30, 12);
    printf("Stage : %d", stage);

}

void RemoveFillUpLine(void) {
    int line, y, x;

    for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
        for (x = 1; x < GBOARD_WIDTH + 1; x++) {
            if (gameBoardInfo[y][x] != 1) {
                break;
            }
        }
        if (x == (GBOARD_WIDTH + 1)) {
            for (line = 0; y - line > 0; line++) {
                memcpy(&gameBoardInfo[y - line][1], &gameBoardInfo[(y - line) - 1][1], (GBOARD_WIDTH + 1) * sizeof(int));
            }
            y++;
            score += 10;
            /*if (score % 10 == 0) {
                speed--;
            }*/
            if (score % 100 == 0) {
                stage++;
            }
        }
    }
    RedrawBlocks();
    /*
    SetCurrentCursorPos(50, 5);

    for (int i = 0; i < GBOARD_HEIGHT + 1; i++) {
        for (int j = 0; j < GBOARD_WIDTH + 2; j++) {
            printf(" %d", gameBoardInfo[i][j]);
        }
        printf("\n");
        SetCurrentCursorPos(50, 5 + i);
    }
    */
}

void RedrawBlocks(void) { 
    int y, x;
    int cursX, cursY;

    for (y = 0; y < GBOARD_HEIGHT; y++) {
        for (x = 1; x < GBOARD_WIDTH + 1; x++) {
            cursX = x * 2 + GBOARD_ORIGIN_X;
            cursY = y + GBOARD_ORIGIN_Y;
            SetCurrentCursorPos(cursX, cursY);
            if (gameBoardInfo[y][x] == 1) {
                printf("¡á");
            }
            else {
                printf("  ");
            }
        }
    }
}

int IsGameOver(void) {
    if (!DetectCollision(curPosX, curPosY, blockModel[block_id])) {
        return (1);
    }
    /*if (speed <= 0) {
        SetCurrentCursorPos(20, 10);
        puts("Game Clear!!");
        return (1);
    }*/
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

    for (y = 0; y < GBOARD_HEIGHT + 1; y++) {
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
    }

    for (x = 0; x < GBOARD_WIDTH + 2; x++) {
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }
}

void DrawGameBoard(void) {
    int y, x;

    for (y = 0; y < GBOARD_HEIGHT + 1; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
            printf("¦¦");
        else
            printf("¦¢");
    }

    for (x = 0; x < (GBOARD_WIDTH + 1) * 2; x++) {
        printf("¦¡");
    }

    for (y = 0; y < GBOARD_HEIGHT + 1; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT - y);
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
    COORD pos = { x, y };
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
            case SPACE:
                for (int j = 0; j < 50; j++) {
                    BlockDown();
                }
                break;
            case LEFT:
                ShiftLeft();
                break;
            case RIGHT:
                ShiftRight();
                break;
            case UP:
                ReverseRotateBlock();
                break;
            case FAST_SPEED:
                if (!speedcount) {
                    speed = 10;
                    speedcount = TRUE;
                }
                else {
                    speed = 20;
                    speedcount = FALSE;
                }
                break;
            case ZERO:
                DeleteBlock(blockModel[block_id]);
                block_id = 0;
                ShowBlock(blockModel[block_id]);
                break;
            case ONE:
                DeleteBlock(blockModel[block_id]);
                block_id = 4;
                ShowBlock(blockModel[block_id]);
                break;
            case TWO:
                DeleteBlock(blockModel[block_id]);
                block_id = 8;
                ShowBlock(blockModel[block_id]);
                break;
            case THREE:
                DeleteBlock(blockModel[block_id]);
                block_id = 12;
                ShowBlock(blockModel[block_id]);
                break;
            case FOUR:
                DeleteBlock(blockModel[block_id]);
                block_id = 16;
                ShowBlock(blockModel[block_id]);
                break;
            }
        }
        Sleep(speed);
    }
}

void ShiftRight(void) {
    if (!DetectCollision(curPosX + 2, curPosY, blockModel[block_id])) {
        DeleteBlock(blockModel[block_id]);
        curPosX = GBOARD_ORIGIN_X + 2;
        SetCurrentCursorPos(curPosX, curPosY);
        ShowBlock(blockModel[block_id]);
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
    //COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            SetCurrentCursorPos(curPosX + (x * 2), curPosY + y);

            if (blockInfo[y][x] == 1) {
                printf("  ");
            }
        }
    }
    SetCurrentCursorPos(curPosX, curPosY);
}

void ShowBlock(char blockInfo[4][4]) {
    int y, x;
    //COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            SetCurrentCursorPos(curPosX + (x * 2), curPosY + y);

            if (blockInfo[y][x] == 1) {
                printf("¡á");
            }
        }
    }
    SetCurrentCursorPos(curPosX, curPosY);
}
