/******************************************************************************************************

    *  ��ƿ��Ƽ
        - Ŀ�� ����
        - ������
        - ��������
        - ���� ���
        - ȭ�� �ʱ�ȭ
        - �� ���

******************************************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Ŀ�� ���� �Լ�
/*
    Ŀ�� ����ü
    ���� ����Ʈ : https://docs.microsoft.com/ko-kr/windows/console/console-cursor-info-str
*/
CONSOLE_CURSOR_INFO Curinfo;

/*
    Ŀ�� ��/���� enum
    off,on
*/
enum eCursorOnOff
{
    off = 0,
    on = 1
};

/*
on Ȥ�� off�� ������ ���� Ŀ���� ������ �� �ִ�.
*/
void cursor(enum eCursorOnOff c)
{                         // �˻��ؼ� ������
    Curinfo.dwSize = 1;   // Ŀ�� ũ��
    Curinfo.bVisible = c; // Ŀ�� ���̱� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}
/*
    ������ �߿� �Է��ϸ� �����ϴ� �Լ� ����  /  �˻��ؼ� ������
    ��ǻ�� ��縶�� ������ ���� �ٸ��� ����� �� �ֽ�
*/
void delay(int delayValue)
{
    for (int i = 0; i < delayValue; i++)
    {
        // windos.h�� ���Ե� �Լ�  /  �� �Լ��� �ڰ� ���� ���� �Է��� �޾ƹ���  /  �ǵ��� �ٸ�
        Sleep(5);
        if (_kbhit())
            while (_getch() == '\0')
                ; // Ű���� �Է��� ���� �� �Է°��� �ΰ��� �� ���� �ݺ�  /  �Է°��� ���شٰ� ���� ��
    }
}

//******************************************************************************************************
//						����
//******************************************************************************************************

/*
    ���� �̸������ص� Enum

        linefont: ��� ���, ���� �Ķ����� ����
        backg: ��� ���, ���� �������� ����
        resetting: ��� ���, ���� ȸ������ ����
        hpfont: ���ڻ��� ���ѻ������� ����
        hpbar: ���, ���� ���ѻ������� ����
        mpfont: ���ڸ� ���ѿ������� ����
        mpbar: ���, ���� ���ѿ������� ����
        brackfont: ���ڸ� �������� ����
        expfont: ���ڸ� ������� ����
        expbar: ���, ���� ������� ����
        winfont: ��� �����Ķ�, ���� �������
        defont: ��� ���ѻ���, ���� ����
        pofont: 0xB1
        gofont: 0xE6
        mefont: 0x8F
        infont: 0x2F
*/
enum eColorName
{
    linefont = 0x71,  // ��� ���, ���� �Ķ����� ����
    backg = 0x70,     // ��� ���, ���� �������� ����
    resetting = 0x88, // ��� ���, ���� ȸ������ ����
    hpfont = 0x7C,    // ���ڻ��� ���ѻ������� ����
    hpbar = 0xCC,     // ���, ���� ���ѻ������� ����
    mpfont = 0x79,    // ���ڸ� ���ѿ������� ����
    mpbar = 0x99,     // ���, ���� ���ѿ������� ����
    brackfont = 0x70, // ���ڸ� �������� ����
    expfont = 0x76,   // ���ڸ� ������� ����
    expbar = 0x66,    // ���, ���� ������� ����
    winfont = 0x9F,   // ��� �����Ķ�, ���� �������
    defont = 0xC0,    // ��� ���ѻ���, ���� ����
    pofont = 0xB1,
    gofont = 0xE6,
    mefont = 0x8F,
    infont = 0x2F
};

/*
    ������ �����ϸ� �ش��ϴ� ������ ���ڸ� �����ش�.

        ����  /  enum���� �̸� �����ϵ� �͸� ��� �����ϰ� �����غ�

            linefont: ��� ���, ���� �Ķ����� ����
            backg: ��� ���, ���� �������� ����
            resetting: ��� ���, ���� ȸ������ ����
            hpfont: ���ڻ��� ���ѻ������� ����
            hpbar: ���, ���� ���ѻ������� ����
            mpfont: ���ڸ� ���ѿ������� ����
            mpbar: ���, ���� ���ѿ������� ����
            brackfont: ���ڸ� �������� ����
            expfont: ���ڸ� ������� ����
            expbar: ���, ���� ������� ����
            winfont: ��� �����Ķ�, ���� �������
            defont: ��� ���ѻ���, ���� ����
            pofont: 0xB1
            gofont: 0xE6
            mefont: 0x8F
            infont: 0x2F
*/
void textcolor(enum eColorName color)
{ // �ܼ�â���� ���ڻ� �������ִ� �Լ�, �˻��ؼ� ������
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//******************************************************************************************************
//						���� ���
//******************************************************************************************************

/*
    Ŀ�� �̵� �κ� �Լ�, �˻�
    ��ǥ��(x,y) �����ؼ� �����̰� ����
*/
void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printfCC(char input[], int colorName)
{
    textcolor(colorName);
    printf("%s", input);
    textcolor(backg);
}
void printfNC(int input, int colorName)
{
    textcolor(colorName);
    printf(" %d ", input);
    textcolor(backg);
}

void printfXY(char input[], int x, int y)
{
    gotoxy(x, y);
    printf("%s", input);
}

void printfCCXY(char input[], int colorValue, int x, int y)
{
    gotoxy(x, y);
    textcolor(colorValue);
    printf("%s", input);
    textcolor(backg);
}
void printfNCXY(int input, int colorValue, int x, int y)
{
    gotoxy(x, y);
    textcolor(colorValue);
    printf("%d", input);
    textcolor(backg);
}

void printBlink(int x, int y, int i, int colorValue)
{
    gotoxy(x, y);
    for (int k = 0; k < i; k++)
        printfCC(" ", colorValue);
}

//******************************************************************************************************
//						ȭ�� �ʱ�ȭ
//******************************************************************************************************

/*
    ȭ�� �ʱ�ȭ �Լ�
    TYPE
    N:������, R:������, A:���
*/
void ResetScreen(int n, char type)
{
    gotoxy(0, 0);

    // ȭ�� ������ �ʱ�ȭ		/	ȭ�� ���� �ٺ��� n��° �ٱ��� �������� ä��
    if (type == 'N')
    {
        for (int i = 0; i < n; i++)
        {
            textcolor(resetting);
            gotoxy(0, i);
            printf("                                                                                \n");
            textcolor(backg);
            gotoxy(0, i - 2);
            printf("                                                                                \n");
            Sleep(1);
            delay(1);
        }
        textcolor(backg);
        for (int i = n - 2; i > 0; i--)
        {
            gotoxy(0, i);
            printf("                                                                                \n");
            gotoxy(0, i - 2);
            printf("                                                                                \n");
        }
    }
    // ȭ�� ���������ʱ�ȭ		/	n �ٺ��� ó�� �ٱ��� �������� ä��
    else if (type == 'R')
    {
        for (int i = n - 1; i > 0; i--)
        {
            textcolor(resetting); // ���߰� ȸ��
            gotoxy(0, i - 2);
            printf("                                                                                \n");
            textcolor(backg); // ���߰� ���
            gotoxy(0, i);
            printf("                                                                                \n");
            Sleep(1);
            delay(1);
        }
        textcolor(backg);
        for (int i = n - 1; i > 0; i--)
        {
            gotoxy(0, i - 2);
            printf("                                                                                \n");
            gotoxy(0, i);
            printf("                                                                                \n");
        }
    }
    // ��� �ʱ�ȭ
    else if (type == 'A')
    {
        textcolor(backg);
        for (int i = n; i > 0; i--)
        {
            gotoxy(0, i);
            printf("                                                                                \n");
        }
    }

    gotoxy(0, 0);
}

//******************************************************************************************************
//						�� ���
//******************************************************************************************************

// x, y ��ǥ�� �޾Ƽ� �� ��ġ���� ���������� i��ŭ �� ����ϱ�
void line(int x, int y, int i)
{
    for (int k = 0; k < i; k++)
    {
        printfCCXY("��", linefont, x + k, y);
    }
}

/*
    x, y ��ǥ�� �޾Ƽ� �� ��ġ���� �Ʒ��� i��ŭ �� ����ϱ�, d�� �������� ���۰� ���� ����
    ����: l. L
    ������: r, R
*/
void Dline(int x, int y, int i, char d)
{

    for (int kk = 0; kk < 2; kk++)
    {
        if (d == 'l' || d == 'L')
            printfCCXY("�� ", linefont, x, y);
        if (d == 'r' || d == 'R')
            printfCCXY("�� ", linefont, x, y);

        for (int k = 1; k < i + 1; k++)
        {
            printfCCXY("�� ", linefont, x, y + k);
        }

        if (d == 'l' || d == 'L')
            printfCCXY("�� ", linefont, x, y + i + 1);
        if (d == 'r' || d == 'R')
            printfCCXY("�� ", linefont, x, y + i + 1);
    }
}

/*
    x, y ��ǥ�� �޾Ƽ� �� ��ġ���� height��ŭ
    ��, �Ʒ� �� �߱�
*/
void lineLine(int x, int y, int height)
{
    line(x, y, 80);
    line(x, y + height, 80);
}

/*
    x, y ��ǥ�� �޾Ƽ� �� ��ġ���� height�� width��ŭ
    �ڽ� ��� ���߱�
*/
void boxLine(int x, int y, int height, int width)
{
    line(x, y, width);
    line(x, y + height, width);
    Dline(x, y, height - 1, 'L');
    Dline(x + width, y, height - 1, 'R');
}
