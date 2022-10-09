#include "block.h"

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

int main() {
    GameBoardInfo();
    for (int y = 0; y < GBOARD_HEIGHT + 1; y++) {
        for (int x = 0; x < GBOARD_WIDTH + 2; x++) {
            printf("%d",gameBoardInfo[y][x]);
        }
        printf("\n");
    }
    getchar();
    return 0;
}
