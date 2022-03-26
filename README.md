
# monsterHunter

### 대학교 1학년 2학기 때 만든 C언어 기반의 턴제 RPG

## 1. 프로젝트 소개

대학 C언어 강의 때 개인적으로 뭔가를 만들어보면 가산점을 주신다고 해서 만들었던 게임입니다.
1달 정도 만들었고, 1주에 한 번씩 업데이트해서 버전이 4라고 되어있습니다.

위의 이유로 턴제로 진행되는 RPG를 만들어 보았고, 전투 시스템이 내가 행동하면 몬스터가 이어서 행동하는 식입니다.

주석의 경우 1버전엔 없이 진행하다가 교수 님의 조언으로 2버전부터 추가하기 시작했습니다. 
중간중간 느낌점들을 적기도 했고, 공부한다는 느낌으로 코딩했습니다.

프로젝트 구동 시 컴퓨터 환경에 따라 딜레이가 다를 수 있습니다.
그 이유가 딜레이 중일 때 입력 받아버리는 상황이 있어서 입력 없는 딜레이를 만들려고 고민하다가 반복 구문을 넣었기 때문입니다. 178번 라인입니다.

## 2. 프로젝트 구현 내용

영상 압축을 잘못해서 화질이 별로입니다! 감사합니다!

<img src="/실행 요약.gif" width="40%" title="게임 실행 GIF"></img>


### 게임의 흐름

1. 사용자의 입력을 받고 해당하는 몬스터와 전투를 벌인다.
2. 사용자는 키보드 위, 아래 버튼과 엔터 및 스페이스 키로 행동을 선택할 수 있다.   
2.1. 사용자의 행동은 '공격', '강한 공격', '포션  사용', '도망가기'가 있다.   
2.2. 공격 시 몬스터를 공격한다.   
2.3. 강한 공격 시 마력을 소모하여 몬스터를 강하게 공격한다. 이때 마력이 없으면 사용할 수 없다.   
2.4. 포션 사용 시 체력과 마력을 회복한다.   
2.5. 도망가기 시 전투에서 즉시 도망가며 패널티는 없다.   
3. 사용자가 행동을 마치면 이어서 몬스터가 무작위로 행동한다.   
3.1. 몬스터의 행동은 '공격', '강한 공격', '휴식 취하기'가 있다.   
3.2. 공격 시 사용자를 공격한다.   
3.3. 강한 공격 시 마력을 소모하여 사용자를 강하게 공격한다. 이때 마력이 없으면 공격을 행동한 것과 같다.   
3.4. 휴식 취하기 시 마력과 체력을 회복한다.   
4. 몬스터의 체력이 0이 되면 승리, 사용자의 체력이 0이 되면 패배다.   
4.1. 승리일 경우 보상을 획득할 수 있다. 보상은 골드, 포션, 경험치가 있다.   
4.2. 패배일 경우 골드를 소모하여 여관을 이용할 수 있다. 이때 체력과 마력이 모두 회복한다.   
4.3. 여관을 이용하지 않을 경우 체력과 마력 일부만 회복된다.   
5. 전투를 마친 후 전투를 이어가거나 게임을 종료할 지 선택할 수 있다.   
5.1. 전투를 선택할 시 1번으로 돌아간다.   
5.2. 종료를 선택할 시 게임을 종료한다.   
6. 게임 도중 ESC키를 누를 경우 메뉴가 나타나고 이때 종료를 선택할 수 있다.   
