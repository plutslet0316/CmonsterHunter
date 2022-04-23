/*****************************************************************************************

                                    몬스터를 잡아라


    완성된 것 : 전투 인터페이스, 몬스터와의 전투, 행동 infont, 포션과 골드


                                                                    programmed by plutslet0316
                                                                                    2022.04.24

*****************************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "monster.h"
#include "utility.h"

//		키보드 값. 검색해서 가져옴
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define SPACE 32

int maxhealthP; // 내 최대 체력
int healthP;    // 내 현재 체력
int maxmanaP;   // 내 최대 마력		/  아직 고민중
int manaP;      // 내 현재 마력
int damage;     // 공격력
int defense;    // 방어력				/  아직 고민중
int speed;      // 속도				/  아직 고민중
int level;      // 레벨
int expP;       // 경험치
int potion;     // 포션
int gold;       // 골드

int ky;           //	위아래 입력 값
int menuType = 0; // 메뉴 설정
int menuPosY = 1; // menu 위아래 움직임 초기 좌표		/  해당 값이 선택 값이 됨
int menuPosX = 1; // menu	좌우  움직임 초기 좌표		/  해당 값이 선택 값이 됨
int settingPosY = 1;
int againSelect = 1;   // 다시하기 값 받기
int runawaySelect = 0; // 도망가기 값
int exitSelect = 0;    // 종료 값
int Select;            // 현재 선택 값
int wdResult = 0;      // 승패결과  /  초기 : 0  /  승리 : 1  /  패배 2

char menuString[4][2][31] = { //	메뉴  /  최대 30바이트까지 받고 여유로 1바이트 남길 예정임 혹시 몰라서
    {{"공격"}, {"적을 공격합니다."}},
    {{"강한 공격 (마력 소모 : 10)"}, {"적을 강하게 공격합니다."}},
    {{"포션 사용"}, {"체력과 마력을 50 회복합니다."}},
    {{"도망가기"}, {"몬스터에게서 도망칩니다."}}};

char settingString[3][31] = {
    //	설정
    {"계속하기"},
    {"메뉴 방식 설정"},
    {"종료"},
};

char menuTypeSettingString[2][31] = {
    // 메뉴 타입 설정
    {"이전 위치부터 선택하기"},
    {"항상 첫번째부터 선택하기"},
};

char exitMenuString[2][31] = {
    {"네"},
    {"아니요"},
};

//******************************************************************************************************
//						몬스터
//******************************************************************************************************

int mHealth; // 몬스터 체력
int mMana;   // 몬스터 마력

//******************************************************************************************************
//						함수 선언
//******************************************************************************************************

void monsterSelect();
void bettleSelect();
// 내 상태창
void statusVar(int x, int y, int health, int mana);
void healthVar(int x, int y, int health, int maxhealth);
void manaVar(int x, int y, int mana, int maxmana);
void expVar(int x, int y);
// 몬스터 상태창
void monsterVar(int x, int y, int health, int mana);
void monsterHealthVar(int x, int y, int health, int maxhealth);
void monsterManaVar(int x, int y, int mana, int maxmana);
// 메뉴 이동 관련
int inputMoveY(int x, int y, int menuCount, char output[][2][31]);
void inputMoveX(int x, int y, int i, int xPos);
// 전투 메뉴
int menuVar(int x, int y, int i);
int runawayVar(int x, int y, int i);
void runawayMenu(int y, int i);
// 승패결과
void wdText(int result);
int resultVar(int x, int y, int i, int result);
void winMenu(int y, int i);
void defeatMenu(int y, int i);
void rewardVar(int x, int y, int i);
void levelUp(int x, int y, int i);
// 종료
int settingMoveY(int x, int y, int menuCount, int menuPos, char output[][31]);
void settingVar(int x, int y, int i);
int settingMenu(int x, int y, int i);
int menuTypeMenu(int x, int y, int i);
int exitMenu(int x, int y, int i);

//******************************************************************************************************
//						필요 함수
//******************************************************************************************************

void statusReset()
{ // 내 정보 초기 설정
    maxhealthP = 50;
    healthP = maxhealthP;
    maxmanaP = 50;
    manaP = maxmanaP;
    damage = 10;
    defense = 10;
    speed = 10;
    level = 1;
    expP = 0;
    potion = 3;
    gold = 10;
}

//******************************************************************************************************
//						메인
//******************************************************************************************************

int main()
{
    system("mode con cols=80 lines=36"); // 화면 크기 조정
    system("color 72");                  // 화면 색 조정  /  16진수로 입력
    system("title 메뉴 이동 : 화살표 / 선택 : 엔터, 스페이스바 / 설정 및 종료 : ESC");
    system("cls"); // 화면 초기화

    cursor(off);                         // 커서 끄기
    printfXY("몬스터를 잡아라", 32, 15); // 임시 제목
    printfXY("불러오는 중", 34, 18);
    printfXY("programmed by plutslet0316", 45, 27);
    delay(100); // 입력 없는 딜레이

    srand((unsigned)time(NULL));

    statusReset();

    do
    {
        delay(35);

        monsterSelect();

        ResetScreen(35, 'R');
        system("cls");
        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);

        wdResult = 0; // 승패결과값 0으로 초기화

        while (wdResult == 0)
        {                      // 승패 결정 나면 나가짐
            runawaySelect = 0; // 도망가기값 0으로 초기화

            bettleSelect(); // 전투 부분 함수

            if (runawaySelect == 1)
                break; // 도망 - while문만 나감 do while 안 나감

            if (exitSelect == 1)
            { // 종료 - 네 선택시 Select변수를 1로 바꾸고 밑에 do while보면 그것도 나가짐
                Select = 1;
                break;
            }

            if (mHealth <= 0)
                wdResult = 1; // 몬스터 체력이 없을 때		/  승리 값은 1
            if (healthP <= 0)
                wdResult = 2; // 내 체력이 없을 때			/  패배 값은 2

            switch (wdResult)
            {
            case 1:
                switch (resultVar(5, 5, 5, wdResult))
                { // 승패결과 창으로 넘어가고 거기서 받은 값을 스위치 문에 적용
                case 1:
                    Select = 0;
                    break;
                case 2:
                    Select = 1;
                    break;
                }
                break;
            case 2:
                switch (resultVar(5, 5, 5, wdResult))
                {       // 승패결과 창으로 넘어가고 거기서 받은 값을 스위치 문에 적용
                case 1: // 휴식
                    if (healthP == 0)
                    {
                        if (gold >= 10)
                        { // 골드가 있으면 모두 회복 없으면 일부 회복
                            healthP = maxhealthP;
                            manaP = maxmanaP;
                            gold -= 10;
                        }
                        else
                        {
                            healthP = maxhealthP / 8;
                            manaP += maxmanaP / 8;
                        }
                    }
                    break;
                case 2:
                    healthP = maxhealthP / 8;
                    manaP += maxmanaP / 8;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

        }                  // while문 끝
    } while (Select == 0); // 0이 아니게 되면 나가짐.

    system("cls");

    for (int i = 10; i <= 13; i++) // 선 위쪽 반복 출력
        line(i, i, 80);
    for (int i = 17; i <= 20; i++)
        line(i + 50, i, 80);

    printfXY("게임을 종료합니다.", 30, 15);
    printfXY("programmed by plutslet0316", 30, 16);

    gotoxy(0, 33);

    system("pause");
}

//******************************************************************************************************
//						몬스터 선택
//******************************************************************************************************

void monsterSelect()
{ // 숫자가 아닌 직접 고르는 방식으로 개선한다면 좋을 것 같다.
    ResetScreen(35, 'N');
    system("cls");

    // 선부터 출력
    lineLine(0, 5, 20);
    boxLine(5, 9, 4, 70);

    printfXY("어떤 몬스터와 싸울 지 숫자로 선택하십시오.", 15, 7);
    printfXY("1. 슬라임		2. 변종 버섯		3. 변종 쥐", 10, 10);
    printfXY("4. 변종 큰 쥐		5. 그루터기", 10, 12);

    printfXY("########\t\b목록 이외의 값을 입력하면 기본 몬스터가 선택됩니다.", 2, 15);
    printfXY("########\t\b처음은 슬라임이지만 이전에 선택한 몬스터가 있으면", 2, 16);
    printfXY("########\t\b그 몬스터가 기본 값으로 설정 됩니다.", 2, 17);

    for (int i = 0; i < 3; i++)
    { // 오른쪽에 #을 3줄 출력
        printfXY("########", 70, 15 + i);
    }

    // 작은 네모
    boxLine(30, 20, 2, 14);

    // 커서 위치
    printfXY("           ", 33, 21);
    printfXY(monster[m].name, 33, 21);
    gotoxy(33 + strlen(monster[m].name), 21);
    cursor(on); // 커서 보이기 / 위에 만들어 둔 함수

    int mSelect = 0;
    if (mSelect = _kbhit())
        ;                     // 키보드 입력시 이상한 값 제거  /  키보드 키의 값이 제대로 안 들어옴.
    mSelect = _getch() - '0'; // getch()로 입력받은 것은 전부 문자다. 이를 숫자로 바꾸기 위해선 문자 '0'을 빼줘야 한다.
    cursor(off);              // 커서 없애기 / 위에 만들어 둔 함수
    switch (mSelect)
    {
    case 1:
        m = slime;
        break;
    case 2:
        m = mushroom;
        break;
    case 3:
        m = mice;
        break;
    case 4:
        m = bigmice;
        break;
    case 5:
        m = stump;
        break;
    default:
        break;
    }

    printfXY("           ", 33, 21);
    printfXY(monster[m].name, 33, 21);
    delay(100);

    mHealth = monster[m].maxHealth;
    mMana = monster[m].maxMana;
}

//******************************************************************************************************
//						전투 선택
//******************************************************************************************************

void bettleSelect()
{
    int input;

    input = menuVar(42, 19, 9); // input에 메뉴 선택값 넣음

    printBlink(0, 14, 80, backg);
    printBlink(0, 15, 80, backg);

    delay(100);

    if (input != 4 && input != 0) // 읽은 값이 도망가기와 설정이 아니면
        printBlink(1, 14, 78, mefont);

    delay(25);

    int selectCount = 0; // 증가되면 몬스터 행동 스킵
    int cRandom;
    int mRandom;

    int cDamage = damage;
    int mDamage = monster[m].damage;

    cRandom = rand() % 3;
    switch (cRandom)
    {
    case 1:
        cDamage = damage + (((rand() % damage) / 5) + 1);
        break;
    case 2:
        cDamage = damage - (((rand() % damage) / 5) + 1);
        break;
    case 0:
        cDamage = damage;
        break;
    default:
        break;
    }

    mRandom = rand() % 3;
    switch (mRandom)
    {
    case 1:
        mDamage = monster[m].damage + (((rand() % monster[m].damage) / 5) + 1);
        break;
    case 2:
        mDamage = monster[m].damage - (((rand() % monster[m].damage) / 5) + 1);
        break;
    case 0:
        mDamage = monster[m].damage;
        break;
    default:
        break;
    }

    switch (input)
    {
    case 1: //		(현재)공격
        textcolor(mefont);
        printfXY(monster[m].name, 5, 14);
        printf("(을)를 공격했습니다. ");
        delay(100);
        mHealth -= cDamage; // 내가 데미지 입힘
        if (mHealth <= 0)
            mHealth = 0; // 0이하로 떨어지면 0으로 고정
        printf("%d 만큼 데미지를 입혔습니다.", cDamage);
        break;

    case 2: //		(현재)강한 공격
        if (manaP <= 0 && manaP < 10)
        { // 마력이 적을 때
            printfCCXY("마력이 부족합니다.", mefont, 5, 14);
            selectCount = 1;
        }
        else
        { // 마력이 충분할 때
            cDamage = damage + (cDamage / 2);
            textcolor(mefont);
            printfXY(monster[m].name, 5, 14);
            printf("(을)를 강하게 공격했습니다. ");
            delay(100);
            mHealth -= cDamage; // 마력 있으면 데미지 증가
            manaP -= 10;        // 마력 사용
            if (mHealth <= 0)
                mHealth = 0;
            printf("%d 만큼 데미지를 입혔습니다.", cDamage);
        }
        break;

    case 3: //		(현재)포션 사용
        if (potion > 0)
        {
            printfCCXY("포션을 사용했습니다. ", mefont, 5, 14);
            delay(100);
            potion--;
            healthP += 50; // 내 체력 50회복 및 최대 체력일 시 최대체력으로 고정
            if (healthP >= maxhealthP)
                healthP = maxhealthP;
            manaP += 50; // 내 마력 50회복 및 최대 마력일 시 최대마력으로 고정
            if (manaP >= maxmanaP)
                manaP = maxmanaP;
            printfCC("체력과 마력을 50만큼 회복했습니다.", mefont);
        }
        else
        {
            printfCCXY("포션이 없습니다.", mefont, 5, 14);
            selectCount = 1;
        }
        break;

    case 4: //		(현재)도망가기기
        selectCount = 1;
        switch (runawayVar(5, 5, 2))
        {                      // 여기서 다시 한번 물음  /  정말 도망가시겠습니까?
        case 1:                // 네
            runawaySelect = 1; // 도망가기 값 1로 설정
            break;
        case 2: // 아니요
            runawaySelect = 0;
            ResetScreen(19, 'R');              // 윗 화면 반대로 정리
            monsterVar(20, 4, mHealth, mMana); // 몬스터 상태창 출력
            break;
        default:
            break;
        }
        break;

    case 0:
        settingVar(5, 5, 1);
        selectCount = 1;
        break;
    default:
        break;
    }

    textcolor(backg);

    if (runawaySelect == 0)
    {
        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);
    }

    if (selectCount == 0)
    {
        delay(100);

        printBlink(1, 15, 78, mefont);

        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);

        delay(25);

        if (mHealth > 0)
        {

            mRandom = rand() % 3 + 1;
            switch (mRandom)
            {
            case 1:
                textcolor(mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(이)가 공격해옵니다. ");
                delay(100);
                healthP -= mDamage; // 내가 데미지 받음
                if (healthP <= 0)
                    healthP = 0; // 0이하로 떨어지면 0으로 고정
                printf("%d 만큼 데미지를 입었습니다.", mDamage);
                break;
            case 2:
                textcolor(mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(이)가 강하게 공격해옵니다. ");
                delay(100);

                if (mMana <= 0 && mMana < (monster[m].maxMana / 10) - 5)
                    healthP -= mDamage; // 마력 없거나 적으면 그냥 데미지
                else
                {
                    mDamage = monster[m].damage + (mDamage / 2);
                    healthP -= mDamage;                     // 마력 있으면 데미지 증가
                    mMana -= (monster[m].maxMana / 10) - 5; // 마력 사용
                }
                if (healthP <= 0)
                    healthP = 0; // 0이하로 떨어지면 0으로 고정
                printf("%d 만큼 데미지를 입었습니다.", mDamage);
                break;

            case 3:
                textcolor(mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(이)가 휴식을 취했습니다. ");
                delay(100);

                mMana += mDamage;
                if (mMana >= monster[m].maxMana)
                    mMana = monster[m].maxMana;

                mHealth += mDamage;
                if (mHealth >= monster[m].maxHealth)
                    mHealth = monster[m].maxHealth;
                printf("체력과 마력을 %d 만큼 회복했습니다.", mDamage);
                break;

            default:
                break;
            }
            textcolor(backg);

            monsterVar(20, 4, mHealth, mMana);
            statusVar(0, 19, healthP, manaP);
        }
        else
        {
            printfCCXY(monster[m].name, mefont, 5, 15);
            printfCC("(이)가 쓰러졌습니다. ", mefont);
        }
    }
}

//******************************************************************************************************
//					내 상태창
//******************************************************************************************************

void statusVar(int x, int y, int health, int mana)
{ // x, y값 받아서 그 위치에 상태창 표시
    boxLine(x, y, 10, 39);

    printfXY("LV. ", x + 4, y + 2);
    printf("%d", level);
    gotoxy(x + 17, y + 2);
    textcolor(pofont);
    printf(" P : %3d ", potion);
    printfCC(" ", backg);
    textcolor(gofont);
    printf(" G : %3d ", gold);
    textcolor(backg);

    healthVar(x + 2, y + 4, health, maxhealthP);
    manaVar(x + 2, y + 7, mana, maxmanaP);
    expVar(x, y + 11);
}

void healthVar(int x, int y, int health, int maxhealth)
{ // 체력 부분 출력

    printfCCXY("  체력 : ", hpfont, x, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)health / maxhealth) * 25) // 현재 체력의 비율을 구함
            printfCC("|", hpbar);
        else
            printfCC("|", 0);
    }

    gotoxy(x + 16, y + 1);
    textcolor(hpfont);
    printf("%3d / %3d", maxhealth, health);
    textcolor(backg);
}

void manaVar(int x, int y, int mana, int maxmana)
{ // 마력 부분 출력

    printfCCXY("  마력 : ", mpfont, x, y);

    if (mana == 0)
    {
        printfCC("마력을 회복하십시오", 11);
    }
    else
    {
        for (int i = 0; i < 25; i++)
        {
            if (i < ((float)mana / maxmana) * 25)
            { // 현재 마력의 비율을 구함
                printfCC("|", mpbar);
            }
            else
            {
                printfCC("|", 0);
            }
        }
    }

    gotoxy(x + 16, y + 1);
    textcolor(mpfont);
    printf("%3d / %3d", maxmana, mana);
    textcolor(backg);
}

void expVar(int x, int y)
{ // x, y값 받아서 그 위치에 상태창 표시

    boxLine(x, y, 5, 78);

    printfCCXY("경험치", brackfont, 37, y + 1);

    gotoxy(x + 2, y + 3);
    for (int i = 0; i < 75; i++)
    {
        if (i < ((float)expP / (25 * level)) * 75)
        { // 현재 경험치의 비율을 구함
            printfCC("|", expbar);
        }
        else
        {
            printfCC("|", 0);
        }
    }
    gotoxy(35, y + 4);
    textcolor(brackfont);
    printf("%3d / %3d", expP, (25 * level));
}

//**********************************
//			몬스터 출력
//**********************************

void monsterVar(int x, int y, int health, int mana)
{ // x, y값 받아서 그 위치에 상태창 표시
    boxLine(x + 1, y, 8, 39);

    gotoxy(x + 3, y + 1);
    printf("[ %s ] %s   LV. %d  ", monster[m].grade, monster[m].name, monster[m].level); // 선택 몬스터 기본 정보 출력

    monsterHealthVar(x + 2, y + 3, health, monster[m].maxHealth); // 선택 몬스터 체력 표시
    monsterManaVar(x + 2, y + 6, mana, monster[m].maxMana);       // 선택 몬스터 마나 표시
}

void monsterHealthVar(int x, int y, int health, int maxhealth)
{ // 몬스터 체력 부분 출력

    printfCCXY("체력 : ", hpfont, x + 2, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)health / maxhealth) * 25)
        { // 현재 체력의 비율을 구함
            printfCC("|", hpbar);
        }
        else
        {
            textcolor(0); // 검정으로 바꿈
            printfCC("|", 0);
        }
    }

    gotoxy(x + 17, y + 1);
    textcolor(hpfont);
    printf("%3d / %3d", maxhealth, health);
    textcolor(backg);
}

void monsterManaVar(int x, int y, int mana, int maxmana)
{ // 몬스터  마력 부분 출력
    printfCCXY("마력 : ", mpfont, x + 2, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)mana / maxmana) * 25)
        { // 현재 마력의 비율을 구함
            printfCC("|", mpbar);
        }
        else
        {
            printfCC("|", 0);
        }
    }

    gotoxy(x + 17, y + 1);
    textcolor(mpfont);
    printf("%3d / %3d", maxmana, mana);
    textcolor(backg);
}

//**********************************
//			메뉴 이동
//**********************************

int inputMoveY(int x, int y, int menuCount, char output[][2][31])
{ // x, y 위치에 있는 i개 만큼의 output 메뉴바에서 위아래로 움직이는 부분,
    int input;
    int exitSelect = 0;
    int i = menuCount;

    if (menuType == 1)
        menuPosY = 1; // 타입 1일 때는 항상 1번째에 커서가 있음  /  설정

    do
    {
        for (int i = 0; i < menuCount; i++)
        { // 현재 메뉴 위치에 띄어쓰기 하나 넣기
            printfXY("                             ", x + 4, y + (i * 2) + 2);
            if (menuPosY == i + 1)
            {                                                   // 현재 위치를 묻는 질문
                                                                //				gotoxy(x + 4, y + (i * 2) + 2);
                printfXY(output[i][0], x + 5, y + (i * 2) + 2); // 현재 메뉴 한칸 띄어쓰고 출력
                textcolor(infont);
                printfXY("                              ", x + 1, y - 1);
                printfXY(output[i][1], x + 2, y - 1); // 메뉴 infont 출력
                textcolor(backg);
            }
            else
                printfXY(output[i][0], x + 4, y + (i * 2) + 2);
        }

        ky = y + (menuPosY * 2);
        printfXY("▶", x, ky);

        if (input = _kbhit())
            ;             // 키보드 입력시 이상한 값 제거  /  안 하면 진짜로 이상한 값이 들어옴
        input = _getch(); // 키보드 입력값 받음

        switch (input)
        {
        case UP: // 키보드 위 누르면 위로 2칸 이동
            if (ky > y + 2)
            {
                printfXY("  ", x, ky);
                ky -= 2;
                menuPosY--;
            }
            else
            {
                printfXY("  ", x, ky);
                menuPosY = i;
            }
            break;
        case DOWN: // 키보드 아래 누르면 아래로 2칸 이동
            if (ky < y + i * 2)
            {
                printfXY("  ", x, ky);
                ky += 2;
                menuPosY++;
            }
            else
            {
                printfXY("  ", x, ky);
                menuPosY = 1;
            }
            break;
        case ESC:
            exitSelect = 1; // ESC 누르면 1로 바꿈  /  기본값 0
            printfXY("  ", x, ky);
            break;
        default:
            printfXY("  ", x, ky);
            break;
        }
    } while (input != ENTER && input != SPACE && input != ESC); // 엔터 혹은 스페이스 혹은 ESC 누르면 반복 종료
    printfXY("                             ", x + 4, y + (menuPosY * 2));
    printfXY(output[menuPosY - 1][0], x + 4, y + (menuPosY * 2));

    if (exitSelect == 1) // 나가는 선택이 1일 경우 0을 호출한 곳에 돌려줌  /  아니면 메뉴의 현재 위치 값 1 ~ 4
        return 0;
    else
        return menuPosY;
}

//****************	위 아래 형식이 조금 다른 것 같다. ****************
//	위는 메뉴까지 출력하고, 아래는 화살표만 출력해서 다르다.

void inputMoveX(int x, int y, int i, int xPos)
{                    // x, y 위치에 선택 i 만큼의 선택지에 l위치에 화살표만 출력
    menuPosX = xPos; // 위치 받아서 초기화 시킴

    int input;
    int kx;
    if (menuPosX == 1) // 현재는 선택지가 2개 뿐이라 이렇게 해둠  /  많아지면 스위치로 전환
        kx = x;
    else
        kx = x * 2;

    do
    {
        printfXY("▶", kx, y);

        if (input = _kbhit())
            ;             // 키보드 입력시 이상한 값 제거  /  키보드 키의 값이 제대로 안 들어옴.
        input = _getch(); // 키보드 입력값 받음

        switch (input)
        {

        case LEFT:
            if (menuPosX > 1)
            {
                printfXY("  ", kx, y);
                kx = x;
                menuPosX--;
            }
            else
            {
                printfXY("  ", kx, y);
                kx = x * 2;
                menuPosX++;
            }
            break;
        case RIGHT:
            if (menuPosX < i)
            {
                printfXY("  ", kx, y);
                kx = x * 2;
                menuPosX++;
            }
            else
            {
                printfXY("  ", kx, y);
                kx = x;
                menuPosX--;
            }
            break;
        default:
            break;
        }
    } while (input != ENTER && input != SPACE);
}

//**********************************
//			메뉴창
//**********************************

int menuVar(int x, int y, int i)
{
    line(x, y, 35);
    line(x, y + i + 1, 35);
    Dline(x - 1, y, i, 'L');
    Dline(x + 35, y, i, 'R');

    return inputMoveY(x + 2, y, 4, menuString); // 선택한 메뉴값 돌려줌
}

int runawayVar(int x, int y, int i)
{
    ResetScreen(19, 'N'); // 상태창 바로 위까지 초기화
    line(0, y, 80);
    line(0, y + i, 80);
    printfXY("정말 도망가시겠습니까?", x, y + 1);
    delay(25);
    settingMoveY(x + 10, y + 2, 2, 2, exitMenuString);
    return settingPosY;
}

void runawayMenu(int y, int i)
{ // 80을 i만큼 나누는 부분은 사실 안 넣어도 되는 부분임
    printfXY("네", 80 / i - 14, y);
    printfXY("아니요", (80 / i - 16) * 2, y);
    delay(25);
    inputMoveX(80 / i - 18, y, 2, 2);
}

//**********************************
//			승패
//**********************************

// 아스키 아트  /  검색해서 가져옴  /  영문을 아트로 만드는 사이트 : http://patorjk.com/software/taag/
// 모습은 이상해도 출력은 제대로 됨
void winText()
{
    char winText[7][39] = {
        {":::       ::: ::::::::::: ::::    :::"},
        {":+:       :+:     :+:     :+:+:   :+:"},
        {"+:+       +:+     +:+     :+:+:+  +:+"},
        {"+#+  +:+  +#+     +#+     +#+ +:+ +#+"},
        {"+#+ +#+#+ +#+     +#+     +#+  +#+#+#"},
        {" #+#+# #+#+#      #+#     #+#   #+#+#"},
        {"  ###   ###   ########### ###    ####"},
    };

    for (int k = 0; k < 7; k++)
    {
        gotoxy(20, 5 + k);
        char *xText = winText[k];
        for (int kk = 0; kk < (int)strlen(winText[k]); kk++)
        {
            if (winText[k][kk] == ' ')
                textcolor(backg); // 공백은 배경색으로
            else
                textcolor(winfont);       // 공백 아니면 winfont 색으로  /  배경 연한파랑  /  글자 흰색
            printf("%c", winText[k][kk]); // 글자 출력
        }
    }
}

void defeatText()
{
    char defeatText[7][64] = {
        {":::::::::  :::::::::: :::::::::: ::::::::::     ::: :::::::::::"},
        {":+:    :+: :+:        :+:        :+:          :+: :+:   :+:"},
        {"+:+    +:+ +:+        +:+        +:+         +:+   +:+  +:+"},
        {"+#+    +:+ +#++:++#   :#::+::#   +#++:++#   +#++:++#++: +#+"},
        {"+#+    +#+ +#+        +#+        +#+        +#+     +#+ +#+"},
        {"#+#    #+# #+#        #+#        #+#        #+#     #+# #+#"},
        {"#########  ########## ###        ########## ###     ### ###"},
    };

    for (int k = 0; k < 7; k++)
    {
        gotoxy(8, 5 + k);
        char *xText = defeatText[k];
        for (int kk = 0; kk < (int)strlen(defeatText[k]); kk++)
        {
            if (defeatText[k][kk] == ' ')
                textcolor(backg);
            else
                textcolor(defont);
            printf("%c", defeatText[k][kk]);
        }
    }
}

void wdText(int result)
{

    if (result == 1)
        winText();
    else
        defeatText();

    textcolor(backg); // 출력 끝나면 다시 배경색으로

    delay(150); // 승패결과 출력후 기다림
}

int resultVar(int x, int y, int i, int result)
{
    ResetScreen(19, 'N'); // 상태창 바로 위까지 초기화
    wdText(result);
    ResetScreen(19, 'R');

    lineLine(0, y, i);

    switch (result)
    { // 스위치 아니라도 가능  /  if문이라던가 등으로
    case 1:
        rewardVar(x, y, i); // 승리시 보상 획득
        lineLine(0, y, i);
        printfXY("전투에서 승리했습니다.", x, y + 2);        // 앞에서 위치 지정  /  뒤에서 출력
        printfXY("다른 몬스터와 싸우시겠습니까?", x, y + 3); // 앞에서 위치 지정  /  뒤에서 출력
        winMenu(y + 9, 2);
        break;
    case 2:
        lineLine(0, y, i);
        printfXY("전투에서 패배했습니다.", x, y + 2);                               // 앞에서 위치 지정  /  뒤에서 출력
        printfXY("여관에서 휴식을 취하시겠습니까? 10골드가 소모됩니다.", x, y + 3); // 앞에서 위치 지정  /  뒤에서 출력
        defeatMenu(y + 9, 2);
        break;
    default:
        break;
    }
    return menuPosX;
}

void winMenu(int y, int i)
{
    printfXY("네 ", 80 / i - 14, y);
    printfXY("아니요(종료) ", (80 / i - 16) * 2, y);

    inputMoveX(80 / i - 18, y, 2, 1);
}

void defeatMenu(int y, int i)
{
    printfXY("네(모두 회복) ", 80 / i - 19, y);
    printfXY("아니요(일부 회복) ", (80 / i - 20) * 2, y);
    delay(35);
    inputMoveX(80 / i - 22, y, 2, 1);
}

void rewardVar(int x, int y, int i)
{
    lineLine(0, y, i);

    printfXY("떨어져있던 포션 ", x, y + 2);
    printfNC(monster[m].potionDrop, pofont);
    printf("개와 골드 ");
    printfNC(monster[m].goldDrop, gofont);
    printf("개를 주웠습니다.");
    printfXY("경험치를", x, y + 3);
    printfNC(monster[m].exp, expfont);
    printf("만큼 얻었습니다.");

    potion += monster[m].potionDrop;
    gold += monster[m].goldDrop;
    expP += monster[m].exp;

    delay(100);
    gotoxy(x + 15, y + 8);
    system("pause");
    ResetScreen(18, 'A');

    statusVar(0, 19, healthP, manaP);

    levelUp(x, y, i); // 레벨업 한다면 레벨업을 한다.
}

void levelUp(int x, int y, int i)
{
    if (expP >= 25 * level)
    { // 레벨업 부분
        lineLine(0, y, i);

        printfXY("경험치를 모두 채워 당신의 레벨이 한 단계 증가했습니다.", x, y + 2);

        delay(100);
        gotoxy(x + 15, y + 8);
        system("pause"); // 잠시 멈춤
        ResetScreen(18, 'A');

        lineLine(0, y, i);

        expP -= 25 * level;
        gotoxy(x + 29, y + 1);
        printf("Lv. %d -> Lv. %d", level++, level);
        maxhealthP += 10;
        maxmanaP += 10;
        damage += 2;

        gotoxy(x, y + 3);
        printf("최대 체력 %3d -> %3d  /  ", maxhealthP - 10, maxhealthP);
        printf("최대 마력 %3d -> %3d  /  ", maxmanaP - 10, maxmanaP);
        printf("공격력 %2d -> %2d", damage - 2, damage);

        statusVar(0, 19, healthP, manaP); //	상태창 화면에 출력

        delay(150);
        gotoxy(x + 15, y + 8);
        system("pause"); // 잠시 멈춤
        ResetScreen(18, 'A');

        lineLine(0, y, i);

        printfXY("체력과 마력이 모두 회복되었습니다.", x, y + 2);

        healthP = maxhealthP;
        manaP = maxmanaP;
        statusVar(0, 19, healthP, manaP); //	상태창 화면에 출력

        delay(150);
        gotoxy(x + 15, y + 8);
        system("pause"); // 잠시 멈춤
        ResetScreen(18, 'A');
    }
}

//**********************************
//			설정
//**********************************

// 설정 메뉴 전용 움직임 함수  /  위에 거 고쳐 씀
int settingMoveY(int x, int y, int menuCount, int menuPos, char output[][31])
{ // x, y 위치에 있는 i개 만큼의 output 메뉴바에서 위아래로 움직이는 부분,
    int input;
    int exitSelect = 0;
    int i = menuCount;
    settingPosY = menuPos;
    do
    {
        for (int i = 0; i < menuCount; i++)
        { // 현재 메뉴 위치에 띄어쓰기 하나 넣기
            printfXY("                                          ", x + 4, y + (i * 2) + 2);
            if (settingPosY == i + 1)
                printfXY(output[i], x + 5, y + (i * 2) + 2); // 현재 메뉴 한칸 띄어쓰고 출력
            else
            {
                printfXY(output[i], x + 4, y + (i * 2) + 2);
            }
        }

        ky = y + (settingPosY * 2);
        gotoxy(x, ky);
        printf("▶");

        if (input = _kbhit())
            ;             // 키보드 입력시 이상한 값 제거  /  안 하면 진짜로 이상한 값이 들어옴
        input = _getch(); // 키보드 입력값 받음

        switch (input)
        {

        case UP: // 키보드 위 누르면 위로 2칸 이동
            if (ky > y + 2)
            {
                gotoxy(x, ky);
                printf("  ");
                ky -= 2;
                settingPosY--;
            }
            else
            {
                gotoxy(x, ky);
                printf("  ");
                settingPosY = i;
            }
            break;
        case DOWN: // 키보드 아래 누르면 아래로 2칸 이동
            if (ky < y + i * 2)
            {
                gotoxy(x, ky);
                printf("  ");
                ky += 2;
                settingPosY++;
            }
            else
            {
                gotoxy(x, ky);
                printf("  ");
                settingPosY = 1;
            }
            break;
        case ESC:
            settingPosY = 1; // ESC 누르면 1로 바꿈
            printf("  ");

            break;
        default:
            gotoxy(x, ky);
            break;
        }
    } while (input != ENTER && input != SPACE && input != ESC); // 엔터 혹은 스페이스 혹은 ESC 누르면 반복 종료

    return settingPosY;
}

void settingVar(int x, int y, int i)
{
    ResetScreen(35, 'N');
    system("cls");
    switch (settingMenu(5, 5, 2))
    {
    case 1:
        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);
        break;
    case 2:
        switch (menuTypeMenu(5, 5, 2))
        {
        case 1: // 이전 위치
            menuType = 0;
            break;
        case 2: // 항상 첫번째
            menuType = 1;
            break;
        default:
            break;
        }
        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);
        break;
    case 3:
        switch (exitMenu(5, 5, 2))
        {
        case 1: // 네
            exitSelect = 1;
            break;
        case 2: // 아니요
            exitSelect = 0;
            monsterVar(20, 4, mHealth, mMana);
            statusVar(0, 19, healthP, manaP);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

int settingMenu(int x, int y, int i)
{ // 80을 i만큼 나누는 부분은 사실 안 넣어도 되는 부분임
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("설정");
    delay(25);
    settingMoveY(x + 10, y + 4, 3, 1, settingString);
    ResetScreen(35, 'R');
    system("cls");
    return settingPosY;
}

int menuTypeMenu(int x, int y, int i)
{ // 80을 i만큼 나누는 부분은 사실 안 넣어도 되는 부분임
    ResetScreen(35, 'N');
    system("cls");
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("메뉴 방식 설정");
    delay(25);
    settingMoveY(x + 10, y + 4, 2, 1, menuTypeSettingString);
    ResetScreen(35, 'R');
    system("cls");
    return settingPosY;
}

int exitMenu(int x, int y, int i)
{
    ResetScreen(35, 'N');
    system("cls");
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("정말 종료하시겠습니까?");
    delay(25);
    settingMoveY(x + 10, y + 4, 2, 1, exitMenuString);
    ResetScreen(35, 'R');
    system("cls");
    return settingPosY;
}