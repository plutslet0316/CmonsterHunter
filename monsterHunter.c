/*****************************************************************************************

                                    ���͸� ��ƶ� v.04


    �ϼ��� �� : ���� �������̽�, ���Ϳ��� ����, �ൿ infont, ���ǰ� ���


                                                                    programmed by plutslet0316
                                                                                    2020.12.07

*****************************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  // �ð����� ���� �����
#include <time.h>    // �ð� ��������
#include <windows.h> // �ܼ�â �ٹ̱�
#include <string.h>

//		Ű���� ��. �˻��ؼ� ������
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define SPACE 32

int maxhealthP; // �� �ִ� ü��
int healthP;    // �� ���� ü��
int maxmanaP;   // �� �ִ� ����		/  ���� �����
int manaP;      // �� ���� ����
int damage;     // ���ݷ�
int defense;    // ����				/  ���� �����
int speed;      // �ӵ�				/  ���� �����
int level;      // ����
int expP;       // ����ġ
int potion;     // ����
int gold;       // ���

int ky;           //	���Ʒ� �Է� ��
int menuType = 0; // �޴� ����
int menuPosY = 1; // menu ���Ʒ� ������ �ʱ� ��ǥ		/  �ش� ���� ���� ���� ��
int menuPosX = 1; // menu	�¿�  ������ �ʱ� ��ǥ		/  �ش� ���� ���� ���� ��
int settingPosY = 1;
int againSelect = 1;   // �ٽ��ϱ� �� �ޱ�
int runawaySelect = 0; // �������� ��
int exitSelect = 0;    // ���� ��
int Select;            // ���� ���� ��
int wdResult = 0;      // ���а��  /  �ʱ� : 0  /  �¸� : 1  /  �й� 2

char menuString[4][2][31] = { //	�޴�  /  �ִ� 30����Ʈ���� �ް� ������ 1����Ʈ ���� ������ Ȥ�� ����
    {{"����"}, {"���� �����մϴ�."}},
    {{"���� ���� (���� �Ҹ� : 10)"}, {"���� ���ϰ� �����մϴ�."}},
    {{"���� ���"}, {"ü�°� ������ 50 ȸ���մϴ�."}},
    {{"��������"}, {"���Ϳ��Լ� ����Ĩ�ϴ�."}}};

char settingString[3][31] = {
    //	����
    {"����ϱ�"},
    {"�޴� ��� ����"},
    {"����"},
};

char menuTypeSettingString[2][31] = {
    // �޴� Ÿ�� ����
    {"���� ��ġ���� �����ϱ�"},
    {"�׻� ù��°���� �����ϱ�"},
};

char exitMenuString[2][31] = {
    {"��"},
    {"�ƴϿ�"},
};

//******************************************************************************************************
//						����
//******************************************************************************************************

struct _MonsterIndex
{                   // ���� ���� Ʋ
    char grade[5];  // ���
    char name[11];  // �̸�			/  ���� �̸� ���̰� 10����Ʈ�� Ȥ�� �� ���� 1����Ʈ
    int level;      // ����
    int maxHealth;  // �ִ� ü��
    int maxMana;    // �ִ� ����		/  ���� �����
    int damage;     // ������
    int defense;    // ����			/   ���� �����
    int exp;        // ����ġ
    int potionDrop; // ���� ��� ����
    int goldDrop;   // ��� ��� ����
};

int mHealth; // ���� ü��
int mMana;   // ���� ����

struct _MonsterIndex monster[] = { //	���� ���� ����  /  ��� �� �����
    {"�Ϲ�", "������", 1, 20, 15, 4, 2, 5, 1, 5},
    {"�Ϲ�", "���� ����", 2, 30, 15, 7, 3, 7, 1, 10},
    {"�Ϲ�", "���� ��", 3, 45, 25, 13, 5, 12, 2, 20},
    {"�Ϲ�", "���� ū ��", 4, 60, 30, 16, 6, 20, 3, 35},
    {"����", "�׷��ͱ�", 5, 120, 25, 20, 8, 50, 5, 100}

};

enum MonsterName
{ //	�ڵ� © �� ���� ������ ��� �� �����  /  ���α׷��� ���������� ������ �� ����  /  ��� ��ġ�� ��� ���͸� ���� ��
    slime = 0,
    mushroom,
    mice,
    bigmice,
    stump

};
enum MonsterName m = slime;

//******************************************************************************************************
//						�Լ� ����
//******************************************************************************************************

void monsterSelect();
void bettleSelect();
// ��
void line(int x, int y, int i);
void Dline(int x, int y, int i, char d);
void lineLine(int x, int y, int height);
void boxLine(int x, int y, int height, int width);
// �� ����â
void statusVar(int x, int y, int health, int mana);
void healthVar(int x, int y, int health, int maxhealth);
void manaVar(int x, int y, int mana, int maxmana);
void expVar(int x, int y);
// ���� ����â
void monsterVar(int x, int y, int health, int mana);
void monsterHealthVar(int x, int y, int health, int maxhealth);
void monsterManaVar(int x, int y, int mana, int maxmana);
// �޴� �̵� ����
int inputMoveY(int x, int y, int menuCount, char output[][2][31]);
void inputMoveX(int x, int y, int i, int xPos);
// ���� �޴�
int menuVar(int x, int y, int i);
int runawayVar(int x, int y, int i);
void runawayMenu(int y, int i);
// ���а��
void wdText(int result);
int resultVar(int x, int y, int i, int result);
void winMenu(int y, int i);
void defeatMenu(int y, int i);
void rewardVar(int x, int y, int i);
void levelUp(int x, int y, int i);
// ����
int settingMoveY(int x, int y, int menuCount, int menuPos, char output[][31]);
void settingVar(int x, int y, int i);
int settingMenu(int x, int y, int i);
int menuTypeMenu(int x, int y, int i);
int exitMenu(int x, int y, int i);

//******************************************************************************************************
//						�ʿ� �Լ�
//******************************************************************************************************

// Ŀ�� ���� �Լ�
CONSOLE_CURSOR_INFO Curinfo; // Ŀ�� ����ü  /  ���� ����Ʈ : https://docs.microsoft.com/ko-kr/windows/console/console-cursor-info-str

enum CursorOnOff
{ // ��� �� �����
    off = 0,
    on = 1
};

void cursor(enum CursorOnOff c)
{                         // �˻��ؼ� ������
    Curinfo.dwSize = 1;   // Ŀ�� ũ��
    Curinfo.bVisible = c; // Ŀ�� ���̱� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}

void delay(int delayValue)
{ // ������ �߿� �Է��ϸ� �����ϴ� �Լ� ����  /  �˻��ؼ� ������
    for (int i = 0; i < delayValue; i++)
    {             //  �� �κ��� �������� ���� ��ǻ�� ��縶�� ������ ���� �ٸ� �� ����
        Sleep(5); // windo.h�� ���Ե� �Լ�  /  �� �Լ��� �ڰ� ���� ���� �Է��� �޾ƹ���  /  �ǵ��� �ٸ�
        if (_kbhit())
            while (_getch() == '\0')
                ; // Ű���� �Է��� ���� �� �Է°��� �ΰ��� �� ���� �ݺ�  /  �Է°��� ���شٰ� ���� ��
    }
}

// �� ���� �Լ�
enum ColorName
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
} cN;

void textcolor(int color_number)
{ // �ܼ�â���� ���ڻ� �������ִ� �Լ�, �˻��ؼ� ������
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

//		����  /  16������ �����  /  ���� ���� �ڿ��� ���ڻ�
//
//		����		/  7. ����� ȸ������ ����(�� ���� ����)  /  F. ���� ����� ��¥ ���
//		0. ����		/	1. �Ķ�		/	2. �ʷ�		/	3. ����
//		4. ����		/	5. ����		/	6. ���		/	7. ���
//		8. ȸ��		/	9. �����Ķ�	/	A. �����ʷ�	/	B. ���ѿ���
//		C. ���ѻ���	/	D. ��������	/	E. ���ѳ��	/	F. �������

void gotoxy(int x, int y)
{ // Ŀ�� �̵� �κ� �Լ�, �˻��ؼ� ������	/	��ǥ�� �����ؼ� �����̰� ����
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� ��� ����

void printfCC(char input[], int colorName)
{
    textcolor(colorName);
    printf("%s", input);
    textcolor(cN = backg);
}
void printfNC(int input, int colorName)
{
    textcolor(colorName);
    printf(" %d ", input);
    textcolor(cN = backg);
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
    textcolor(cN = backg);
}
void printfNCXY(int input, int colorValue, int x, int y)
{
    gotoxy(x, y);
    textcolor(colorValue);
    printf("%d", input);
    textcolor(cN = backg);
}

void printBlink(int x, int y, int i, int colorValue)
{
    gotoxy(x, y);
    for (int k = 0; k < i; k++)
        printfCC(" ", colorValue);
}

void reset(int k)
{ // ȭ�� �ʱ�ȭ		/	ȭ�� ���� �ٺ��� k��° �ٱ��� �������� ä��  /  �ٲ۴ٸ� ���� �ٺ��� k���� ��������
    gotoxy(0, 0);
    for (int i = 0; i < k; i++)
    {
        textcolor(cN = resetting);
        gotoxy(0, i);
        printf("                                                                                \n");
        textcolor(cN = backg);
        gotoxy(0, i - 2);
        printf("                                                                                \n");
        Sleep(1);
        delay(1);
    }
    textcolor(cN = backg);
    for (int i = k - 2; i > 0; i--)
    {
        gotoxy(0, i);
        printf("                                                                                \n");
        gotoxy(0, i - 2);
        printf("                                                                                \n");
    }
    gotoxy(0, 0);
}

void Rreset(int k)
{ // ȭ�� ���������ʱ�ȭ		/	k �ٺ��� ó�� �ٱ��� �������� ä��  /  �ٲ۴ٸ� ���� �ٺ��� k���� ��������
    gotoxy(0, 0);
    for (int i = k - 1; i > 0; i--)
    {
        textcolor(cN = resetting); // ���߰� ȸ��
        gotoxy(0, i - 2);
        printf("                                                                                \n");
        textcolor(cN = backg); // ���߰� ���
        gotoxy(0, i);
        printf("                                                                                \n");
        Sleep(1);
        delay(1);
    }
    textcolor(cN = backg);
    for (int i = k - 1; i > 0; i--)
    {
        gotoxy(0, i - 2);
        printf("                                                                                \n");
        gotoxy(0, i);
        printf("                                                                                \n");
    }
    gotoxy(0, 0);
}

void Areset(int k)
{
    gotoxy(0, 0);
    textcolor(cN = backg);
    for (int i = k; i > 0; i--)
    {
        gotoxy(0, i);
        printf("                                                                                \n");
    }
    gotoxy(0, 0);
}

void statusReset()
{ // �� ���� �ʱ� ����
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
//						����
//******************************************************************************************************

int main()
{
    system("mode con cols=80 lines=36"); // ȭ�� ũ�� ����
    system("color 72");                  // ȭ�� �� ����  /  16������ �Է�
    system("title �޴� �̵� : ȭ��ǥ / ���� : ����, �����̽��� / ���� �� ���� : ESC");
    system("cls"); // ȭ�� �ʱ�ȭ

    cursor(off);                         // Ŀ�� ����
    printfXY("���͸� ��ƶ�", 32, 15); // �ӽ� ����
    printfXY("�ҷ����� ��", 34, 18);
    printfXY("programmed by plutslet0316", 45, 27);
    delay(100); // �Է� ���� ������

    srand((unsigned)time(NULL));

    statusReset();

    do
    {
        delay(35);

        monsterSelect();

        Rreset(35);
        system("cls");
        monsterVar(20, 4, mHealth, mMana);
        statusVar(0, 19, healthP, manaP);

        wdResult = 0; // ���а���� 0���� �ʱ�ȭ

        while (wdResult == 0)
        {                      // ���� ���� ���� ������
            runawaySelect = 0; // �������Ⱚ 0���� �ʱ�ȭ

            bettleSelect(); // ���� �κ� �Լ�

            if (runawaySelect == 1)
                break; // ���� - while���� ���� do while �� ����

            if (exitSelect == 1)
            { // ���� - �� ���ý� Select������ 1�� �ٲٰ� �ؿ� do while���� �װ͵� ������
                Select = 1;
                break;
            }

            if (mHealth <= 0)
                wdResult = 1; // ���� ü���� ���� ��		/  �¸� ���� 1
            if (healthP <= 0)
                wdResult = 2; // �� ü���� ���� ��			/  �й� ���� 2

            switch (wdResult)
            {
            case 1:
                switch (resultVar(5, 5, 5, wdResult))
                { // ���а�� â���� �Ѿ�� �ű⼭ ���� ���� ����ġ ���� ����
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
                {       // ���а�� â���� �Ѿ�� �ű⼭ ���� ���� ����ġ ���� ����
                case 1: // �޽�
                    if (healthP == 0)
                    {
                        if (gold >= 10)
                        { // ��尡 ������ ��� ȸ�� ������ �Ϻ� ȸ��
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

        }                  // while�� ��
    } while (Select == 0); // 0�� �ƴϰ� �Ǹ� ������.

    system("cls");

    for (int i = 10; i <= 13; i++) // �� ���� �ݺ� ���
        line(i, i, 80);
    for (int i = 17; i <= 20; i++)
        line(i + 50, i, 80);

    printfXY("������ �����մϴ�.", 30, 15);
    printfXY("programmed by plutslet0316", 30, 16);

    gotoxy(0, 33);

    system("pause");
}

//******************************************************************************************************
//						���� ����
//******************************************************************************************************

void monsterSelect()
{ // ���ڰ� �ƴ� ���� ���� ������� �����Ѵٸ� ���� �� ����.
    reset(35);
    system("cls");

    // ������ ���
    lineLine(0, 5, 20);
    boxLine(5, 9, 4, 70);

    printfXY("� ���Ϳ� �ο� �� ���ڷ� �����Ͻʽÿ�.", 15, 7);
    printfXY("1. ������		2. ���� ����		3. ���� ��", 10, 10);
    printfXY("4. ���� ū ��		5. �׷��ͱ�", 10, 12);

    printfXY("########\t\b��� �̿��� ���� �Է��ϸ� �⺻ ���Ͱ� ���õ˴ϴ�.", 2, 15);
    printfXY("########\t\bó���� ������������ ������ ������ ���Ͱ� ������", 2, 16);
    printfXY("########\t\b�� ���Ͱ� �⺻ ������ ���� �˴ϴ�.", 2, 17);

    for (int i = 0; i < 3; i++)
    { // �����ʿ� #�� 3�� ���
        printfXY("########", 70, 15 + i);
    }

    // ���� �׸�
    boxLine(30, 20, 2, 14);

    // Ŀ�� ��ġ
    printfXY("           ", 33, 21);
    printfXY(monster[m].name, 33, 21);
    gotoxy(33 + strlen(monster[m].name), 21);
    cursor(on); // Ŀ�� ���̱� / ���� ����� �� �Լ�

    int mSelect = 0;
    if (mSelect = _kbhit())
        ;                     // Ű���� �Է½� �̻��� �� ����  /  Ű���� Ű�� ���� ����� �� ����.
    mSelect = _getch() - '0'; // getch()�� �Է¹��� ���� ���� ���ڴ�. �̸� ���ڷ� �ٲٱ� ���ؼ� ���� '0'�� ����� �Ѵ�.
    cursor(off);              // Ŀ�� ���ֱ� / ���� ����� �� �Լ�
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
//						���� ����
//******************************************************************************************************

void bettleSelect()
{
    int input;

    input = menuVar(42, 19, 9); // input�� �޴� ���ð� ����

    printBlink(0, 14, 80, backg);
    printBlink(0, 15, 80, backg);

    delay(100);

    if (input != 4 && input != 0) // ���� ���� ��������� ������ �ƴϸ�
        printBlink(1, 14, 78, mefont);

    delay(25);

    int selectCount = 0; // �����Ǹ� ���� �ൿ ��ŵ
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
    case 1: //		(����)����
        textcolor(cN = mefont);
        printfXY(monster[m].name, 5, 14);
        printf("(��)�� �����߽��ϴ�. ");
        delay(100);
        mHealth -= cDamage; // ���� ������ ����
        if (mHealth <= 0)
            mHealth = 0; // 0���Ϸ� �������� 0���� ����
        printf("%d ��ŭ �������� �������ϴ�.", cDamage);
        break;

    case 2: //		(����)���� ����
        if (manaP <= 0 && manaP < 10)
        { // ������ ���� ��
            printfCCXY("������ �����մϴ�.", mefont, 5, 14);
            selectCount = 1;
        }
        else
        { // ������ ����� ��
            cDamage = damage + (cDamage / 2);
            textcolor(cN = mefont);
            printfXY(monster[m].name, 5, 14);
            printf("(��)�� ���ϰ� �����߽��ϴ�. ");
            delay(100);
            mHealth -= cDamage; // ���� ������ ������ ����
            manaP -= 10;        // ���� ���
            if (mHealth <= 0)
                mHealth = 0;
            printf("%d ��ŭ �������� �������ϴ�.", cDamage);
        }
        break;

    case 3: //		(����)���� ���
        if (potion > 0)
        {
            printfCCXY("������ ����߽��ϴ�. ", mefont, 5, 14);
            delay(100);
            potion--;
            healthP += 50; // �� ü�� 50ȸ�� �� �ִ� ü���� �� �ִ�ü������ ����
            if (healthP >= maxhealthP)
                healthP = maxhealthP;
            manaP += 50; // �� ���� 50ȸ�� �� �ִ� ������ �� �ִ븶������ ����
            if (manaP >= maxmanaP)
                manaP = maxmanaP;
            printfCC("ü�°� ������ 50��ŭ ȸ���߽��ϴ�.", mefont);
        }
        else
        {
            printfCCXY("������ �����ϴ�.", mefont, 5, 14);
            selectCount = 1;
        }
        break;

    case 4: //		(����)���������
        selectCount = 1;
        switch (runawayVar(5, 5, 2))
        {                      // ���⼭ �ٽ� �ѹ� ����  /  ���� �������ðڽ��ϱ�?
        case 1:                // ��
            runawaySelect = 1; // �������� �� 1�� ����
            break;
        case 2: // �ƴϿ�
            runawaySelect = 0;
            Rreset(19);                        // �� ȭ�� �ݴ�� ����
            monsterVar(20, 4, mHealth, mMana); // ���� ����â ���
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

    textcolor(cN = backg);

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
                textcolor(cN = mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(��)�� �����ؿɴϴ�. ");
                delay(100);
                healthP -= mDamage; // ���� ������ ����
                if (healthP <= 0)
                    healthP = 0; // 0���Ϸ� �������� 0���� ����
                printf("%d ��ŭ �������� �Ծ����ϴ�.", mDamage);
                break;
            case 2:
                textcolor(cN = mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(��)�� ���ϰ� �����ؿɴϴ�. ");
                delay(100);

                if (mMana <= 0 && mMana < (monster[m].maxMana / 10) - 5)
                    healthP -= mDamage; // ���� ���ų� ������ �׳� ������
                else
                {
                    mDamage = monster[m].damage + (mDamage / 2);
                    healthP -= mDamage;                     // ���� ������ ������ ����
                    mMana -= (monster[m].maxMana / 10) - 5; // ���� ���
                }
                if (healthP <= 0)
                    healthP = 0; // 0���Ϸ� �������� 0���� ����
                printf("%d ��ŭ �������� �Ծ����ϴ�.", mDamage);
                break;

            case 3:
                textcolor(cN = mefont);
                printfXY(monster[m].name, 5, 15);
                printf("(��)�� �޽��� ���߽��ϴ�. ");
                delay(100);

                mMana += mDamage;
                if (mMana >= monster[m].maxMana)
                    mMana = monster[m].maxMana;

                mHealth += mDamage;
                if (mHealth >= monster[m].maxHealth)
                    mHealth = monster[m].maxHealth;
                printf("ü�°� ������ %d ��ŭ ȸ���߽��ϴ�.", mDamage);
                break;

            default:
                break;
            }
            textcolor(cN = backg);

            monsterVar(20, 4, mHealth, mMana);
            statusVar(0, 19, healthP, manaP);
        }
        else
        {
            printfCCXY(monster[m].name, mefont, 5, 15);
            printfCC("(��)�� ���������ϴ�. ", mefont);
        }
    }
}
//******************************************************************************************************
//						�� ���
//******************************************************************************************************

void line(int x, int y, int i)
{ // x, y ��ǥ�� �޾Ƽ� �� ��ġ���� ���������� i��ŭ �� ����ϱ�
    for (int k = 0; k < i; k++)
    {
        printfCCXY("��", linefont, x + k, y);
    }
}

void Dline(int x, int y, int i, char d)
{ // x, y ��ǥ�� �޾Ƽ� �� ��ġ���� �Ʒ��� i��ŭ �� ����ϱ�, d�� �������� ���۰� ���� ����

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

void lineLine(int x, int y, int height)
{
    line(x, y, 80);
    line(x, y + height, 80);
}

void boxLine(int x, int y, int height, int width)
{
    line(x, y, width);
    line(x, y + height, width);
    Dline(x, y, height - 1, 'L');
    Dline(x + width, y, height - 1, 'R');
}

//******************************************************************************************************
//					�� ����â
//******************************************************************************************************

void statusVar(int x, int y, int health, int mana)
{ // x, y�� �޾Ƽ� �� ��ġ�� ����â ǥ��
    boxLine(x, y, 10, 39);

    printfXY("LV. ", x + 4, y + 2);
    printf("%d", level);
    gotoxy(x + 17, y + 2);
    textcolor(cN = pofont);
    printf(" P : %3d ", potion);
    printfCC(" ", backg);
    textcolor(cN = gofont);
    printf(" G : %3d ", gold);
    textcolor(cN = backg);

    healthVar(x + 2, y + 4, health, maxhealthP);
    manaVar(x + 2, y + 7, mana, maxmanaP);
    expVar(x, y + 11);
}

void healthVar(int x, int y, int health, int maxhealth)
{ // ü�� �κ� ���

    printfCCXY("  ü�� : ", hpfont, x, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)health / maxhealth) * 25) // ���� ü���� ������ ����
            printfCC("|", hpbar);
        else
            printfCC("|", 0);
    }

    gotoxy(x + 16, y + 1);
    textcolor(cN = hpfont);
    printf("%3d / %3d", maxhealth, health);
    textcolor(cN = backg);
}

void manaVar(int x, int y, int mana, int maxmana)
{ // ���� �κ� ���

    printfCCXY("  ���� : ", mpfont, x, y);

    if (mana == 0)
    {
        printfCC("������ ȸ���Ͻʽÿ�", 11);
    }
    else
    {
        for (int i = 0; i < 25; i++)
        {
            if (i < ((float)mana / maxmana) * 25)
            { // ���� ������ ������ ����
                printfCC("|", mpbar);
            }
            else
            {
                printfCC("|", 0);
            }
        }
    }

    gotoxy(x + 16, y + 1);
    textcolor(cN = mpfont);
    printf("%3d / %3d", maxmana, mana);
    textcolor(cN = backg);
}

void expVar(int x, int y)
{ // x, y�� �޾Ƽ� �� ��ġ�� ����â ǥ��

    boxLine(x, y, 5, 78);

    printfCCXY("����ġ", brackfont, 37, y + 1);

    gotoxy(x + 2, y + 3);
    for (int i = 0; i < 75; i++)
    {
        if (i < ((float)expP / (25 * level)) * 75)
        { // ���� ����ġ�� ������ ����
            printfCC("|", expbar);
        }
        else
        {
            printfCC("|", 0);
        }
    }
    gotoxy(35, y + 4);
    textcolor(cN = brackfont);
    printf("%3d / %3d", expP, (25 * level));
}

//**********************************
//			���� ���
//**********************************

void monsterVar(int x, int y, int health, int mana)
{ // x, y�� �޾Ƽ� �� ��ġ�� ����â ǥ��
    boxLine(x + 1, y, 8, 39);

    gotoxy(x + 3, y + 1);
    printf("[ %s ] %s   LV. %d  ", monster[m].grade, monster[m].name, monster[m].level); // ���� ���� �⺻ ���� ���

    monsterHealthVar(x + 2, y + 3, health, monster[m].maxHealth); // ���� ���� ü�� ǥ��
    monsterManaVar(x + 2, y + 6, mana, monster[m].maxMana);       // ���� ���� ���� ǥ��
}

void monsterHealthVar(int x, int y, int health, int maxhealth)
{ // ���� ü�� �κ� ���

    printfCCXY("ü�� : ", hpfont, x + 2, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)health / maxhealth) * 25)
        { // ���� ü���� ������ ����
            printfCC("|", hpbar);
        }
        else
        {
            textcolor(0); // �������� �ٲ�
            printfCC("|", 0);
        }
    }

    gotoxy(x + 17, y + 1);
    textcolor(cN = hpfont);
    printf("%3d / %3d", maxhealth, health);
    textcolor(cN = backg);
}

void monsterManaVar(int x, int y, int mana, int maxmana)
{ // ����  ���� �κ� ���
    printfCCXY("���� : ", mpfont, x + 2, y);

    for (int i = 0; i < 25; i++)
    {
        if (i < ((float)mana / maxmana) * 25)
        { // ���� ������ ������ ����
            printfCC("|", mpbar);
        }
        else
        {
            printfCC("|", 0);
        }
    }

    gotoxy(x + 17, y + 1);
    textcolor(cN = mpfont);
    printf("%3d / %3d", maxmana, mana);
    textcolor(cN = backg);
}

//**********************************
//			�޴� �̵�
//**********************************

int inputMoveY(int x, int y, int menuCount, char output[][2][31])
{ // x, y ��ġ�� �ִ� i�� ��ŭ�� output �޴��ٿ��� ���Ʒ��� �����̴� �κ�,
    int input;
    int exitSelect = 0;
    int i = menuCount;

    if (menuType == 1)
        menuPosY = 1; // Ÿ�� 1�� ���� �׻� 1��°�� Ŀ���� ����  /  ����

    do
    {
        for (int i = 0; i < menuCount; i++)
        { // ���� �޴� ��ġ�� ���� �ϳ� �ֱ�
            printfXY("                             ", x + 4, y + (i * 2) + 2);
            if (menuPosY == i + 1)
            {                                                   // ���� ��ġ�� ���� ����
                                                                //				gotoxy(x + 4, y + (i * 2) + 2);
                printfXY(output[i][0], x + 5, y + (i * 2) + 2); // ���� �޴� ��ĭ ���� ���
                textcolor(cN = infont);
                printfXY("                              ", x + 1, y - 1);
                printfXY(output[i][1], x + 2, y - 1); // �޴� infont ���
                textcolor(cN = backg);
            }
            else
                printfXY(output[i][0], x + 4, y + (i * 2) + 2);
        }

        ky = y + (menuPosY * 2);
        printfXY("��", x, ky);

        if (input = _kbhit())
            ;             // Ű���� �Է½� �̻��� �� ����  /  �� �ϸ� ��¥�� �̻��� ���� ����
        input = _getch(); // Ű���� �Է°� ����

        switch (input)
        {
        case UP: // Ű���� �� ������ ���� 2ĭ �̵�
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
        case DOWN: // Ű���� �Ʒ� ������ �Ʒ��� 2ĭ �̵�
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
            exitSelect = 1; // ESC ������ 1�� �ٲ�  /  �⺻�� 0
            printfXY("  ", x, ky);
            break;
        default:
            printfXY("  ", x, ky);
            break;
        }
    } while (input != ENTER && input != SPACE && input != ESC); // ���� Ȥ�� �����̽� Ȥ�� ESC ������ �ݺ� ����
    printfXY("                             ", x + 4, y + (menuPosY * 2));
    printfXY(output[menuPosY - 1][0], x + 4, y + (menuPosY * 2));

    if (exitSelect == 1) // ������ ������ 1�� ��� 0�� ȣ���� ���� ������  /  �ƴϸ� �޴��� ���� ��ġ �� 1 ~ 4
        return 0;
    else
        return menuPosY;
}

//****************	�� �Ʒ� ������ ���� �ٸ� �� ����. ****************
//	���� �޴����� ����ϰ�, �Ʒ��� ȭ��ǥ�� ����ؼ� �ٸ���.

void inputMoveX(int x, int y, int i, int xPos)
{                    // x, y ��ġ�� ���� i ��ŭ�� �������� l��ġ�� ȭ��ǥ�� ���
    menuPosX = xPos; // ��ġ �޾Ƽ� �ʱ�ȭ ��Ŵ

    int input;
    int kx;
    if (menuPosX == 1) // ����� �������� 2�� ���̶� �̷��� �ص�  /  �������� ����ġ�� ��ȯ
        kx = x;
    else
        kx = x * 2;

    do
    {
        printfXY("��", kx, y);

        if (input = _kbhit())
            ;             // Ű���� �Է½� �̻��� �� ����  /  Ű���� Ű�� ���� ����� �� ����.
        input = _getch(); // Ű���� �Է°� ����

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
//			�޴�â
//**********************************

int menuVar(int x, int y, int i)
{
    line(x, y, 35);
    line(x, y + i + 1, 35);
    Dline(x - 1, y, i, 'L');
    Dline(x + 35, y, i, 'R');

    return inputMoveY(x + 2, y, 4, menuString); // ������ �޴��� ������
}

int runawayVar(int x, int y, int i)
{
    reset(19); // ����â �ٷ� ������ �ʱ�ȭ
    line(0, y, 80);
    line(0, y + i, 80);
    printfXY("���� �������ðڽ��ϱ�?", x, y + 1);
    delay(25);
    settingMoveY(x + 10, y + 2, 2, 2, exitMenuString);
    return settingPosY;
}

void runawayMenu(int y, int i)
{ // 80�� i��ŭ ������ �κ��� ��� �� �־ �Ǵ� �κ���
    printfXY("��", 80 / i - 14, y);
    printfXY("�ƴϿ�", (80 / i - 16) * 2, y);
    delay(25);
    inputMoveX(80 / i - 18, y, 2, 2);
}

//**********************************
//			����
//**********************************

// �ƽ�Ű ��Ʈ  /  �˻��ؼ� ������  /  ������ ��Ʈ�� ����� ����Ʈ : http://patorjk.com/software/taag/
// ����� �̻��ص� ����� ����� ��
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
                textcolor(cN = backg); // ������ ��������
            else
                textcolor(cN = winfont);  // ���� �ƴϸ� winfont ������  /  ��� �����Ķ�  /  ���� ���
            printf("%c", winText[k][kk]); // ���� ���
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
                textcolor(cN = backg);
            else
                textcolor(cN = defont);
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

    textcolor(cN = backg); // ��� ������ �ٽ� ��������

    delay(150); // ���а�� ����� ��ٸ�
}

int resultVar(int x, int y, int i, int result)
{
    reset(19); // ����â �ٷ� ������ �ʱ�ȭ
    wdText(result);
    Rreset(19);

    lineLine(0, y, i);

    switch (result)
    { // ����ġ �ƴ϶� ����  /  if���̶���� ������
    case 1:
        rewardVar(x, y, i); // �¸��� ���� ȹ��
        lineLine(0, y, i);
        printfXY("�������� �¸��߽��ϴ�.", x, y + 2);        // �տ��� ��ġ ����  /  �ڿ��� ���
        printfXY("�ٸ� ���Ϳ� �ο�ðڽ��ϱ�?", x, y + 3); // �տ��� ��ġ ����  /  �ڿ��� ���
        winMenu(y + 9, 2);
        break;
    case 2:
        lineLine(0, y, i);
        printfXY("�������� �й��߽��ϴ�.", x, y + 2);                               // �տ��� ��ġ ����  /  �ڿ��� ���
        printfXY("�������� �޽��� ���Ͻðڽ��ϱ�? 10��尡 �Ҹ�˴ϴ�.", x, y + 3); // �տ��� ��ġ ����  /  �ڿ��� ���
        defeatMenu(y + 9, 2);
        break;
    default:
        break;
    }
    return menuPosX;
}

void winMenu(int y, int i)
{
    printfXY("�� ", 80 / i - 14, y);
    printfXY("�ƴϿ�(����) ", (80 / i - 16) * 2, y);

    inputMoveX(80 / i - 18, y, 2, 1);
}

void defeatMenu(int y, int i)
{
    printfXY("��(��� ȸ��) ", 80 / i - 19, y);
    printfXY("�ƴϿ�(�Ϻ� ȸ��) ", (80 / i - 20) * 2, y);
    delay(35);
    inputMoveX(80 / i - 22, y, 2, 1);
}

void rewardVar(int x, int y, int i)
{
    lineLine(0, y, i);

    printfXY("�������ִ� ���� ", x, y + 2);
    printfNC(monster[m].potionDrop, pofont);
    printf("���� ��� ");
    printfNC(monster[m].goldDrop, gofont);
    printf("���� �ֿ����ϴ�.");
    printfXY("����ġ��", x, y + 3);
    printfNC(monster[m].exp, expfont);
    printf("��ŭ ������ϴ�.");

    potion += monster[m].potionDrop;
    gold += monster[m].goldDrop;
    expP += monster[m].exp;

    delay(100);
    gotoxy(x + 15, y + 8);
    system("pause");
    Areset(18);

    statusVar(0, 19, healthP, manaP);

    levelUp(x, y, i); // ������ �Ѵٸ� �������� �Ѵ�.
}

void levelUp(int x, int y, int i)
{
    if (expP >= 25 * level)
    { // ������ �κ�
        lineLine(0, y, i);

        printfXY("����ġ�� ��� ä�� ����� ������ �� �ܰ� �����߽��ϴ�.", x, y + 2);

        delay(100);
        gotoxy(x + 15, y + 8);
        system("pause"); // ��� ����
        Areset(18);

        lineLine(0, y, i);

        expP -= 25 * level;
        gotoxy(x + 29, y + 1);
        printf("Lv. %d -> Lv. %d", level++, level);
        maxhealthP += 10;
        maxmanaP += 10;
        damage += 2;

        gotoxy(x, y + 3);
        printf("�ִ� ü�� %3d -> %3d  /  ", maxhealthP - 10, maxhealthP);
        printf("�ִ� ���� %3d -> %3d  /  ", maxmanaP - 10, maxmanaP);
        printf("���ݷ� %2d -> %2d", damage - 2, damage);

        statusVar(0, 19, healthP, manaP); //	����â ȭ�鿡 ���

        delay(150);
        gotoxy(x + 15, y + 8);
        system("pause"); // ��� ����
        Areset(18);

        lineLine(0, y, i);

        printfXY("ü�°� ������ ��� ȸ���Ǿ����ϴ�.", x, y + 2);

        healthP = maxhealthP;
        manaP = maxmanaP;
        statusVar(0, 19, healthP, manaP); //	����â ȭ�鿡 ���

        delay(150);
        gotoxy(x + 15, y + 8);
        system("pause"); // ��� ����
        Areset(18);
    }
}

//**********************************
//			����
//**********************************

// ���� �޴� ���� ������ �Լ�  /  ���� �� ���� ��
int settingMoveY(int x, int y, int menuCount, int menuPos, char output[][31])
{ // x, y ��ġ�� �ִ� i�� ��ŭ�� output �޴��ٿ��� ���Ʒ��� �����̴� �κ�,
    int input;
    int exitSelect = 0;
    int i = menuCount;
    settingPosY = menuPos;
    do
    {
        for (int i = 0; i < menuCount; i++)
        { // ���� �޴� ��ġ�� ���� �ϳ� �ֱ�
            printfXY("                                          ", x + 4, y + (i * 2) + 2);
            if (settingPosY == i + 1)
                printfXY(output[i], x + 5, y + (i * 2) + 2); // ���� �޴� ��ĭ ���� ���
            else
            {
                printfXY(output[i], x + 4, y + (i * 2) + 2);
            }
        }

        ky = y + (settingPosY * 2);
        gotoxy(x, ky);
        printf("��");

        if (input = _kbhit())
            ;             // Ű���� �Է½� �̻��� �� ����  /  �� �ϸ� ��¥�� �̻��� ���� ����
        input = _getch(); // Ű���� �Է°� ����

        switch (input)
        {

        case UP: // Ű���� �� ������ ���� 2ĭ �̵�
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
        case DOWN: // Ű���� �Ʒ� ������ �Ʒ��� 2ĭ �̵�
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
            settingPosY = 1; // ESC ������ 1�� �ٲ�
            printf("  ");

            break;
        default:
            gotoxy(x, ky);
            break;
        }
    } while (input != ENTER && input != SPACE && input != ESC); // ���� Ȥ�� �����̽� Ȥ�� ESC ������ �ݺ� ����

    return settingPosY;
}

void settingVar(int x, int y, int i)
{
    reset(35);
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
        case 1: // ���� ��ġ
            menuType = 0;
            break;
        case 2: // �׻� ù��°
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
        case 1: // ��
            exitSelect = 1;
            break;
        case 2: // �ƴϿ�
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
{ // 80�� i��ŭ ������ �κ��� ��� �� �־ �Ǵ� �κ���
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("����");
    delay(25);
    settingMoveY(x + 10, y + 4, 3, 1, settingString);
    Rreset(35);
    system("cls");
    return settingPosY;
}

int menuTypeMenu(int x, int y, int i)
{ // 80�� i��ŭ ������ �κ��� ��� �� �־ �Ǵ� �κ���
    reset(35);
    system("cls");
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("�޴� ��� ����");
    delay(25);
    settingMoveY(x + 10, y + 4, 2, 1, menuTypeSettingString);
    Rreset(35);
    system("cls");
    return settingPosY;
}

int exitMenu(int x, int y, int i)
{
    reset(35);
    system("cls");
    line(0, y, 80);
    line(0, y + i, 80);
    gotoxy(x, y + 1);
    printf("���� �����Ͻðڽ��ϱ�?");
    delay(25);
    settingMoveY(x + 10, y + 4, 2, 1, exitMenuString);
    Rreset(35);
    system("cls");
    return settingPosY;
}