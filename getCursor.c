#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

int main(void) {
    char blockModel[][4][4] = {
        {
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0} },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}, }
    };
    CONSOLE_SCREEN_BUFFER_INFO curInfo;
    HANDLE console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    int j = 0;
    bool check = false;
    for (int i = 0; i < 7; i++) {
        for (int k = 0; k < j; k++) {
            printf(" ");
        }
        GetConsoleScreenBufferInfo(console, &curInfo);
        printf("[%d, %d] \n",curInfo.dwCursorPosition.X, curInfo.dwCursorPosition.Y);
        if (j == 3)
            check = true;
        if (check)
            j--;
        else
            j++;
    }

    getchar();
    return (0);
}