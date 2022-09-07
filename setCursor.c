#include <stdio.h>
#include <windows.h>

int main(void) {
    COORD p1;

    HANDLE console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 6; i < 25; i++) {
        for (int j = 3; j < 13; j++) {
            if (!(j == 3 || j == 12) && !(i == 6 || i == 24)) continue;
            p1.X = i;
            p1.Y = j;
            SetConsoleCursorPosition(console, p1);
            printf("бс");
        }
    }

    getchar();
    return 0;
}