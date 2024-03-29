/******************************************************************************************************
    몬스터

******************************************************************************************************/

struct _MonsterInfo
{                   // 몬스터 정보 틀
    char grade[5];  // 등급
    char name[11];  // 이름			/  현재 이름 길이가 10바이트임 혹시 모를 여유 1바이트
    int level;      // 레벨
    int maxHealth;  // 최대 체력
    int maxMana;    // 최대 마나		/  아직 고민중
    int damage;     // 데미지
    int defense;    // 방어력			/   아직 고민중
    int exp;        // 경험치
    int potionDrop; // 포션 드롭 갯수
    int goldDrop;   // 골드 드롭 갯수
};

struct _MonsterInfo monster[] = { //	몬스터 실제 정보  /  배운 거 써먹음
    {"일반", "슬라임", 1, 20, 15, 4, 2, 5, 1, 5},
    {"일반", "변종 버섯", 2, 30, 15, 7, 3, 7, 1, 10},
    {"일반", "변종 쥐", 3, 45, 25, 13, 5, 12, 2, 20},
    {"일반", "변종 큰 쥐", 4, 60, 30, 16, 6, 20, 3, 35},
    {"보스", "그루터기", 5, 120, 25, 20, 8, 50, 5, 100}

};

enum MonsterName
{ //	코드 짤 때 쉽게 보려고 배운 거 써먹음  /  프로그램이 복잡해지면 유용할 것 같음  /  어느 위치에 어느 몬스터만 등장 등
    slime = 0,
    mushroom,
    mice,
    bigmice,
    stump

} m = slime;