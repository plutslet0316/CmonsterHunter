/******************************************************************************************************

    *  유틸리티
        - 커서 제어
        - 딜레이
        - 색상지정
        - 글자 출력
        - 화면 초기화
        - 선 출력

******************************************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 커서 관련 함수
/*
    커서 구조체
    관련 사이트 : https://docs.microsoft.com/ko-kr/windows/console/console-cursor-info-str
*/
CONSOLE_CURSOR_INFO Curinfo;

/*
    커서 온/오프 enum
    off,on
*/
enum eCursorOnOff
{
    off = 0,
    on = 1
};

/*
on 혹은 off만 적으면 쉽게 커서를 제어할 수 있다.
*/
void cursor(enum eCursorOnOff c)
{                         // 검색해서 참고함
    Curinfo.dwSize = 1;   // 커서 크기
    Curinfo.bVisible = c; // 커서 보이기 여부
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}
/*
    딜레이 중에 입력하면 무시하는 함수 만들어봄  /  검색해서 참고함
    컴퓨터 사양마다 딜레이 값이 다르게 적용될 수 있슴
*/
void delay(int delayValue)
{
    for (int i = 0; i < delayValue; i++)
    {
        // windos.h에 포함된 함수  /  이 함수는 자고 있을 때도 입력을 받아버림  /  의도랑 다름
        Sleep(5);
        if (_kbhit())
            while (_getch() == '\0')
                ; // 키보드 입력이 있을 때 입력값이 널값일 때 까지 반복  /  입력값을 없앤다고 보면 된
    }
}

//******************************************************************************************************
//						색상
//******************************************************************************************************

/*
    색을 미리지정해둔 Enum

        linefont: 배경 흰색, 글자 파랑으로 변경
        backg: 배경 흰색, 글자 검정으로 변경
        resetting: 배경 흰색, 글자 회색으로 변경
        hpfont: 글자색만 연한빨강으로 변경
        hpbar: 배경, 글자 연한빨강으로 변경
        mpfont: 글자만 연한옥색으로 변경
        mpbar: 배경, 글자 연한옥색으로 변경
        brackfont: 글자만 검정으로 변경
        expfont: 글자만 노랑으로 변경
        expbar: 배경, 글자 노랑으로 변경
        winfont: 배경 연한파랑, 글자 밝은흰색
        defont: 배경 연한빨강, 글자 검정
        pofont: 0xB1
        gofont: 0xE6
        mefont: 0x8F
        infont: 0x2F
*/
enum eColorName
{
    linefont = 0x71,  // 배경 흰색, 글자 파랑으로 변경
    backg = 0x70,     // 배경 흰색, 글자 검정으로 변경
    resetting = 0x88, // 배경 흰색, 글자 회색으로 변경
    hpfont = 0x7C,    // 글자색만 연한빨강으로 변경
    hpbar = 0xCC,     // 배경, 글자 연한빨강으로 변경
    mpfont = 0x79,    // 글자만 연한옥색으로 변경
    mpbar = 0x99,     // 배경, 글자 연한옥색으로 변경
    brackfont = 0x70, // 글자만 검정으로 변경
    expfont = 0x76,   // 글자만 노랑으로 변경
    expbar = 0x66,    // 배경, 글자 노랑으로 변경
    winfont = 0x9F,   // 배경 연한파랑, 글자 밝은흰색
    defont = 0xC0,    // 배경 연한빨강, 글자 검정
    pofont = 0xB1,
    gofont = 0xE6,
    mefont = 0x8F,
    infont = 0x2F
};

/*
    색상값을 지정하면 해당하는 색으로 글자를 보여준다.

        사용법  /  enum으로 미리 지정하둔 것만 사용 가능하게 수정해봄

            linefont: 배경 흰색, 글자 파랑으로 변경
            backg: 배경 흰색, 글자 검정으로 변경
            resetting: 배경 흰색, 글자 회색으로 변경
            hpfont: 글자색만 연한빨강으로 변경
            hpbar: 배경, 글자 연한빨강으로 변경
            mpfont: 글자만 연한옥색으로 변경
            mpbar: 배경, 글자 연한옥색으로 변경
            brackfont: 글자만 검정으로 변경
            expfont: 글자만 노랑으로 변경
            expbar: 배경, 글자 노랑으로 변경
            winfont: 배경 연한파랑, 글자 밝은흰색
            defont: 배경 연한빨강, 글자 검정
            pofont: 0xB1
            gofont: 0xE6
            mefont: 0x8F
            infont: 0x2F
*/
void textcolor(enum eColorName color)
{ // 콘솔창에서 글자색 변경해주는 함수, 검색해서 가져옴
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//******************************************************************************************************
//						글자 출력
//******************************************************************************************************

/*
    커서 이동 부분 함수, 검색
    좌표값(x,y) 지정해서 움직이게 만듬
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
//						화면 초기화
//******************************************************************************************************

/*
    화면 초기화 함수
    TYPE
    N:정방향, R:역방향, A:모두
*/
void ResetScreen(int n, char type)
{
    gotoxy(0, 0);

    // 화면 정방향 초기화		/	화면 시작 줄부터 n번째 줄까지 공백으로 채움
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
    // 화면 역순으로초기화		/	n 줄부터 처음 줄까지 공백으로 채움
    else if (type == 'R')
    {
        for (int i = n - 1; i > 0; i--)
        {
            textcolor(resetting); // 색추가 회색
            gotoxy(0, i - 2);
            printf("                                                                                \n");
            textcolor(backg); // 색추가 흰색
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
    // 모두 초기화
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
//						선 출력
//******************************************************************************************************

// x, y 좌표값 받아서 그 위치에서 오른쪽으로 i만큼 선 출력하기
void line(int x, int y, int i)
{
    for (int k = 0; k < i; k++)
    {
        printfCCXY("─", linefont, x + k, y);
    }
}

/*
    x, y 좌표값 받아서 그 위치에서 아래로 i만큼 선 출력하기, d의 방향으로 시작과 끝을 맺음
    왼쪽: l. L
    오른쪽: r, R
*/
void Dline(int x, int y, int i, char d)
{

    for (int kk = 0; kk < 2; kk++)
    {
        if (d == 'l' || d == 'L')
            printfCCXY("┌ ", linefont, x, y);
        if (d == 'r' || d == 'R')
            printfCCXY("┐ ", linefont, x, y);

        for (int k = 1; k < i + 1; k++)
        {
            printfCCXY("│ ", linefont, x, y + k);
        }

        if (d == 'l' || d == 'L')
            printfCCXY("└ ", linefont, x, y + i + 1);
        if (d == 'r' || d == 'R')
            printfCCXY("┘ ", linefont, x, y + i + 1);
    }
}

/*
    x, y 좌표값 받아서 그 위치에서 height만큼
    위, 아래 선 긋기
*/
void lineLine(int x, int y, int height)
{
    line(x, y, 80);
    line(x, y + height, 80);
}

/*
    x, y 좌표값 받아서 그 위치에서 height와 width만큼
    박스 모양 선긋기
*/
void boxLine(int x, int y, int height, int width)
{
    line(x, y, width);
    line(x, y + height, width);
    Dline(x, y, height - 1, 'L');
    Dline(x + width, y, height - 1, 'R');
}
