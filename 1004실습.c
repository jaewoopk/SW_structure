#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define GBOARD_WIDTH 20
#define GBOARD_HEIGHT 20
#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2
// ��������, �����迭
int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
int block_id;// ��� ���̵� �������� ����
int curPosX = 10, curPosY = 2;
int speed = 50;
char blockModel[][4][4] =
{
    /* ù ��° ���
         ��
         ����     */
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0} },

        /* �� ��° ���
                 ��
             ����     */
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0} },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0} },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 1, 0, 0},
            {0, 0, 0, 0} },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0} },

            /* �� ��° ���
                    ��
                  ����    */
            {
                {0, 0, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0} },
            {
                {0, 0, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 1, 0, 0} },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 0, 0} },
            {
                {0, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0} },

                /* �� ��° ���

                      �����   */
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0} },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0} },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0} },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0} },

                /* �ټ� ��° ���

                      ���
                      ���      */
                {
                    {1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0} },
                {
                    {1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0} },
                {
                    {1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0} },
                {
                    {1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0} },


                    /* ���� ��° ���
                            ���
                          ���      */
                    {
                        {0, 0, 0, 0},
                        {0, 1, 1, 0},
                        {1, 1, 0, 0},
                        {0, 0, 0, 0} },
                    {
                        {0, 1, 0, 0},
                        {0, 1, 1, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0} },
                    {
                        {0, 0, 0, 0},
                        {0, 1, 1, 0},
                        {1, 1, 0, 0},
                        {0, 0, 0, 0} },
                    {
                        {0, 1, 0, 0},
                        {0, 1, 1, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0} },

                        /* �ϰ� ��° ���

                             ���
                               ���    */
                       {
                           {0, 0, 0, 0},
                           {1, 1, 0, 0},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0} },
                       {
                           {0, 1, 0, 0},
                           {1, 1, 0, 0},
                           {1, 0, 0, 0},
                           {0, 0, 0, 0} },
                       {
                           {0, 0, 0, 0},
                           {1, 1, 0, 0},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0} },
                       {
                           {0, 1, 0, 0},
                           {1, 1, 0, 0},
                           {1, 0, 0, 0},
                           {0, 0, 0, 0} },
};
COORD GetCurrentCursorPos(void)
{
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;
    return curPoint;

}
void SetCurrentCursorPos(int t, int y)
{
    COORD pos = { t, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void ShowBlock(char blockInfo[4][4])
{
    int y, t;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 4; y++)
    {
        for (t = 0; t < 4; t++)
        {
            SetCurrentCursorPos(curPos.X + (t * 2), curPos.Y + y);
            if (blockInfo[y][t] == 1)
                printf("��");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
void DeleteBlock(char blockInfo[4][4])
{
    int y, t;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 4; y++)
    {
        for (t = 0; t < 4; t++)
        {
            SetCurrentCursorPos(curPos.X + t * 2, curPos.Y + y);
            if (blockInfo[y][t] == 1)
                printf("  ");// ��ĭ
            //printf("aa");
            //printf("��");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
void RemoveCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void Shift_R()// �������̵�
{
    //Sleep(300);
    if (!DetectCollision(curPosX + 2, curPosY, blockModel[block_id])) {
        return;
    }
    DeleteBlock(blockModel[block_id]);
    curPosX += 2;
    SetCurrentCursorPos(curPosX, curPosY);

    ShowBlock(blockModel[block_id]);
}
void Shift_L()// �������� �̵�
{
    //Sleep(300);
    if (!DetectCollision(curPosX - 2, curPosY, blockModel[block_id])) {
        return;
    }
    DeleteBlock(blockModel[block_id]);
    curPosX -= 2;
    SetCurrentCursorPos(curPosX, curPosY);

    ShowBlock(blockModel[block_id]);
}
void Shift_D()// �Ʒ��� �̵�
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Shift_U()// ���� �̵�
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosY -= 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Shift_RU()
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosX += 2;
    curPosY -= 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Shift_RD()
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosX += 2;
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Shift_LU()
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosX -= 2;
    curPosY -= 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Shift_LD()
{
    //Sleep(300);
    DeleteBlock(blockModel[block_id]);
    curPosX -= 2;
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
}
void Rotate90()
{
    int block_base = (block_id / 4) * 4;
    int block_rotated = block_base + (block_id + 1) % 4;
   
    if (!DetectCollision(curPosX, curPosY, blockModel[block_rotated])) {
        return;
    }
    DeleteBlock(blockModel[block_id++]);
    int block_id = block_rotated;
    if (block_id == (block_base + 4))// �� �κ��� ����� ������.
    {
        block_id = block_base;
    }
    ShowBlock(blockModel[block_id]);

}
void Rotate180()
{
    Rotate90();
    Rotate90();
}
void ProcessKeyInput()
{
    if (!DetectCollision(curPosX, curPosY + 1, blockModel[block_id]))// ProcessKeyInput�Լ����� �������� �߰��ؾ���
    {
        return;
    }

    int key;
    //Shift_D();

    for (int i = 0; i < 20; i++)//1�ʿ� 20�� �˻�
    {
        if (_kbhit() != 0)
        {
            key = _getch();
            switch (key)
            {
            case LEFT:
                Shift_L();
                break;
            case RIGHT:
                Shift_R();
                break;
            case UP:// ȸ��
                Rotate90();
                break;

            }
        }

        Sleep(speed);
    }
}
void DrawGameBoard()
{
    int y, x;
    for (y = 0; y <= GBOARD_HEIGHT; y++)
    {

        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

        if (y == GBOARD_HEIGHT)
        {
            printf("��");
        }
        else
            printf("��");
    }
    for (x = 0; x < GBOARD_WIDTH; x++)
    {
        printf("��");
    }
    for (y = 0; y <= GBOARD_HEIGHT; y++)
    {

        SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, GBOARD_ORIGIN_Y + GBOARD_HEIGHT - y);

        if (y == 0)
        {
            printf("��");// ��+ ����
        }
        else
            printf("��");
    }
    // curPosX = GBOARD_ORIGIN_X + GBOARD_WIDTH;
    // curPosY = 0;
}
void GameBoardInfo()
{
    int x, y;
    for (y = 0; y < GBOARD_HEIGHT; y++)//Draw Gameboard
    {
        gameBoardInfo[y][0] = 1;// ���� ��
        gameBoardInfo[y][(GBOARD_WIDTH / 2)] = 1;// ������ ��
    }
    for (x = 0; x < GBOARD_WIDTH + 2; x++)// �ٴ�
    {
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }
}


int DetectCollision(int posX, int posY, char blockModel[4][4])
{
    int x, y;
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;
    int arrY = posY - GBOARD_ORIGIN_Y;
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            if ((blockModel[y][x] == 1) &&( gameBoardInfo[arrY + y][arrX + x] == 1))
            {
                return 0;
            }
        }
    }
    return 1;
}
int BlockDown()
{
    if (!DetectCollision(curPosX, curPosY + 1, blockModel[block_id]))
    {
        return 0;
    }
    DeleteBlock(blockModel[block_id]);
    curPosY += 1;
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[block_id]);
    return 1;
}
int main() {
    RemoveCursor();
    speed = 10;
    srand((unsigned int)time(NULL));
    block_id = (rand() % 7) * 4;
    //printgameboard();

    DrawGameBoard();//������ �׸��� �Լ�
    GameBoardInfo();//�浹 üũ�� 2�����迭
    //curPosX, curPosY �� ���� �����ϴ°��� ����. Set~ �Լ��� �̿��� �� ������ curPosX,Y�� ���������̿���.. �����ϰ� curPosX,curPosY�� �����ϴ°��� ����.
    ShowBlock(blockModel[block_id]);

    while (1)
    {
        BlockDown();
        ProcessKeyInput();
    }



    getchar();
    return 0;

}